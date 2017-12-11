#include <stdio.h>
#include <string.h>

int calculateRec(int from, int to);
int calculateArr(int from, int to);
void calculateTask3(void);
char* convert(int number);
void convertTask1(void);
int powRec(int number, int pow);
void powerTask2(void);
int powEven(int number, int pow);
int powArr(int number, int pow);

//int main(int argc, const char * argv[])
//{
//    convertTask1();
//    powerTask2();
//    calculateTask3();
//}

void convertTask1()
{
    printf("Task 1: convert\n");
    
    printf("%d to bin: %s\n", 1, convert(1));
    printf("%d to bin: %s\n", 106, convert(106));
    printf("%d to bin: %s\n", 7492, convert(7492));
}

char* convert(int number)
{
    char string[100] = "";
    
    if (number > 1) {
        strcpy(string, convert(number / 2));
    }
    
    return strcat(string, number % 2 == 0 ? "0" : "1");
}

void powerTask2()
{
    printf("\nTask 2: power\n");
    
    printf("Arr power %d to %d: %d\n", 4, 3, powArr(4, 3));
    printf("Rec power %d to %d: %d\n", 4, 3, powRec(4, 3));
    printf("Even power %d to %d: %d\n", 4, 3, powEven(4, 3));
    printf("---\n");
    printf("Arr power %d to %d: %d\n", 5, 4, powArr(5, 4));
    printf("Rec power %d to %d: %d\n", 5, 4, powRec(5, 4));
    printf("Even power %d to %d: %d\n", 5, 4, powEven(5, 4));
}

int powArr(int number, int pow)
{
    if (pow == 0) {
        return 1;
    }
    
    int result = number;
    
    for (int i = 0; i < pow - 1; i++) {
        result *= number;
    }
    
    return result;
}

int powRec(int number, int pow)
{
    if (pow == 0) {
        return 1;
    }
    
    if (pow > 1) {
        return number * powRec(number, pow - 1);
    }
    
    return number;
}

int powEven(int number, int pow)
{
    if (pow == 0) {
        return 1;
    }
    
    if (pow > 1) {
        if (pow % 2 == 0) {
            return powRec(number * number, pow / 2);
        } else {
            return number * powRec(number * number, pow / 2);
        }
    }
    
    return number;
}

void calculateTask3()
{
    printf("\nTask 3: calculate\n");
    
    printf("from %d to %d: %d\n", 1, 1, calculateRec(1, 1));
    printf("from %d to %d: %d\n", 1, 4, calculateRec(1, 4));
    printf("from %d to %d: %d\n", 3, 20, calculateRec(3, 20));
    
//    printf("from %d to %d: %d\n", 1, 1, calculateArray(1, 1));
//    printf("from %d to %d: %d\n", 1, 4, calculateArray(1, 4));
//    printf("from %d to %d: %d\n", 3, 20, calculateArray(3, 20));
}

//       1
//      / \
//     2   2
//    /|   |\
//   3 4   3 4
//  / \   / \
// 4   6 4   6
int calculateRec(int from, int to)
{
    if (from == to) {
        return 1;
    } else if (from > to) {
        return 0;
    }
    
    return calculateRec(from + 1, to) + calculateRec(from * 2, to);
}

int calculateArray(int from, int to)
{
    int count = 0;

    for (int i = from; i <= to; i++) {
        if (i == to) {
            count++;
        } else if (i * 2 == to) {
            count++;
        }
    }
    
    for (int i = from; i <= to; i *= 2) {
        if (i == to) {
            count++;
        } else if (i + 1 == to) {
            count++;
        }
    }

    return count;
}

