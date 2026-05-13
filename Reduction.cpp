Reduction


#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>

using namespace std;

int main()
{
    int n;

    // Input size
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);

    // Input array elements
    cout << "Enter elements:\n";

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Variables for operations
    int sum = 0;

    int minimum = INT_MAX;
    int maximum = INT_MIN;

    double average;

    // Start time
    double start = omp_get_wtime();

    // Parallel Reduction
    #pragma omp parallel for reduction(+:sum) reduction(min:minimum) reduction(max:maximum)
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];

        if (arr[i] < minimum)
            minimum = arr[i];

        if (arr[i] > maximum)
            maximum = arr[i];
    }

    // Calculate average
    average = (double)sum / n;

    // End time
    double end = omp_get_wtime();

    // Output
    cout << "\nSum = " << sum << endl;

    cout << "Minimum = " << minimum << endl;

    cout << "Maximum = " << maximum << endl;

    cout << "Average = " << average << endl;

    cout << "Execution Time = " << end - start << " seconds" << endl;

    return 0;
}