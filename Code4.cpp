#include <stdio.h>
#include <stdlib.h>

// Define a structure for an item
struct Item {
    int item_id;
    float item_profit;
    float item_weight;
    float profit_weight_ratio;
};

// Function to perform heapify operation
void maxHeapify(struct Item arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i) {
        struct Item temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        maxHeapify(arr, n, largest);
    }
}

// Function to perform heap sort
void heapSort(struct Item arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        struct Item temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        maxHeapify(arr, i, 0);
    }
}

// Function to solve fractional knapsack
void fractionalKnapsack(struct Item items[], int n, float capacity) {
    heapSort(items, n);

    float *result = (float *)malloc(n * sizeof(float));
    float totalProfit = 0.0;
    float currentWeight = 0.0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].item_weight <= capacity) {
            result[i] = 1.0;
            currentWeight += items[i].item_weight;
            totalProfit += items[i].item_profit;
        } else {
            result[i] = (capacity - currentWeight) / items[i].item_weight;
            totalProfit += result[i] * items[i].item_profit;
            break;
        }
    }

    printf("Item No profit Weight Amount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d %.6f %.6f %.6f\n", items[i].item_id, items[i].item_profit, items[i].item_weight, result[i]);
    }

    printf("Total Profit: %.6f\n", totalProfit);
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    struct Item *items = (struct Item *)malloc(n * sizeof(struct Item));

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i + 1);
        scanf("%f %f", &items[i].item_profit, &items[i].item_weight);
        items[i].item_id = i + 1;
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    fractionalKnapsack(items, n, capacity);

    free(items);

    return 0;
}

