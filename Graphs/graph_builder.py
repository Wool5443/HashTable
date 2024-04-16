from matplotlib import pyplot as plt
import numpy as np
from os import listdir

def hist(ys):
    hist_data = []

    for i in range(len(ys)):
        hist_data += [i] * (ys[i] + 1)

    plt.hist(hist_data, range(0, len(ys), int(len(ys)** 0.4)))

def main():
    containers_folder = "Containers/"
    containers_files  = [containers_folder + x for x in listdir(containers_folder) if x[-3:] == "txt"]

    for file_path in containers_files:
        with open(file_path, "r") as f:
            lines = f.read().split('\n')
            xs = [0] * len(lines)
            ys = [0] * len(lines)
            for i, line in enumerate(lines):
                if line:
                    xs[i], ys[i] = map(int, line.split())

        hist(ys)
        print(f"done {file_path}")
        plt.savefig(file_path + 'graph.png')
        plt.cla()

    return

if __name__ == '__main__':
    main()

