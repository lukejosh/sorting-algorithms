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

def make_func_xy(length):
	x = range(length)
	y = [float(f ** 2) / 4 for f in x]

	return x, y

def main():
	data_file = open("random_array_op_count.txt")
	x, y = make_xy_graphs(data_file)
	x1, y1 = make_func_xy(len(x))
	plt.plot(x, y, '.', label='data')
	plt.plot(x1, y1, '2-r', label='theoretical')
	plt.legend(loc='upper left')
	plt.xlabel('Size of array')
	plt.ylabel('Number of operations')
	plt.title('Average Array Operations Count')
	plt.savefig('random_basic_operation_count_data.svg'.format(int(time.time())))
	#plt.show()