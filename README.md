# HashTable
Моя реализация хэш-таблицы. Ключи - слова на английском языке,
а значения - количество их встреч в тексте.

## Система
- **CPU** Intel Core i5 1135G7
- **OS** Arch Linux x86_64 6.8.8-zen1-1-zen
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
Containers Count = 8192
|Zero|Length|SumLength|FirstChar|Sum|MurMur|CRC32|
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|$8.797\cdot10^{10}$|$1.160\cdot10^{10}$|$5.542\cdot10^{9}$|$3.178\cdot10^{9}$|$7.354\cdot10^{8}$|$7.027\cdot10^{8}$|$7.418\cdot10^{8}$|

## Оптимизация

Видно, что CRC32 быстрее, чем MurMur, да и распределение у него получше,
поэтому будем использовать его. Я буду измерять 100 раз поиск всех слов
текста в хэш-таблице.

|Оптимизация|Тики|Ускорение относительно "базы"|Относительное ускорение|
|-----------|-----------|-----------|-----------|
|Base|$1.091\cdot10^{8} \pm 2.01\%$|$0.0\%$|$0.0\%$|

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

|Оптимизация|Тики|Ускорение относительно "базы"|Относительное ускорение|
|-----------|-----------|-----------|-----------|
|Base|$1.091\cdot10^{8} \pm 2.01\%$|$0.0\%$|$0.0\%$|
|StrcmpAVX|$9.508\cdot10^{7} \pm 1.18\%$|$14.75\%$|$14.75\%$|

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

|Оптимизация|Тики|Ускорение относительно "базы"|Относительное ускорение|
|-----------|-----------|-----------|-----------|
|Base|$1.091\cdot10^{8} \pm 2.01\%$|$0.0\%$|$0.0\%$|
|StrcmpAVX|$9.508\cdot10^{7} \pm 1.18\%$|$14.75\%$|$14.75\%$|
|CRC32Step8|$9.473\cdot10^{7} \pm 1.57\%$|$15.17\%$|$0.37\%$|

Ускорение оказалось совсем небольшим. Попробую ещё развернуть цикл,
обрабатывающий последние 0-7 байт. Видимо, дело в том, что английские
слова в основном короткие, поэтому по 8 байт мы шагаем редко, а чаще
как и раньше проходимся по одному байту за раз. Поэтому я разверну
цикол, в котором обрабатываются оставшиеся от деления на 8 байты.

|Оптимизация|Тики|Ускорение относительно "базы"|Относительное ускорение|
|-----------|-----------|-----------|-----------|
|Base|$1.091\cdot10^{8} \pm 2.01\%$|$0.0\%$|$0.0\%$|
|StrcmpAVX|$9.508\cdot10^{7} \pm 1.18\%$|$14.75\%$|$14.75\%$|
|CRC32Step8|$9.473\cdot10^{7} \pm 1.57\%$|$15.17\%$|$0.37\%$|
|CRC32LoopUnrolling|$8.861\cdot10^{7} \pm 1.16\%$|$23.12\%$|$6.9\%$|

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
контейнеров на 8192.

```c++
static inline uint64_t _mod2(uint64_t value, const uint64_t mod)
{
    asm volatile("and  %0, %1" : "+r"(value) : "r"(mod - 1));
    return value;
}
```

|Оптимизация|Тики|Ускорение относительно "базы"|Относительное ускорение|
|-----------|-----------|-----------|-----------|
|Base|$1.091\cdot10^{8} \pm 2.01\%$|$0.0\%$|$0.0\%$|
|StrcmpAVX|$9.508\cdot10^{7} \pm 1.18\%$|$14.75\%$|$14.75\%$|
|CRC32Step8|$9.473\cdot10^{7} \pm 1.57\%$|$15.17\%$|$0.37\%$|
|CRC32LoopUnrolling|$8.861\cdot10^{7} \pm 1.16\%$|$23.12\%$|$6.9\%$|
|Mod2|$8.407\cdot10^{7} \pm 2.82\%$|$29.77\%$|$5.4\%$|

## Вывод
Нам удалось оптимизировать хэш-таблицу со строками на 29.77%, используя
различные техники оптимизации такие, как переписывание на ассемблере,
интринсики, gcc inline assembly, рассмотрение частных случаев,
а также профилировщик perf.
