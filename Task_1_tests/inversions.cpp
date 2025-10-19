#include "inversions.h"

long long countInversions(int arr[], int n) {
    long long invCount = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arr[i] > arr[j]) {
                ++invCount;
            }
        }
    }
    return invCount;
}