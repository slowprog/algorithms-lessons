#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void printArray(int *a, int size)
{
    for (int i = 0; i < size; i++) {
        printf("%2i ", a[i]);
    }
}

void fillArray(int *a, int size, int isRandom)
{
    for (int i = 0; i < size; i++) {
        a[i] = isRandom ? ((int)rand() % 100) : i;
    }
}

/**
 * Обычная сортировка пузырьком.
 */
void bubbleClassic(int *array, int size)
{
    printf("\nTask 1a: bubble classic\n");
    
    printf("%-16s", "Array: ");
    printArray(array, size);
    printf("\n");
    
    int i;
    int j;
    int count = 0;
    
    for (i = 0; i < size; i++) {
        for (j = 0; j < size - 1; j++) {
            count++;
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
    }
    
    printf("%-16s", "Sorted: ");
    printArray(array, size);
    printf("– hits %d (O(n^2) = %d)\n", count, size * size);
}

/**
 * Сортировка пузырьком оканчивающаяся раньше, если была итерация без перемещений.
 */
void bubbleFast(int *array, int size)
{
    printf("\nTask 1b: bubble fast\n");
    
    printf("%-16s", "Array: ");
    printArray(array, size);
    printf("\n");
    
    int i;
    int j;
    int count = 0;
    int found = 0;
    
    for (i = 0; i < size; i++) {
        found = 0;
        for (j = 0; j < size - 1; j++) {
            count++;
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                found = 1;
            }
        }
        if (!found) {
            break;
        }
    }
    
    printf("%-16s", "Sorted: ");
    printArray(array, size);
    printf("– hits %d (O(n^2) = %d)\n", count, size * size);
}

/**
 * Обычная шейкерная сортировка.
 */
void shakeClassic(int *array, int size)
{
    printf("\nTask 2a: shake classic\n");
    
    printf("%-16s", "Array: ");
    printArray(array, size);
    printf("\n");
    
    int i;
    int j;
    int count = 0;
    
    for (i = 0; i < size; i++) {
        for (j = i; j < size - 1 - i; j++) {
            count++;
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
            }
        }
        
        for (j = size - 1 - i; j > i; j--) {
            count++;
            if (array[j] < array[j - 1]) {
                swap(&array[j], &array[j - 1]);
            }
        }
    }
    
    printf("%-16s", "Sorted: ");
    printArray(array, size);
    printf("– hits %d (O(n^2) = %d)\n", count, size * size);
}

/**
 * Шейкерная сортировка оканчивающаяся раньше, если была итерация без перемещений.
 */
void shakeFast(int *array, int size)
{
    printf("\nTask 2b: shake fast\n");
    
    printf("%-16s", "Array: ");
    printArray(array, size);
    printf("\n");
    
    int i;
    int j;
    int count = 0;
    int found = 0;
    
    for (i = 0; i < size; i++) {
        found = 0;
        for (j = i; j < size - 1 - i; j++) {
            count++;
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                found = 1;
            }
        }
        
        if (!found) {
            break;
        }
        
        for (j = size - 1 - i; j > i; j--) {
            count++;
            if (array[j] < array[j - 1]) {
                swap(&array[j], &array[j - 1]);
                found = 1;
            }
        }
        
        if (!found) {
            break;
        }
    }
    
    printf("%-16s", "Sorted: ");
    printArray(array, size);
    printf("– hits %d (O(n^2) = %d)\n", count, size * size);
}

/**
 * Бинарный поиск в массиве.
 */
void binarySearch(int *array, int size, int needle)
{
    printf("\nTask 3: binary search (range 0..%d) – %d\n", size - 1, needle);
    
    int first = 0;
    int last = size;
    int count = 0;
    int center = last / 2;
    
    while (first < last) {
        count++;
        // 0 1 2 3 4 5 6 7 8 9 10 11 12
        if (array[center] >= needle) {
            last = center;
        } else {
            first = center + 1;
        }
        
        center = first + (last - first) / 2;
    }
    
    if (array[center] == needle) {
        printf("%-16s", "Found: ");
        printf("hits %d\n", count);
    } else {
        printf("%-16s", "Not found: ");
        printf("hits %d\n", count);
    }
}

void sortings()
{
    int size = 13;
    int arrayBuuble[size];
    int arrayBuubleFast[size];
    int arrayShake[size];
    int arrayShakeFast[size];
    
    fillArray(arrayBuuble, size, 1);
    
    memcpy(arrayBuubleFast, arrayBuuble, sizeof(arrayBuuble));
    memcpy(arrayShake, arrayBuuble, sizeof(arrayBuuble));
    memcpy(arrayShakeFast, arrayBuuble, sizeof(arrayBuuble));
    
    bubbleClassic(arrayBuuble, size);
    bubbleFast(arrayBuubleFast, size);
    shakeClassic(arrayShake, size);
    shakeFast(arrayShakeFast, size);
}

void searching()
{
    int size = 100;
    int array[size];
    
    fillArray(array, size, 0);
    
    // Разные варианты искомого, чтобы поглядеть во сколько хитов закончит.
    binarySearch(array, size, array[0]);
    binarySearch(array, size, array[size - 1]);
    binarySearch(array, size, array[size / 2 - 1]);
    binarySearch(array, size, array[size / 2]);
    binarySearch(array, size, array[size / 2 + 1]);
    binarySearch(array, size, size);
}

int main()
{
    srand((int)time(NULL));
    
    sortings();
    searching();
}
