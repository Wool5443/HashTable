# HashTable
Моя реализация хэш-таблицы. Ключи - слова на английском языке,
а значения - количество их встреч в тексте.

## Система
- **CPU** Intel Core i5 1135G7
- **OS** Arch Linux x86_64 6.8.5-zen1-1-zen
- **RAM** 8GB 3200 Mhz
- **Compiler** gcc 13.2.1
- **Containers counts** 5113
- **Text** Все произведение Шекспира

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
![alt text](Containers/ContainersUtils.csvgraph.png)

## Тесты

|Hash        | Уровень оптимизации | Количество тактов | Относительно предыдщуего |
|------------|---------------------|-------------------|--------------------------|
| Zero       | -O0                 |$1.972 * 10^{11}$  | $1$                      |
| Length     | -O0                 |$2.675 * 10^{10}$  | $1$                      |
| SumLength  | -O0                 |$1.184 * 10^{10}$  | $1$                      |
| FirtsChar  | -O0                 |$6.636 * 10^{ 9}$  | $1$                      |
| Sum        | -O0                 |$1.318 * 10^{ 9}$  | $1$                      |
| MurMur2A   | -O0                 |$1.323 * 10^{ 9}$  | $1$                      |

|Hash        | Уровень оптимизации | Количество тактов | Относительно предыдщуего |
|------------|---------------------|-------------------|--------------------------|
| Zero       | -O1                 |$1.227 * 10^{11}$  | $0.62$                   |
| Length     | -O1                 |$1.585 * 10^{10}$  | $0.59$                   |
| SumLength  | -O1                 |$7.425 * 10^{ 9}$  | $0.63$                   |
| FirtsChar  | -O1                 |$4.276 * 10^{ 9}$  | $0.64$                   |
| Sum        | -O1                 |$1.102 * 10^{ 9}$  | $0.84$                   |
| MurMur2A   | -O1                 |$1.035 * 10^{ 9}$  | $0.78$                   |

Дальше протестировать неудолось, ибо мои обёрточный функции начали инлайнится.

## Оптимизация

Нужно решить, какую хэш-функцию использовать далее, для этого посмотрим, какой хэш
успешно скейлится. Увеличим в $\approx 2$ количество контейнеров. Поулчилось, что
MurMurHash оказался лучшим. Оставим только его, и поставим также O3. Протестим!
Это будет нашей "базой". Будем суммарное количество тиков функции HashTable::Get().

![alt text](img/O3_5113.png)

| Оптимизация       | Тики             | Ускорение относительно "базы" | Относительное ускорение |
|-------------------|------------------|-------------------------------|-------------------------|
| O3                | $3.294 * 10^{8}$ | 1                             | 1                       |

Видно, что сейчас большую процессорного времени занимает strcmp, перепишем его, используя интринсики.

```c++
bool StrcmpAVX512(const char* s1, const char* s2)
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
| O3 StrCmpAVX512   | $2.909 * 10^{8}$ | 1.13                          | 1.13                    |

