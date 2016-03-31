#include <iostream>

using namespace std;

int insertion_sort(int array_to_sort[], int length){
    int v;
    int j;
    int op_count = 0;

    for(int i = 0; i < length; i++){
        v = array_to_sort[i];
        j = i - 1;
        while(j >= 0 && array_to_sort[j] > v){
            if (j >= 0){
                op_count++;
            }
            array_to_sort[j+1] = array_to_sort[j];
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
    }

    int expected_operations = length * length / 4.0;
    int actual_operations = double(total_operations) / iterations;

    cout << "expected: " << expected_operations  << "\nactual: " << actual_operations << endl;
    cout << "\n% difference: " << double(abs(expected_operations - actual_operations)) / expected_operations * 100;
}

int main(){
    time_t t;
    srand(time(&t));

    int length = 100000;
    int lower = 0;
    int upper = 1000000;
    int iterations = 1;

    test_operations_fixed_length(length, lower, upper, iterations);

    return 0;
}

int actual_main(){

    int length = 5;
    int unsorted[] = {5, 4, 3, 2, 1};

    cout << "Original Array: ";
    print_array(unsorted, length);

    insertion_sort(unsorted, length);


    cout << "Sorted Array: ";
    print_array(unsorted, length);


    return 0;
}