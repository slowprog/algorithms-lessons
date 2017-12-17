#include <stdio.h>
#include <malloc/malloc.h>
#include <stdlib.h>
#include <string.h>

#define T char
#define MaxSize 100

// Опишем структуру узла списка
struct TNode
{
    T value;
    struct TNode *next;
};
typedef struct TNode Node;

struct Stack
{
    Node *head;
    int size;
    int maxSize;
};
struct Stack Stack;

int push(T value)
{
    if (Stack.size >= Stack.maxSize) {
        printf("Error stack size");

        return 0;
    }
    
    Node *tmp = (Node*) malloc(sizeof(Node));
    
    if (tmp == NULL) {
        printf("Не получилось выделить память\n");
        
        return 0;
    }
    
    tmp->value = value;
    tmp->next = Stack.head;
    Stack.head = tmp;
    Stack.size++;
    
    return 1;
}

T pop() {
    if (Stack.size == 0) {
        return '\0';
    }
    // Временный указатель на голову чтобы удалить потом
    Node* next = Stack.head;
    // Значение "наверху" списка
    T value = Stack.head->value;
    // Перемещаем голову вниз
    Stack.head = Stack.head->next;
    // Запись, на которую указывала голова удаляем, освобождая память
    free(next);
    Stack.size--;
    // Возвращаем значение, которое было в голове
    return value;
}

T get() {
    if (Stack.size == 0) {
        return '\0';
    }
    
    return Stack.head->value;
}

void printStack()
{
    Node *current = Stack.head;
    while(current != NULL)
    {
        printf("%c ", current->value);
        current = current->next;
    }
    printf("\n");
}

void clearStack()
{
    while(Stack.size != 0) {
        pop();
    }
}

char* convert(int number)
{
    while (number > 1) {
        push(number % 2 == 0 ? '0' : '1');
        number /= 2;
    }
    
    push(number == 0 ? '0' : '1');
    
    char string[MaxSize] = "";
    char part;
    
    while(Stack.size != 0) {
        part = pop();
        strcat(string, &part);
    }
    
    return strdup(string);
}

void convertTask1()
{
    printf("Task 1: перевод из 10-ой в 2-ую систему счисления с помощью стека\n");
    
    printf("Переводим %d в бинарное отображение: %s\n", 1, convert(1));
    printf("Переводим %d в бинарное отображение: %s\n", 106, convert(106));
    printf("Переводим %d в бинарное отображение: %s\n", 7492, convert(7492));
}

/**
 * Проверяет наличие элемента в массиве, если нет, то вернёт -1,
 * иначе номериндекс элемента в массиве.
 */
int searchArray(int val, int *arr, int size){
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) {
            return i;
        }
    }
    
    return -1;
}

int checkBrackets(char* string)
{
    clearStack();
    
    int index;
    const int size = 4;
    int open[size] = {'{', '[', '<', '('};
    int close[size] = {'}', ']', '>', ')'};
    
    for (int i = 0; string[i] != '\0'; i++){
        if (searchArray(string[i], open, size) != -1) {
            push(string[i]);
        } else if (searchArray(string[i], close, size) != -1) {
            index = searchArray(pop(), open, size);
            if (string[i] != close[index]) {
                return 0;
            }
        }
    }
    
    return 1;
}

void bracketsTask3()
{
    printf("\nTask 3: проверка валидности скобок\n");
    
    printf("Проверяем строку %s: %s\n", "([{}])", checkBrackets("([{}])") ? "валидно" : "невалидно");
    printf("Проверяем строку %s: %s\n", "([{])", checkBrackets("([{})") ? "валидно" : "невалидно");
    printf("Проверяем строку %s: %s\n", " [2/{5*(4+7)}]", checkBrackets("[2/{5*(4+7)}]") ? "валидно" : "невалидно");
    printf("Проверяем строку %s: %s\n", "(1 - 1) * 2", checkBrackets("(1 - 1) * 2") ? "валидно" : "невалидно");
    printf("Проверяем строку %s: %s\n", "(1 - 1) * 2)", checkBrackets("(1 - 1) * 2)") ? "валидно" : "невалидно");
    
}

/**
 * Перевод инфиксной записи в постфиксную с условием, что все элементы
 * разбиты проблеами, и даже скобки должны ими отделяться. А все операции односимвольные.
 */
char* convertInfToPost(char input[])
{
    char output[MaxSize] = "";
    char *string;
    char *array[20] = {0};
    char *part;
    char first;
    int number = 0;
    int inc = 0;
    int end = 0;
    char current;
    
    string = strdup(input);
    
    // Разбиваем строку по пробелам.
    while((part = strsep(&string, " ")) != NULL) {
        array[inc++] = strdup(part);
    }
    
    number = inc;
    inc = 0;
    
    while (!end) {
        // Получаем текущее значение с верха стека.
        first = get();
        part = array[inc];
        // Костыльный выход т.к. нормальные значения в массиве закончились
        if (part != '\0') {
            current = part[0];
        } else {
            current = '\0';
        }
        // Если это не цифра, то обрабатываем операцию
        if ((part == '\0' || atoi(part) == 0) && current != '0') {
            switch(current) {
                case '+':
                case '-':
                    if (first == '\0' || first == '(') {
                        push(current);
                        inc++;
                    } else if (first == '+' || first == '-' || first == '*' || first == '/') {
                        pop();
                        strcat(output, &first);
                        output[strlen(output)] = '\0';
                        strcat(output, " ");
                        output[strlen(output)] = '\0';
                    }
                    break;
                    
                case '*':
                case '/':
                    if (first == '\0' || first == '(' || first == '+' || first == '-') {
                        push(current);
                        inc++;
                    } else if (first == '*' || first == '/') {
                        pop();
                        strcat(output, &first);
                        output[strlen(output)] = '\0';
                        strcat(output, " ");
                        output[strlen(output)] = '\0';
                    }
                    break;
                    
                case '(':
                    push(current);
                    inc++;
                    break;
                    
                case ')':
                    if (first == '\0') {
                        return "Ошибка с закрывающей скобкой!";
                    } else if (first == '+' || first == '-' || first == '*' || first == '/') {
                        pop();
                        // Супер-костыль т.к. копировался мусор и я без понятия почему!
                        unsigned long len = strlen(output);
                        strcat(output, &first);
                        output[len + 1] = 0;
                        strcat(output, " ");
                    } else if (first == '(') {
                        pop();
                        inc++;
                    }
                    break;
                    
                case '\0':
                    if (first == '\0') {
                        end = 1;
                    } else if (first == '+' || first == '-' || first == '*' || first == '/') {
                        pop();
                        strcat(output, &first);
                        output[strlen(output)] = '\0';
                        strcat(output, " ");
                        output[strlen(output)] = '\0';
                    } else if (first == '(') {
                        return "Открывающая скобка не на своём месте";
                    }
                    break;
                    
                default:
                    return "Неизвестный символ!";
            }
        } else {
            // Цифру ложим в выходной массив
            strcat(output, part);
            strcat(output, " ");
            inc++;
        }
    }
    
    return strdup(output);
}


void infToPostTask5()
{
    printf("\nTask 5: перевод инфиксной записи в постфиксную\n");
    
    printf("Переводим строку %s = %s\n", "11 + 3 / 5", convertInfToPost("11 + 3 / 5"));
    printf("Переводим строку %s = %s\n", "( 11 + 3 ) / 5", convertInfToPost("( 11 + 3 ) / 5"));
    printf("Переводим строку %s = %s\n", "( 11 + ( 3 - 1 ) ) / 5", convertInfToPost("( 11 + ( 3 - 1 ) ) / 5"));
    printf("Переводим строку %s = %s\n", "( 11 + ( 3 - 1 ) / 5", convertInfToPost("( 11 + ( 3 - 1 ) / 5"));
    printf("Переводим строку %s = %s\n", "11 + ( 3 - 1 ) ) / 5", convertInfToPost("11 + ( 3 - 1 ) ) / 5"));
    printf("Переводим строку %s = %s\n", "11 + ( 3 - 1 ) 5", convertInfToPost("11 + ( 3 - 1 ) 5"));
}

int main()
{
    Stack.maxSize = MaxSize;
    Stack.head = NULL;
    
    convertTask1();
    bracketsTask3();
    infToPostTask5();
    
    return 0;
}
