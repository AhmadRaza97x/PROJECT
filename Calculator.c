#include <stdio.h>
#include <stdlib.h>

void calculator() 
{
    double num1, num2, result;
    char operator;

    while (1) 
    {
        printf("\nENTER OPERATION (+, -, *, /) or 'q' == EXIT : ");
        scanf(" %c", &operator);

        if (operator == 'q') 
        {
            printf("\nEXIT..\n");
            break;
        }
        printf("\nENTER NO. 1 : ");
        scanf("%lf", &num1);

        printf("\nENTER NO. 2 : ");
        scanf("%lf", &num2);

        switch (operator) 
        {
            case '+': result = num1 + num2; break;
            case '-': result = num1 - num2; break;
            case '*': result = num1 * num2; break;
            case '/':
                if (num2 == 0) {
                    printf("\nERROR ! ..DIVISION BY 0 NOT ALLOWED \n");
                    continue;
                }
                result = num1 / num2;
                break;
            default:
                printf("\nOPERATION NOT FOUND\n");
                continue;
        }
        printf("\nRESULT : %.2lf\n\n", result);
    }
}

int main() {
    calculator();
    return 0;
}

