#include <stdio.h>
#include <stdlib.h>

// Struct to represent an item
typedef struct {
    int value;
    int weight;
} Item;


int knapsack(Item items[], int n, int max_weight) {
    int dp[n + 1][max_weight + 1];

    // Initiation de la table de DP
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= max_weight; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case: no items or no weight capacity
            } else if (items[i - 1].weight <= w) {
                // If the current item can fit, choose the maximum between including or excluding it
                dp[i][w] = (dp[i - 1][w] > dp[i - 1][w - items[i - 1].weight] + items[i - 1].value)
                               ? dp[i - 1][w]
                               : dp[i - 1][w - items[i - 1].weight] + items[i - 1].value;
            } else {
                // If the current item cannot fit, exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    // La valeur maximale
    return dp[n][max_weight];
}


// Fonction pour déterminer les articles inclus
void findIncludedItems(Item items[], int n, int max_weight, int dp[n + 1][max_weight + 1]) {
    int w = max_weight;
    printf("Included items:\n");
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            // Item i was included
            printf("Item with value %d and weight %d\n", items[i - 1].value, items[i - 1].weight);
            w -= items[i - 1].weight; // Réduire le poids restant
        }
    }
}


int main() {
    // Test case 1
    Item items1[] = {{60, 10}, {100, 20}, {120, 30}};
    int n1 = sizeof(items1) / sizeof(items1[0]);
    int max_weight1 = 50;

    int dp1[n1 + 1][max_weight1 + 1];
    int max_value1 = knapsack(items1, n1, max_weight1);
    printf("Maximum value: %d\n", max_value1);
    findIncludedItems(items1, n1, max_weight1, dp1);

    return 0;
}