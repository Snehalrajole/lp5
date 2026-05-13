Merge Sort
#include <iostream>
#include <omp.h>

using namespace std;

// Merge Function
void merge(int arr[], int low, int mid, int high)
{
    int temp[100];

    int i = low;
    int j = mid + 1;
    int k = low;

    // Merge two sorted parts
    while (i <= mid && j <= high)
    {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    // Copy remaining elements
    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    // Copy back to original array
    for (int i = low; i <= high; i++)
        arr[i] = temp[i];
}

// Sequential Merge Sort
void sequentialMergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        sequentialMergeSort(arr, low, mid);

        sequentialMergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        // Parallel sections
        #pragma omp parallel sections
        {
            // Left half
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            // Right half
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }

        // Merge sorted halves
        merge(arr, low, mid, high);
    }
}

// Main Function
int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr1[n], arr2[n];

    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr1[i];

        arr2[i] = arr1[i];
    }

    // Sequential Merge Sort
    double start = omp_get_wtime();

    sequentialMergeSort(arr1, 0, n - 1);

    double end = omp_get_wtime();

    cout << "\nSequential Merge Sort:\n";

    for (int i = 0; i < n; i++)
        cout << arr1[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    // Parallel Merge Sort
    start = omp_get_wtime();

    parallelMergeSort(arr2, 0, n - 1);

    end = omp_get_wtime();

    cout << "\nParallel Merge Sort:\n";

    for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return 0;
}