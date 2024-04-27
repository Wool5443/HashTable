# HashTable
Моя реализация хэш-таблицы. Ключи - слова на английском языке,
а значения - количество их встреч в тексте.

## Система
- **CPU** Intel Core i5 1135G7
- **OS** Arch Linux x86_64 6.8.5-zen1-1-zen
- **RAM** 8GB 3200 Mhz
- **Compiler** gcc 13.2.1

## Исследование загруженности таблицы

<details>
<summary> <b> Distributions </b> </summary>
<p align="center">

<figure>
    <img src = Containers/ContainersZero.csvgraph.png style = "width: 65vw">
    <figcaption align="center">Zero</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersLength.csvgraph.png style = "width: 65vw">
    <figcaption align="center">Length</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersSumLength.csvgraph.png style = "width: 65vw">
    <figcaption align="center">SumLength</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersFirstChar.csvgraph.png style = "width: 65vw">
    <figcaption align="center">FirstChar</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersSum.csvgraph.png style = "width: 65vw">
    <figcaption align="center">Sum</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersMurMur.csvgraph.png style = "width: 65vw">
    <figcaption align="center">MurMur</figcaption>
</figure>
<figure>
    <img src = Containers/ContainersCRC32.csvgraph.png style = "width: 65vw">
    <figcaption align="center">CRC32</figcaption>
</figure>

</p>
</details>

## Тесты 0 итерация
Containers Count = 5113
|Zero|Length|SumLength|FirstChar|Sum|MurMur|CRC32|
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|$7.125\cdot10^{10}$|$8.125\cdot10^{09}$|$3.698\cdot10^{09}$|$1.921\cdot10^{09}$|$4.546\cdot10^{08}$|$4.228\cdot10^{08}$|$3.905\cdot10^{08}$|

## Оптимизация

Нужно решить, какую хэш-функцию использовать далее, для этого посмотрим, какой хэш
успешно скейлится. Увеличим в $\approx 2$ количество контейнеров.

ContainersCount = 10007
|Zero|Length|SumLength|FirstChar|Sum|MurMur|CRC32|
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|$7.120\cdot10^{10}$|$7.893\cdot10^{09}$|$3.582\cdot10^{09}$|$1.864\cdot10^{09}$|$4.330\cdot10^{08}$|$4.077\cdot10^{08}$|$3.788\cdot10^{08}$|

Видно, что сильнее всего ускорились **MurMur** и **CRC32**, но последний всё ещё быстрее, поэтому далее будем использовать
его. Теперь 100 раз прогоним наш тест, и запишем этот результат как "базу".

| Оптимизация       | Тики             | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|------------------|-------------------------------|-------------------------|
| O3                | $3.962 \cdot 10^{8} \pm 0.89\%$ | 1                             | 1        |

<details>
<summary> <b> Profiler data O3 </b> </summary>
<p align="center">
<img src = img/O3.png style = "width: 65vw">
</p>
</details>

Видно, что сейчас большую процессорного времени занимает strcmp, перепишем его, используя интринсики.

```c++
bool StrcmpAVX(const char* s1, const char* s2)
{
    __m256i s1Vector = _mm256_loadu_epi8(s1);
    __m256i s2Vector = _mm256_loadu_epi8(s2);

    __m256i difference = _mm256_xor_epi32(s1Vector, s2Vector);

    __mmask32 res = _mm256_test_epi8_mask(difference, difference);

    return res == 0;
}
```

| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительно предыдущего |
|-------------------|---------------------------------|-------------------------------|--------------------------|
| O3 StrCmpAVX      | $3.707 \cdot 10^{8} \pm 1.17\%$ | $6.88\%$                      | $6.88\%$                 |

Посмотрим, что ещё можно улучшить.

<details>
<summary> <b> Profiler data O3StrcmpAVX </b> </summary>
<p align="center">
<img src = img/O3StrcmpAVX.png style = "width: 65vw">
</p>
</details>

Ни одну из "горячих" функций нельзя особо оптимизировать, поэтому мне пришла оптимизировать
операцию вычисления остатка, ведь для этого вызывается довольно тяжёлая инструкция ```div```.
Вместо этого остаток можно найти с помощью сдвигов и вычитания.
