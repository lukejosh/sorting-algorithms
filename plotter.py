from matplotlib import pyplot as plt
from time import time

def make_xy_graphs(data_file):
	x = []
	y = []

	for line in data_file:
		l = line.rsplit(' ')

		x.append(int(l[0]))
		y.append(int(l[1][:-1]))

	return x, y

def make_func_xy(length):
	x = range(length)
	y = [(f**2)/4 for f in x]

	return x, y

def main():
	data_file = open("data.txt")
	x, y = make_xy_graphs(data_file)
	x1, y1 = make_func_xy(len(x))
	plt.plot(x, y, '.', label='data')
	plt.plot(x1, y1, '2-r', label='theoretical')
	plt.legend(loc='upper left')
	plt.xlabel('Size of array')
	plt.ylabel('Number of operations')
	plt.savefig('data_export_{0}.svg'.format(int(time.time())))
	plt.show()