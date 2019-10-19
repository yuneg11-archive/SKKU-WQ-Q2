#include <stdio.h>
#include <string.h>

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

#define MAX_FLOAT_LEN 56
#define MAX_RESULT_LEN 64
#define MAX_RECURR_LEN 9

#define TYPE_ERROR    0
#define TYPE_FINITE   1
#define TYPE_INFINITE 2

int calculate_division(int numerator, int denominator, char *result) {
    int nth_numerator[MAX_FLOAT_LEN];

    if (numerator >= denominator || numerator * 10 < denominator) {
        if (numerator == denominator) {
            result[0] = '1';
            result[1] = '\0';
            return TYPE_FINITE;
        } else {
            result[0] = '\0';
            return TYPE_ERROR;
        }
    } else {
        result[0] = '0';
        result[1] = '.';
    }

    for (int i = 0; i < MAX_FLOAT_LEN; i++) {
        if (numerator == 0) {
            result[i + 2] = '\0';
            return TYPE_FINITE;
        } else {
            for (int j = MAX(0, i - MAX_RECURR_LEN); j < i; j++) {
                if (nth_numerator[j] == numerator) {
                    for (int k = i; k > j; k--) {
                        result[k + 2] = result[k + 1];
                    }
                    result[j + 2] = '[';
                    result[i + 3] = ']';
                    result[i + 4] = '\0';
                    return TYPE_INFINITE;
                }
            }
        }

        nth_numerator[i] = numerator;
        result[i + 2] = ((numerator * 10) / denominator) + '0';
        numerator = (numerator * 10) % denominator;
    }

    result[MAX_FLOAT_LEN + 2] = '\0';
    return TYPE_INFINITE;
}

int main(int argc, char *argv[]) {
    printf("To stop the program, press [Ctrl + D]\n");

    while (1) {
        int numerator, denominator;
        char result[MAX_RESULT_LEN];
        int type;

        printf("\n");

        printf("Input Numerator Number: ");
        if (scanf("%d", &numerator) == EOF) {
            break;
        }

        printf("Input Denominator Number: ");
        if (scanf("%d", &denominator) == EOF) {
            break;
        }

        type = calculate_division(numerator, denominator, result);

        if (type == TYPE_FINITE || type == TYPE_INFINITE) {
            printf("The Result:: %s Number: %s\n", type == TYPE_FINITE ? "Finite" : "Infinite", result);
        } else {
            printf("The Range of \"Numerator / Denominator\" is not from 0.1 to 1\n");
        }
    }

    printf("\n");

    return 0;
}
