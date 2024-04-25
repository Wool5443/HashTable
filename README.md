# HashTable
Моя реализация хэш-таблицы. Ключи - слова на английском языке,
а значения - количество их встреч в тексте.

## Система
- **CPU** Intel Core i5 1135G7
- **OS** Arch Linux x86_64 6.8.5-zen1-1-zen
- **RAM** 8GB 3200 Mhz
- **Compiler** gcc 13.2.1

## Исследование загруженности таблицы

### ZeroHash
![alt text](Containers/ContainersZero.csvgraph.png)

### FirstChar
![alt text](Containers/ContainersFirstChar.csvgraph.png)

### LengthHash
![alt text](Containers/ContainersLength.csvgraph.png)

### SumLengthHash
![alt text](Containers/ContainersSumLength.csvgraph.png)

### SumHash
![alt text](Containers/ContainersSum.csvgraph.png)

### Murmur2AHash
![alt text](Containers/ContainersMurMur.csvgraph.png)

### CRC32
![alt text](Containers/ContainersCRC32.csvgraph.png)

## Тесты 0 итерация
Containers Count = 5113
|FirtChar - sum|MurMur - sum|Zero - sum|Sum - sum|SumLength - sum|CRC32 - sum|Length - sum|
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|$1.860*10^{09}$|$3.998*10^{08}$|$7.143*10^{10}$|$4.299*10^{08}$|$3.581*10^{09}$|$3.675*10^{08}$|$7.944*10^{09}$|

## Оптимизация

Нужно решить, какую хэш-функцию использовать далее, для этого посмотрим, какой хэш
успешно скейлится. Увеличим в $\approx 2$ количество контейнеров. Поулчилось, что
MurMurHash оказался лучшим. Оставим только его, и поставим также O3. Протестим!
Это будет нашей "базой".

ContainersCount = 10007
|Zero|Length|FirtChar|SumLength|Sum|MurMur|CRC32|
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|$7.173*10^{10}$|$7.934*10^{09}$|$1.870*10^{09}$|$3.626*10^{09}$|$4.348*10^{08}$|$4.078*10^{08}$|$3.751*10^{08}$|

![alt text](img/O3_5113.png)

| Оптимизация       | Тики             | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|------------------|-------------------------------|-------------------------|
| O3                | $3.294 \cdot 10^{8}$ | 1                             | 1                       |

Видно, что сейчас большую процессорного времени занимает strcmp, перепишем его, используя интринсики.

```c++
bool StrcmpAVX512(const char\cdot s1, const char\cdot s2)
{
    __m512i s1_intr = _mm512_load_epi64(s1);
    __m512i s2_intr = _mm512_load_epi64(s2);
    __mmask64 cmp   = _mm512_cmp_epi8_mask(s1_intr, s2_intr, _MM_CMPINT_EQ);
    return cmp == (~(uint64_t)0);
}
```

![alt text](img/O3_5113_StrcmpAVX512.png)

| Оптимизация       | Тики             | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|------------------|-------------------------------|-------------------------|
| O3 StrCmpAVX512   | $2.909 \cdot 10^{8}$ | 1.13                          | 1.13                    |

