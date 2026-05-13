Bubble Sort


#include <iostream>
#include <omp.h>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // Even phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }

        // Odd phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

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

    // Sequential
    double start = omp_get_wtime();

    sequentialBubbleSort(arr1, n);

    double end = omp_get_wtime();

    cout << "\nSequential Bubble Sort:\n";

    for (int i = 0; i < n; i++)
        cout << arr1[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    // Parallel
    start = omp_get_wtime();

    parallelBubbleSort(arr2, n);

    end = omp_get_wtime();

    cout << "\nParallel Bubble Sort:\n";

    for (int i = 0; i < n; i++)
        cout << arr2[i] << " ";

    cout << "\nTime: " << end - start << " sec\n";

    return 0;
}