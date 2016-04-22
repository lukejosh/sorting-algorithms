from matplotlib import pyplot as plt
import time

def make_xy_graphs(data_file):
    x = []
    y = []

    for line in data_file:
        l = line.rsplit(' ')

        x.append(int(l[0]))
        y.append(float(l[1]))

    return x, y

def make_func_xy(length, func):
    x = range(length)
    y = [func(f) for f in x]

    return x, y

def make_plot(filename, include_expected=True, include_results=True, func=None, title=None, output=None):
    data_file = open(filename)
    x, y = make_xy_graphs(data_file)

    if include_expected:
        x1, y1 = make_func_xy(len(x), func)
        plt.plot(x1, y1, '2-r', label='theoretical')

    if include_results:
        plt.plot(x, y, '.', label='data')
    plt.legend(loc='upper left')
    plt.xlabel('Size of array')
    yl = 'Time (S)' if 'time' in filename else 'Number of Operations'
    plt.ylabel(yl)
    plt.title(title)
    plt.savefig(output)
    plt.clf()

    data_file.close()

def main():
    # plot measured operations for sorted arrays
    make_plot("sorted_array_op_count.txt", include_expected=False, func=lambda x: x - 1, title="Sorted Array Measured Results", output = "sorted_array_op_count_measured.svg")

    # plot expected operations for reverse sorted arrays
    make_plot("sorted_array_op_count.txt", include_results=False, func=lambda x: x - 1, title="Sorted Array Expected Results", output="sorted_array_op_count_expected.svg")

    # plot measured operations for reverse sorted arrays
    make_plot("reverse_sorted_array_op_count.txt", include_expected=False, func=lambda x: (x*(x-1)) / float(2), title="Reverse Sorted Array Measured Results", output="reverse_sorted_array_op_count_measured.svg")

    # plot expected operations for reverse sorted arrays
    make_plot("reverse_sorted_array_op_count.txt", include_results=False, func=lambda x: (x*(x-1)) / float(2), title="Reverse Sorted Array Measured Results", output="reverse_sorted_array_op_count_expected.svg")

    # plot operations for random arrays
    make_plot("random_array_op_count.txt", func=lambda x: (x ** 2) / float(4), title="Random Array Results", output="random_array_op_count.svg")

    # plot time for sorted arrays
    make_plot("sorted_array_time.txt", func=None, include_expected=False, title="Measured time for Sorted array", output="sorted_array_time.svg")

    # plot time for reverse sorted arrays
    make_plot("reverse_sorted_array_time.txt", func=None, include_expected=False, title="Measured Time For a Reverse Sorted Array", output="reverse_sorted_array_time.svg")

    # plot time for random arrays
    make_plot("random_array_time.txt", func=None, include_expected=False, title="Measured Time For a Random Array", output="random_array_time.svg")
