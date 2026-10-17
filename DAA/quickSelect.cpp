#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(vector<int>& A, int low, int high) {
    int pivot = A[high];     // choosing last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[high]);
    return i + 1;             // final position of pivot
}

// Randomized partition: swap a random element into the 'high' position first
int randomizedPartition(vector<int>& A, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(A[randomIndex], A[high]);
    return partition(A, low, high);
}

// k is 0-indexed target rank
int quickSelect(vector<int>& A, int low, int high, int k) {
    if (low == high) return A[low];

    int pivotIndex = randomizedPartition(A, low, high);

    if (k == pivotIndex) {
        return A[pivotIndex];
    } else if (k < pivotIndex) {
        return quickSelect(A, low, pivotIndex - 1, k);
    } else {
        return quickSelect(A, pivotIndex + 1, high, k);
    }
}

int main() {
    srand(time(0));
    vector<int> A = {7, 2, 1, 6, 8, 5, 3, 4};
    int n = A.size();

    int k_smallest = 3;    // find 3rd smallest (1-indexed)
    int result1 = quickSelect(A, 0, n - 1, k_smallest - 1);  // convert to 0-indexed
    cout << k_smallest << "rd smallest element = " << result1 << endl;

    vector<int> B = {7, 2, 1, 6, 8, 5, 3, 4};  // fresh copy since array gets modified
    int k_largest = 3;     // find 3rd largest (1-indexed)
    int result2 = quickSelect(B, 0, n - 1, n - k_largest);   // convert to 0-indexed
    cout << k_largest << "rd largest element = " << result2 << endl;

    return 0;
}