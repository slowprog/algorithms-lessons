#include <stdio.h>
#include <string.h>
#include <malloc/malloc.h>
#include "queue.c"

int size = 1;

int** readFromFile()
{
    int** matrix;
    char* filename = "/Users/SlowProg/Dropbox/www/algorithms-lessons/matrix";
    
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Can't open file %s!", filename);
        exit(1);
    }
    fscanf(file, "%d", &size); // Считываем размер матрицы
    
    // Выделение памяти под указатели на строки
    matrix = (int**)malloc(size * sizeof(int*));
    
    for (int i = 0; i < size; i++) {
        // Выделение памяти под хранение строк
        matrix[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    fclose(file);
    
    return matrix;
}

void printMatrix(int** matrix)
{
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d", matrix[i][j]);
        }
        
        printf("\n");
    }
}

void walkInDepth(int** matrix, int x)
{
    for (int y = x; y < size; y++) {
        if (matrix[x][y] != 0) {
            printf("(%d, %d) ", x, y);
            
            if (x != y) {
                walkInDepth(matrix, y);
            }
        }
    }
}

void walkInWidth(int** matrix)
{
    TQueue queue = {NULL, NULL};
    int leafs[size];
    memset(leafs, 0, size * sizeof(int));
    Push(&queue, 0);
    
    do {
        int value = Pop(&queue);
        if (leafs[value] != 1) {
            printf("%d ", value);
            for (int i = 0; i < size; i++) {
                if (matrix[value][i] != 0) {
                    Push(&queue, i);
                }
            }
            leafs[value] = 1;
        }
    } while (!IsEmpty(&queue));
    
    printf("\n");
}

int main()
{
    // Задача 1 – чтение графа из файла
    int** matrix = readFromFile();
    
    printf("Считанная матрица из файла:\n");
    printMatrix(matrix);
    
    // Задача 2 – проход графа в глубину с помщью рекрсии
    printf("\nОбход матрицы смежности в глубину:\n");
    walkInDepth(matrix, 0);
    
    // Задача 3 – проход графа в ширину с помщью очереди
    printf("\n\nОбход матрицы смежности в ширину:\n");
    walkInWidth(matrix);
}
