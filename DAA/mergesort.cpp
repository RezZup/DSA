#include <iostream>
#include <vector>
using namespace std;

// Merge two sorted subarrays A[left..mid] and A[mid+1..right]
void merge(vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int j = 0; j < n2; j++) R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Merge L and R back into A[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {      // <= ensures stability
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements, if any
    while (i < n1) { A[k] = L[i]; i++; k++; }
    while (j < n2) { A[k] = R[j]; j++; k++; }
}

void mergeSort(vector<int>& A, int left, int right) {
    if (left >= right) return;      // base case: 0 or 1 element

    int mid = left + (right - left) / 2;   // avoids overflow vs (left+right)/2
    mergeSort(A, left, mid);
    mergeSort(A, mid + 1, right);
    merge(A, left, mid, right);
}

int main() {
    vector<int> A = {38, 27, 43, 10};

    cout << "Before sorting: ";
    for (int x : A) cout << x << " ";
    cout << endl;

    mergeSort(A, 0, A.size() - 1);

    cout << "After sorting: ";
    for (int x : A) cout << x << " ";
    cout << endl;

    return 0;
}