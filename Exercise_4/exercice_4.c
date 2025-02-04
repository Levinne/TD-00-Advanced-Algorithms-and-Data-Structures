#include <stdio.h>
#include <stdlib.h>

// 1. Represent the intervals as a list of tuples, where each tuple is (start_time, end_time)

typedef struct {
    int start;
    int end;
} Interval;



// 2. Implement an algorithm to merge overlapping intervals:

int compare(const void *a, const void *b) {
    return ((Interval *)a)->start - ((Interval *)b)->start;
}

// 2. Fonction pour fusionner les intervalles
void merge_intervals(Interval intervals[], int n) {
    // Étape 1 : Trier les intervalles par temps de début
    qsort(intervals, n, sizeof(Interval), compare);

    // Étape 2 : Initialiser un tableau pour stocker les intervalles fusionnés
    Interval merged[n];
    int merged_count = 0;

    for (int i = 0; i < n; i++) {
        // Si merged est vide ou qu'il n'y a pas de chevauchement, ajouter l'intervalle
        if (merged_count == 0 || merged[merged_count - 1].end < intervals[i].start) {
            merged[merged_count++] = intervals[i];
        } else {
            // Il y a chevauchement, donc fusionner les intervalles
            if (merged[merged_count - 1].end < intervals[i].end) {
                merged[merged_count - 1].end = intervals[i].end;
            }
        }
    }

    //3. Return the merged list of intervals.
    printf("Merged intervals: ");
    for (int i = 0; i < merged_count; i++) {
        printf("(%d, %d) ", merged[i].start, merged[i].end);
    }
    printf("\n");
}

int main() {
    // Exemples d'intervalles
    Interval intervals1[] = {{1, 2}, {3, 4}, {5, 6}};
    Interval intervals3[] = {{1, 3}, {2, 4}, {5, 7}, {6, 8}};
    Interval intervals2[] = {{1, 4}, {2, 3}, {3, 5}, {6, 8}};

    printf("Test case 1:\n");
    merge_intervals(intervals1, sizeof(intervals1) / sizeof(intervals1[0]));

    printf("Test case 3:\n");
    merge_intervals(intervals3, sizeof(intervals3) / sizeof(intervals3[0]));

    printf("Test case 4:\n");
    merge_intervals(intervals2, sizeof(intervals2) / sizeof(intervals2[0]));

    return 0;
}