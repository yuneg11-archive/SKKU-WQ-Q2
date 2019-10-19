#include <stdio.h>
#include <string.h>

#define MAX_FLOAT_LEN 120
#define MAX_RESULT_LEN 128

#define IO_CONSOLE 1
#define IO_FILE    2

#define TYPE_ERROR    0
#define TYPE_FINITE   1
#define TYPE_INFINITE 2

int calculate_division(int numerator, int denominator, char *result) {
    int nth_numerator[MAX_FLOAT_LEN];
    int i, j, k;

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

    for (i = 0; i < MAX_FLOAT_LEN; i++) {
        nth_numerator[i] = numerator;
        
        if (numerator == 0) {
            result[i + 2] = '\0';
            return TYPE_FINITE;
        } else {
            for (j = 0; j < i; j++) {
                if (nth_numerator[j] == numerator) {
                    for (k = i; k > j; k--) {
                        result[k + 2] = result[k + 1];
                    }
                    result[j + 2] = '[';
                    result[i + 3] = ']';
                    result[i + 4] = '\0';
                    return TYPE_INFINITE;
                }
            }
        }

        result[i + 2] = ((numerator * 10) / denominator) + '0';
        numerator = (numerator * 10) % denominator;
    }

    result[i+2] = '\0';
    return TYPE_INFINITE;
}

int main(int argc, char *argv[]) {
    FILE *fin, *fout;
    short mode = 0;

    if (argc == 1) {
        mode = IO_CONSOLE;
        printf("To stop the program, press [Ctrl + D]\n");
    } else if (argc <= 3) {
        mode = IO_FILE;
        fin = fopen(argv[1], "r");
        if (argc == 3) {
            fout = fopen(argv[2], "w");
        } else {
            fout = fopen("output.txt", "w");
        }
    } else if (argc > 3) {
        printf("Usage: RecurringDecimal [input_file [, output_file]]");
        return -1;
    }

    while (1) {
        int numerator, denominator;
        char result[MAX_RESULT_LEN];
        int type;

        if (mode == IO_CONSOLE) {
            printf("\n");

            printf("Input Numerator Number: ");
            if (scanf("%d", &numerator) == EOF) {
                printf("\n");
                return 0;
            }

            printf("Input Denominator Number: ");
            if (scanf("%d", &denominator) == EOF) {
                printf("\n");
                return 0;
            }
        } else {
            int readn = fscanf(fin, "%d / %d", &numerator, &denominator);
            if (readn == EOF) {
                return 0;
            } else if (readn != 2) {
                printf("Input file contains wrong format");
                fclose(fout);
                return -1;
            }
        }

        type = calculate_division(numerator, denominator, result);

        if (mode == IO_CONSOLE) {
            if (type == TYPE_FINITE || type == TYPE_INFINITE) {
                printf("The Result:: %s Number: %s\n", type == TYPE_FINITE ? "Finite" : "Infinite", result);
            } else {
                printf("The Range of \"Numerator / Denominator\" is not from 0.1 to 1\n");
            }
        } else {
            if (type == TYPE_FINITE || type == TYPE_INFINITE) {
                fprintf(fout, "%d / %d = %s (%s)\n", numerator, denominator, result, type == TYPE_FINITE ? "Finite" : "Infinite");
            } else {
                fprintf(fout, "%d / %d = Out of Range (\"Numerator / Denominator\" is not from 0.1 to 1)\n", numerator, denominator);
            }
        }
    }

    if (mode == IO_FILE) {
        fclose(fin);
        fclose(fout);
    }

    return 0;
}
