#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int arr[], int n, int i);
void heap_sort(int arr[], int n);
void generate_and_sort_large_dataset(int size);

int main() {
    // Specify the size of the dataset (adjust as needed)
    int dataset_size = 500000;

    // Generate, shuffle, and sort the large dataset using heapsort
    generate_and_sort_large_dataset(dataset_size);

    return 0;
}

void generate_and_sort_large_dataset(int size) {
    // Generate a large dataset of random integers
    int* array = (int*)malloc(size * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000000;
    }

    // Shuffle the sequence of values
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }

    // Repeat the sorting process to get a more accurate execution time
    int num_repeats = 10;
    clock_t total_time = 0;

    for (int repeat = 0; repeat < num_repeats; repeat++) {
        clock_t start_time = clock();

        // Sort the array using heapsort
        heap_sort(array, size);

        clock_t end_time = clock();
        total_time += end_time - start_time;
    }

    double average_time = ((double)total_time) / (num_repeats * CLOCKS_PER_SEC);

    printf("Generated and sorted %d values using heapsort in average time: %.6f seconds\n", size, average_time);

    // Free dynamically allocated memory
    free(array);
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heap_sort(int arr[], int n) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // One by one extract an element from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
