#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>

using namespace std;

int insertion_sort_op_count(int array_to_sort[], int length){
    int v;
    int j;
    int op_count = 0;

    for(int i = 1; i < length; i++){
        v = array_to_sort[i];
        j = i - 1;
        op_count++;

        while(j >= 0 && array_to_sort[j] > v){
            op_count++;
            array_to_sort[j + 1] = array_to_sort[j];
            j--;
        }
        array_to_sort[j + 1] = v;
    }
    return op_count;
}

double insertion_sort_time(int array_to_sort[], int length){
    int v;
    int j;
    clock_t start;
    start = clock();

    unsigned long long duration;

    for(int i = 0; i < length; i++){
        v = array_to_sort[i];
        j = i - 1;

        while(j >= 0 && array_to_sort[j] > v){
            if (j >= 0){
            }
            array_to_sort[j + 1] = array_to_sort[j];
            j--;
        }
        array_to_sort[j + 1] = v;
    }
    return (clock() - start) / (double) CLOCKS_PER_SEC;
}

void print_array(int array[], int length){
    cout << "[";
    for (int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << "]" << endl;
}

void populate_random_data(int empty[], int length, int lower, int upper){
    for (int i = 0; i < length; i++){
        empty[i] = rand() % (upper - lower + 1) + lower;
    }
}

void populate_sorted_data(int empty[], int length, int lower, int upper){
    for (int i = 0; i < length; i++){
        empty[i] = i + 1;
    }
}

void populate_reverse_sorted_data(int empty[], int length, int lower, int upper){
    for (int i = 0; i < length; i++){
        empty[i] = upper - i;
    }
}

void write_data_points_to_file(string filename, double data_points[][2], int num_points){
    ofstream file(filename);

    for(int i = 0; i < num_points; i++){
        file << data_points[i][0] << " " << data_points[i][1] << endl;
    }

    file.close();

}

void test_range_operations(string filename, int lower, int upper, int iterations, void (*genFunction)(int[], int, int, int)){
    double operations;
    double data_points[upper - lower][2];
    for (int length = lower; length <= upper; length++){
        cout << length << " / " << upper << endl;
        operations = 0;
        for(int repeat = 0; repeat < iterations; repeat++) {
            int gen_array[length];
            genFunction(gen_array, length, 0, upper * 2);
            operations += insertion_sort_op_count(gen_array, length);
        }
        data_points[length - lower][0] = length;
        data_points[length - lower][1] = operations / (double) iterations;
    }
    write_data_points_to_file(filename, data_points, upper - lower);
}

void test_range_time(string filename, int lower, int upper, int iterations, void (*genFunction)(int[], int, int, int)){
    double time;
    double data_points[upper - lower][2];
    for (int length = lower; length <= upper; length++){
        cout << length << " / " << upper << endl;
        time = 0;
        for(int repeat = 0; repeat < iterations; repeat++) {
            int gen_array[length];
            genFunction(gen_array, length, 0, upper * 2);
            time += insertion_sort_time(gen_array, length);
        }
        data_points[length - lower][0] = length;
        data_points[length - lower][1] = time / (double) iterations;
    }
    write_data_points_to_file(filename, data_points, upper - lower);
}

int main(){
    //Test number of operations for sorted arrays
    test_range_operations("sorted_array_op_count.txt", 2, 1000, 10, &populate_sorted_data);

    //Test number of operations for sorted arrays
    test_range_operations("reverse_sorted_array_op_count.txt", 2, 1000, 10, &populate_reverse_sorted_data);
}