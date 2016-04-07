#include <iostream>
#include <fstream>
#include <python2.7/Python.h>

using namespace std;

void insertion_sort_v2(int arr[], int length) {
    int c = 0;
    for (int i = 1; i < length; i++) {
        // a temporary copy of the current element
        int tmp = arr[i];
        int j;

        // find the position for insertion
        for (j = i; j > 0; j--) {
            c++;
            if (arr[j - 1] < tmp)
                break;
            // shift the sorted part to right
            arr[j] = arr[j - 1];
        }

        // insert the current element
        arr[j] = tmp;
    }
    cout << c << endl;
}

int insertion_sort(int array_to_sort[], int length){
    int v;
    int j;
    int op_count = 0;

    for(int i = 0; i < length; i++){
        v = array_to_sort[i];
        j = i - 1;
        op_count++;
        while(j >= 0 && array_to_sort[j] > v){
            if (j >= 0){
                op_count++;
            }
            array_to_sort[j + 1] = array_to_sort[j];
            j--;
        }
        array_to_sort[j + 1] = v;
    }
    return op_count;
}

void print_array(int array[], int length){
    cout << "[";
    for (int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << "]" << endl;
}

void populate_data(int empty[], int length, int lower, int upper){
    for (int i = 0; i < length; i++){
        empty[i] = rand() % (upper - lower + 1) + lower;
    }
}

void test_operations_fixed_length(int length, int lower, int upper, int iterations){
    int total_operations = 0;
    for (int repeat = 0; repeat < iterations; repeat++){

        int gen_array[length];
        populate_data(gen_array, length, lower, upper);
        total_operations += insertion_sort(gen_array, length);
        delete(gen_array);
    }

    int expected_operations = ((length - 1) * (length - 2)) / double(4);
    int actual_operations = double(total_operations) / iterations;

    cout << "expected: " << expected_operations  << "\nactual: " << actual_operations << endl;
    cout << "\n% difference: " << double(abs(expected_operations - actual_operations)) / expected_operations * 100;
}

void test_range(int lower, int upper){
    ofstream data_file("data.txt");

    for (int length = lower; length < upper; length++){
            cout << length << " / " << upper << endl;
        int gen_array[length];
        populate_data(gen_array, length, 0, length * 2);
        int data_point[2] = {length, insertion_sort(gen_array, length)};
        data_file << data_point[0] << " " << data_point[1] << endl;
    }
    data_file.close();
}

void make_plot(){
    Py_Initialize();
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyString_FromString("."));
    PyRun_SimpleString("import plotter\nplotter.main()\n");
    Py_Finalize();
}

int notmain(){
    time_t t;
    srand(time(&t));
    test_range(0, 10000);
    make_plot();
    return 0;
}

int main(){
    int length = 10;
    int arr[10] = {1,2,3,4,5,6,7,8,8,10};
    insertion_sort_v2(arr, 10);
    print_array(arr, 10);
}