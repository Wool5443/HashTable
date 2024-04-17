# HashTable
Моя реализация хэш-таблицы. Ключи - слова на английском языке,
а значения - количество их встреч в тексте.

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

## Оптимизация

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