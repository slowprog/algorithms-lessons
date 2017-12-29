//
//  main.c
//  algorithms
//
//  Created by SlowProg on 22.12.2017.
//  Copyright © 2017 SlowProg. All rights reserved.
//

#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <string.h>

int hash(char *str)
{
    int hash = 1;
    int c;
    
    while (c = *str++) {
        hash += hash ^ c * 5;
    }
    
    return hash;
}

void hashTask1()
{
    printf("Задача 1: простейшая хеш-функция\n");
    
    printf("Преобразовываем строку %10s: %i\n", "a", hash("a"));
    printf("Преобразовываем строку %10s: %i\n", "b", hash("b"));
    printf("Преобразовываем строку %10s: %i\n", "aaaaa", hash("aaaaa"));
    printf("Преобразовываем строку %10s: %i\n", "aaaab", hash("aaaab"));
    printf("Преобразовываем строку %10s: %i\n", "adbjmccsf", hash("adbjmccsf"));
    printf("Преобразовываем строку %10s: %i\n", "11111", hash("11111"));
    printf("Преобразовываем строку %10s: %i\n", "12345", hash("12345"));
}

typedef int T;
typedef struct Node {
    T data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

// Распечатка двоичного дерева в виде скобочной записи
void printTree(Node *root) {
    if (root)
    {
        printf("%d",root->data);
        if (root->left || root->right)
        {
            printf("(");
            
            if (root->left)
                printTree(root->left);
            else
                printf("NULL");
            printf(",");
            
            if (root->right)
                printTree(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

// Создание нового узла
Node* getFreeNode(T value, Node *parent) {
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

// Вставка узла
void insert(Node **head, int value) {
    Node *tmp = NULL;
    if (*head == NULL)
    {
        *head = getFreeNode(value, NULL);
        return;
    }
    
    tmp = *head;
    while (tmp)
    {
        if (value> tmp->data)
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }
        else if (value< tmp->data)
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
        else
        {
            exit(2);// дерево построено неправильно
        }
    }
}

/**
 * КЛП - “корень-левый-правый” (обход в прямом порядке, pre-order)
 */
void preOrderTravers(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

/**
 * ЛКП - “левый - корень - правый” (симметричный обход, in-order)
 */
void inOrderTravers(Node* root) {
    if (root) {
        preOrderTravers(root->left);
        printf("%d ", root->data);
        preOrderTravers(root->right);
    }
}

/**
 * ЛПК - “левый - правый - корень” (обход в обратном порядке, post-order)
 */
void postOrderTravers(Node* root) {
    if (root) {
        preOrderTravers(root->left);
        preOrderTravers(root->right);
        printf("%d ", root->data);
    }
}

/**
 * Поиск по дереву с помощью КЛП
 */
int searchTree(Node* root, int needle) {
    if (root) {
        if (needle == root->data) {
            return 1;
        }
        return searchTree(root->left, needle);
        return searchTree(root->right, needle);
    }
    
    return 0;
}

int bitreeTask2()
{
    printf("\nЗадача 2: доработка работы с бинарным деревом\n");
    
    Node *Tree = NULL;
    
    char filename[256] = "";
    int traverseType;
    
    printf("Введите название файла для подгрузки дерева: ");
    scanf("%s", filename);
    
    printf("Укажите желаемый тип обхода [0 - все, 1 – КЛП, 2 – ЛКП, 3 – ЛПК]: ");
    scanf("%i", &traverseType);
    
    FILE* file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Can't open file %s!", filename);
        exit(1);
    }
    int count;
    fscanf(file, "%d", &count); // Считываем количество записей
    
    for (int i = 0; i < count; i++) {
        int value;
        fscanf(file, "%d", &value);
        insert(&Tree, value);
    }
    fclose(file);
    
    printf("Дерево: ");
    printTree(Tree);
    
    if (!traverseType || traverseType == 1) {
        printf("\nОбходи дерева КЛП: ");
        preOrderTravers(Tree);
    }
    
    if (!traverseType || traverseType == 2) {
        printf("\nОбходи дерева ЛКП: ");
        inOrderTravers(Tree);
    }
    
    if (!traverseType || traverseType == 3) {
        printf("\nОбходи дерева ЛПК: ");
        postOrderTravers(Tree);
    }
    
    printf("\nПоиск в дереве %i: %s\n", 3, searchTree(Tree, 3) ? "есть" : "нет");
    printf("Поиск в дереве %i: %s\n", 4, searchTree(Tree, 4) ? "есть" : "нет");
    printf("Поиск в дереве %i: %s\n", 5, searchTree(Tree, 5) ? "есть" : "нет");
    printf("Поиск в дереве %i: %s\n", 9, searchTree(Tree, 9) ? "есть" : "нет");
    
    return 0;
}

//int main()
//{
//    hashTask1();
//    bitreeTask2();
//}


