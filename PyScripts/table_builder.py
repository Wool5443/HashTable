from csv import reader
from sys import argv
from os import listdir

class Column:
    name: str
    value: int

    def __init__(self, name: str, value: int):
        self.name  = name
        self.value = value


HASH_RANK = \
{
    "Zero": 0,
    "Length": 1,
    "SumLength": 2,
    "FirstChar": 3,
    "Sum": 4,
    "MurMur": 5,
    "CRC32": 6,
}


def main():
    if len(argv) != 2:
        print("What to build table from? 1x or 2x")
        return -1

    col_names = []
    values    = []

    timings_folder = "Timings/"

    timing_1x_condition = lambda x: x[-6:] == "1x.csv"
    timing_2x_condition = lambda x: x[-6:] == "2x.csv"
    condition = timing_1x_condition if argv[1] == "1x" else timing_2x_condition

    timings_files  = [timings_folder + x for x in listdir(timings_folder) if condition(x)]

    columns = []    

    for file in timings_files:
        with open(file, 'r') as f:
            csv_reader = reader(f, delimiter='\t', quotechar='"')
            for row in csv_reader:
                columns.append(Column(row[0], int(row[1])))
    
    columns = [col for col in columns if col.name.count(' ') == 0]
    columns.sort(key=lambda x: HASH_RANK[x.name])
    
    for col in columns:
        print(f"|{col.name}", end='')
    print(f"|\n{'|-----------' * len(columns)}|")
    for col in columns:
        good_val = str(f"{col.value:.3E}").replace("E+", "*10^{") + '}'
        print(f"|${good_val}$", end='')
    print("|")


if __name__ == '__main__':
    main()
