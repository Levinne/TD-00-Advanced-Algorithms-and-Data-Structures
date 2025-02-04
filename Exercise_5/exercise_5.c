#include <stdio.h>
#include <limits.h>

// Function to implement Kadane's Algorithm and find the subarray
void kadane(int arr[], int n, int *max_sum, int *start, int *end) {
    int current_sum = 0;    // Initialize current sum
    *max_sum = INT_MIN;     // Initialize to smallest possible integer
    int temp_start = 0;     // Temporary start index for current subarray

    for (int i = 0; i < n; i++) {
        current_sum += arr[i];  // Add current element to current sum

        if (current_sum > *max_sum) {
            *max_sum = current_sum;  // Update max sum if current is greater
            *start = temp_start;      // Update start index
            *end = i;                 // Update end index
        }

        if (current_sum < 0) {
            current_sum = 0;  // Reset current sum if it becomes negative
            temp_start = i + 1; // Move start to the next index
        }
    }
}

int main() {
    int arr1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    
    int max_sum, start, end;
    kadane(arr1, n1, &max_sum, &start, &end);

    printf("Max subarray sum: %d\n", max_sum);
    printf("Subarray: [");
    for (int i = start; i <= end; i++) {
        printf("%d", arr1[i]);
        if (i < end) printf(", ");
    }
    printf("]\n");

    return 0;
}