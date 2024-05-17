#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

void swap(struct person *x, struct person *y)
{
    struct person temp = *x;
    *x = *y;
    *y = temp;
}

void heapify_age(struct person arr[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        heapify_age(arr, n, smallest);
    }
}

void build_min_age_heap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_age(arr, n, i);
}

void heapify_weight(struct person arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify_weight(arr, n, largest);
    }
}

void build_max_weight_heap(struct person arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_weight(arr, n, i);
}

int main()
{
    int n, option;
    struct person *people = NULL;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    people = (struct person *)malloc(n * sizeof(struct person));

    if (people == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    FILE *file = fopen("student_data.txt", "r");

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        fscanf(file, "%d %s %d %d %d", &people[i].id, people[i].name, &people[i].age, &people[i].height, &people[i].weight);
    }

    fclose(file);

    do
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
        
            break;
        case 2:
            build_min_age_heap(people, n);
            printf("Min-heap based on age created.\n");
            break;
        case 3:
            build_max_weight_heap(people, n);
            printf("Max-heap based on weight created.\n");
            break;
        case 4:
            printf("Weight of youngest student: %.2f kg\n", (float)people[0].weight / 2.20462);
            break;
        case 5:
            if (n >= 2 * n)
            {
                printf("Heap is full. Cannot insert more students.\n");
                break;
            }
            printf("Enter new student data (Id Name Age Height Weight): ");
            scanf("%d %s %d %d %d", &people[n].id, people[n].name, &people[n].age, &people[n].height, &people[n].weight);
            n++;
            build_min_age_heap(people, n);
            printf("New student inserted into the Min-heap based on age.\n");
            break;
        case 6:
            if (n <= 0)
            {
                printf("Heap is empty. Cannot delete more students.\n");
                break;
            }
            printf("Deleting the oldest student: %s (Age: %d)\n", people[0].name, people[0].age);
            people[0] = people[n - 1];
            n--;
            build_min_age_heap(people, n);
            break;
        case 7:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    } while (option != 7);

    free(people);
    return 0;
}

