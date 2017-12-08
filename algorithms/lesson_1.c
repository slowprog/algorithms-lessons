#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void automorphicNumbers(void);
void randCustom(void);
void maxThree(void);
void avrPositive(void);
void existsOdd(void);
void divide(void);
void fromSquareToCube(void);
void checkmate(void);
void exchange(void);

//int main(int argc, const char * argv[])
//{
//    srand((int)time(NULL));
//    
//    automorphicNumbers();
//    randCustom();
//    maxThree();
//    avrPositive();
//    existsOdd();
//    divide();
//    fromSquareToCube();
//    checkmate();
//    exchange();
//    
//    return 0;
//}

void exchange()
{
    printf("\nTask 3b: exchange of values without temp var\n");
    
    int a = 42;
    int b = 11;
    
    printf("a = %i, b = %i\n", a, b);
    
    a = a - b;
    b = a + b;
    a = b - a;
    
    printf("a = %i, b = %i\n", a, b);
}

void checkmate()
{
    printf("\nTask 7: check and mats\n");
    
    int x1;
    int y1;
    int x2;
    int y2;
    
    printf("Input x1: ");
    scanf("%i", &x1);
    
    printf("Input y1: ");
    scanf("%i", &y1);
    
    printf("Input x2: ");
    scanf("%i", &x2);
    
    printf("Input y2: ");
    scanf("%i", &y2);
    
    int isOneColor = (((abs(x1 - x2)) % 2) > 0) == (((abs(y1 - y2)) % 2) > 0);
    
    printf("One color? – %s\n", isOneColor ? "Yeap!" : "Nope!");
}

void fromSquareToCube()
{
    printf("\nTask 8: square and cube\n");
    
    int from;
    int to;
    int i;
    
    printf("Input from: ");
    scanf("%i", &from);
    
    printf("Input to: ");
    scanf("%i", &to);
    
    for (i = from; i <= to; i++) {
        printf("Result: %i, %i, %i\n", i, i * i, i * i * i);
    }
}

void divide()
{
    printf("\nTask 9: divide\n");
    
    int dividend;
    int divider;
    int quotient = 0;
    
    printf("Input dividend: ");
    scanf("%i", &dividend);
    
    printf("Input divider: ");
    scanf("%i", &divider);
    
    for (dividend; dividend >= divider; dividend -= divider) {
        quotient++;
    }
    
    printf("Quotient: %i\n", quotient);
    printf("Memainder: %i\n", dividend);
}

void existsOdd()
{
    printf("\nTask 10: exists odd numbers\n");
    
    int number;
    int part;
    
    printf("Input number: ");
    scanf("%i", &number);
    
    for (part = number; part != 0; part /= 10) {
        if (part % 2 != 0) {
            printf("True\n");
            
            return;
        }
    }
    
    printf("False\n");
}

void avrPositive()
{
    printf("\nTask 11: average of positive with 8\n");
    
    int count  = 0;
    double avr = 0;
    
    int number;
    
    do {
        printf("Input number (0 to end): ");
        scanf("%i", &number);
        
        if (number > 0 && number % 10 == 8) {
            avr += number;
            count++;
            printf("– check!\n");
        }
    } while(number != 0);
    
    printf("Avr: %f\n", avr / count);
}

void maxThree()
{
    printf("\nTask 12: max number\n");
    
    int size = 3;
    int i;
    int max;
    int arrayNumbers[size];
    
    printf("Array: ");
    for (i = 0; i < size; i++) {
        arrayNumbers[i] = (int)rand() % 100;
        
        printf("%i ", arrayNumbers[i]);
    }
    
    max = arrayNumbers[0];
    
    for (i = 1; i < size; i++) {
        if (arrayNumbers[i] > max) {
            max = arrayNumbers[i];
        }
    }
    
    printf("Max: %i\n", max);
}

void randCustom()
{
    printf("\nTask 13: rand\n");
    
    int from    = 1;
    int to      = 100;
    int randNum = rand() % to + from;
    
    printf("Rand stdlib: %i\n", randNum);
    
    int a = 494;
    int b = 2230;
    
    // В нормальном генераторе я бы запоминал последнее сгенерированное
    // число и подставлял бы его в расчёты, но тут возьму из randNum.
    randNum = (a * randNum + b) % to + from;
    
    printf("Rand custom: %d\n", randNum);
}

void automorphicNumbers()
{
    printf("Task 14: automorphic numbers\n");
    
    int number;
    int divider;
    
    printf("Input number: ");
    scanf("%i", &number);
    
    for (int i = 0; i <= number; i++) {
        // Проверка на ноль – костыль, для оптимизации может быть уместно
        // вынести вывод 0 перед цеиклом (вручную), и вырезать проверку.
        divider = pow(10, (int)(log10(i == 0 ? 1 : i) + 1));
        
        if ((i * i) % divider == i) {
            printf("%d ", i);
        }
    }
}
