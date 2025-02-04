#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void kadane(const vector<int>& arr, int& max_sum, int& start, int& end) {
    int current_sum = 0, temp_start = 0;
    max_sum = INT_MIN;

    for (int i = 0; i < arr.size(); i++) {
        current_sum = max(arr[i], current_sum + arr[i]);

        if (current_sum > max_sum) {
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }

        if (current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
}

int main() {
    vector<int> arr1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};

    int max_sum, start, end;
    kadane(arr1, max_sum, start, end);

    cout << "Max subarray sum: " << max_sum << endl;
    cout << "Subarray: [";
    for (int i = start; i <= end; i++) {
        cout << arr1[i];
        if (i < end) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}