from csv import reader
from os import listdir

class Column:
    name: str
    value: int

    def __init__(self, name: str, value: int):
        self.name  = name
        self.value = value


def main():
    col_names = []
    values    = []

    timings_folder = "Timings/"
    timing_1x_condition = lambda x: x[-6:] == "1x.csv"
    timing_2x_condition = lambda x: x[-6:] == "2x.csv"
    print(listdir(timings_folder))
    timings_files  = [timings_folder + x for x in listdir(timings_folder) if timing_1x_condition(x)]

    columns = []    

    for file in timings_files:
        with open(file, 'r') as f:
            csv_reader = reader(f, delimiter='\t', quotechar='"')
            for row in csv_reader:
                columns.append(Column(row[0], int(row[1])))
    
    columns = [col for col in columns if "sum" in col.name]
    
    for col in columns:
        print(f"|{col.name}", end='')
    print(f"|\n{'|-----------' * len(columns)}|")
    for col in columns:
        good_val = str(f"{col.value:.3E}").replace("E+", "*10^{") + '}'
        print(f"|${good_val}$", end='')
    print("|")


if __name__ == '__main__':
    main()
