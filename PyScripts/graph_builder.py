from matplotlib import pyplot as plt
import numpy as np
from os import listdir
from csv import reader

def hist(ys, load_factor):
    hist_data = []

    for i in range(len(ys)):
        hist_data += [i] * (ys[i] + 1)

    plt.title(f"Load Factor = {load_factor}")
    plt.xlabel("Container #")
    plt.ylabel("Load")
    plt.hist(hist_data, range(0, len(ys), int(len(ys)** 0.4)))

def main():
    containers_folder = "Containers/"
    containers_files  = [containers_folder + x for x in listdir(containers_folder) if x[-3:] == "csv"]

    for file_path in containers_files:
        with open(file_path, "r") as f:
            csv_reader = list(reader(f, delimiter='\t'))
            ys = [list(map(int, row))[1] for row in csv_reader[:-1]]
            load_factor = float(csv_reader[-1][0])

        hist(ys, load_factor)
        print(f"done {file_path}")
        plt.savefig(file_path + 'graph.png')
        plt.cla()

    return

if __name__ == '__main__':
    main()

