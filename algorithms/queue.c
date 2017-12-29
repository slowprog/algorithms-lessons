//
//  queue.c
//  algorithms
//
//  Created by SlowProg on 28.12.2017.
//  Copyright © 2017 SlowProg. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include <limits.h>

typedef struct node_t    // Узел
{
    int value;           // Само значение
    struct node_t* next; // Указатель на следующий элемент
}   TNode;

typedef struct queue_t   // Очередь
{
    TNode* head;         // Вершина очереди
    TNode* tail;         // Хвост
}   TQueue;

//-----------------------------------------------------------------------------
// Функция добавления элемента в очередь
TQueue* Push(TQueue* queue, int value)
{
    // Создание нового узла
    TNode* node = malloc(sizeof(TNode));
    // Присваиваем значение новому узлу
    node->value = value;
    // Т.к. элемент добавляется в хвост, то указатель
    // на следующий элемент ни на что не ссылается
    node->next = NULL;
    
    // Если очередь не пуста, то ...
    if (queue->head && queue->tail)
    {
        // Хвостовой элемент теперь ссылается на
        // созданный узел
        queue->tail->next = node;
        // Созданный узел становится хвостом
        queue->tail = node;
    }
    else
    {
        // О-о-о... Первый элемент, теперь он и
        // вершина и хвост
        queue->head = queue->tail = node;
    }
    
    return queue;
}
//-----------------------------------------------------------------------------
// Извлечение элемента из очереди
int Pop(TQueue* queue)
{
    int value = 0;
    TNode* node;
    
    // Пока есть элементы в очереди
    if (queue->head)
    {
        // Сохраняем указатель на удаляемый элемент
        node = queue->head;
        // Сохраняем значение удаляемого элемента
        value = node->value;
        // Вершиной очереди становится следующий за удаляемым элемент
        queue->head = queue->head->next;
        // Окончательно удаляем элемент
        free(node);
    }
    
    return value;
}
//-----------------------------------------------------------------------------
// Функция полной очистки очереди
void Clear(TQueue* queue)
{
    // Пока есть хотя бы один элемент
    while (queue->head)
    {
        // Извлекаем очередной элемент
        Pop(queue);
    }
    
    queue->head = queue->tail = NULL;
}
//-----------------------------------------------------------------------------
// Функция полной очистки очереди
int IsEmpty(TQueue* queue)
{
    return queue->head ? 0 : 1;
}
//-----------------------------------------------------------------------------
// Вывод всех элементов на дисплей
void Print(const TQueue* queue)
{
    const TNode* node = queue->head;
    
    // Перебираем все элементы и выводим их на дисплей
    for (; node; node = node->next)
    {
        printf("%d ", node->value);
    }
    printf("\n");
}
