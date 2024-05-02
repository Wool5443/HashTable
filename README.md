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
|$7.817\cdot10^{10}$|$1.068\cdot10^{10}$|$4.907\cdot10^{9}$|$2.676\cdot10^{9}$|$5.292\cdot10^{8}$|$4.724\cdot10^{8}$|$4.326\cdot10^{8}$|

## Оптимизация

Видно, что CRC32 быстрее, чем MurMur, да и распределение у него получше,
поэтому будем использовать его.

| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|---------------------------------|-------------------------------|-------------------------|
| O3                | $3.927 \cdot 10^{8} \pm 1.46\%$ | 1                             | 1                       |

<details>
<summary> <b> Profiler data O3 </b> </summary>
<p align="center">
<img src = img/Base.png style = "width: 65vw">
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
| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|---------------------------------|-------------------------------|-------------------------|
| O3                | $3.927 \cdot 10^{8} \pm 1.46\%$ | 1                             | 1                       |
| O3 StrcmpAVX      | $3.640 \cdot 10^{8} \pm 1.41\%$ | $7.88\%$                      | $7.88\%$                |

Посмотрим, что ещё можно улучшить.

<details>
<summary> <b> Profiler data O3StrcmpAVX </b> </summary>
<p align="center">
<img src = img/StrcmpAVX.png style = "width: 65vw">
</p>
</details>

Видно, что CRC32 довольно "горячая", поэтому я решил переписать её более
оптимально. Сейчас там хэш считается побайтово, попробую делать это
по 8 байт.

| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|---------------------------------|-------------------------------|-------------------------|
| O3                | $3.927 \cdot 10^{8} \pm 1.46\%$ | 1                             | 1                       |
| O3 StrcmpAVX      | $3.640 \cdot 10^{8} \pm 1.41\%$ | $7.88\%$                      | $7.88\%$                |
| CRC32 Steps 8     | $3.659 \cdot 10^{8} \pm 1.20\%$ | $7.32\%$                      | $-0.5\%$                |

Получилось медленнее. Попробую ещё развернуть цикл, обрабатывающий последние 0-7 байт.

| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|---------------------------------|-------------------------------|-------------------------|
| O3                | $3.927 \cdot 10^{8} \pm 1.46\%$ | 1                             | 1                       |
| O3 StrcmpAVX      | $3.640 \cdot 10^{8} \pm 1.41\%$ | $7.88\%$                      | $7.88\%$                |
| CRC32 Loop Unroll | $3.551 \cdot 10^{8} \pm 1.02\%$ | $10.59\%$                     | $2.51\%$                |

Прогоним через профилировщик.

<details>
<summary> <b> Profiler data CRC32 Loop Unroll </b> </summary>
<p align="center">
<img src = img/CRC32LoopUnroll.png style = "width: 65vw">
</p>
</details>

Больше оптимизировать ничего нельзя, поэтому мне пришла идея оптимизировать
операцию нахождения остатка от деления, ведь для этого сейчас используется
дорогая инструкция div, а для остатков по степеням двойки можно использовать
дешёвые битовые операции. Для этого придётся изменить количество
контейнеров на 4096.

```c++
static inline uint64_t _mod2(uint64_t value, const uint64_t mod)
{
    asm volatile("and  %0, %1" : "+r"(value) : "r"(mod - 1));
    return value;
}
```

| Оптимизация       | Тики                            | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|---------------------------------|-------------------------------|-------------------------|
| O3                | $3.927 \cdot 10^{8} \pm 1.46\%$ | 1                             | 1                       |
| O3 StrcmpAVX      | $3.640 \cdot 10^{8} \pm 1.41\%$ | $7.88\%$                      | $7.88\%$                |
| CRC32 Loop Unroll | $3.551 \cdot 10^{8} \pm 1.02\%$ | $10.59\%$                     | $2.51\%$                |
| Mod2              | $3.536 \cdot 10^{8} \pm 0.74\%$ | $11.06\%$                     | $0.42\%$                |
