#include <iostream>
#include <omp.h>

using namespace std;

void bubble(int *, int);
void swap(int &, int &);

void bubble(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int first = i % 2;
        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b) {
    int test;
    test = a;
    a = b;
    b = test;
}

int main() {
    int *a, n;
    cout << "\nEnter total number of elements: ";
    cin >> n;
    a = new int[n];
    cout << "\nEnter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Before parallel bubble sort
    cout << "\nArray before parallel bubble sort: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    // Parallel bubble sort
    bubble(a, n);

    // After parallel bubble sort
    cout << "\nArray after parallel bubble sort: ";
    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    delete[] a; // Free allocated memory
    return 0;
}
