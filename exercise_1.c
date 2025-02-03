#include <stdio.h>

// Fonction pour effectuer une recherche binaire
int binary_search(int sorted_list[], int size, int target) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2; 

        if (sorted_list[mid] == target) {
            return mid;
        } else if (sorted_list[mid] < target) {
            left = mid + 1; // Recherche dans la moitié droite
        } else {
            right = mid - 1; // Recherche dans la moitié gauche
        }
    }

    return -1;
}

int main() {
    // Liste triée
    int sorted_list[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int size = sizeof(sorted_list) / sizeof(sorted_list[0]);

    // Test 1
    int target = 7;
    int result = binary_search(sorted_list, size, target);
    printf("Test 1: Index de %d -> %d\n", target, result);

    // Test 2
    target = 8;
    result = binary_search(sorted_list, size, target);
    printf("Test 2: Index de %d -> %d\n", target, result);

    // Test 3
    target = 1;
    result = binary_search(sorted_list, size, target);
    printf("Test 3: Index de %d -> %d\n", target, result);

    // Test 4
    target = 15;
    result = binary_search(sorted_list, size, target);
    printf("Test 4: Index de %d -> %d\n", target, result);

    // Test 5
    target = 20;
    result = binary_search(sorted_list, size, target);
    printf("Test 5: Index de %d -> %d\n", target, result);

    return 0;
}