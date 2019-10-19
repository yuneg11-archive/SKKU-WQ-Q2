#include <stdio.h>
#include <string.h>

#define MAX_REC_LEN 9
#define MAX_RES_LEN 64

#define IO_CONSOLE 1
#define IO_FILE    2

#define TYPE_ERROR    0
#define TYPE_FINITE   1
#define TYPE_INFINITE 2

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
        char result[MAX_RES_LEN];
        short type;

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

        /* DEBUG */
        type = TYPE_FINITE;
        strcpy(result, "RESULT");
        /* DEBUG */

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
                fprintf(fout, "Out of Range (\"Numerator / Denominator\" is not from 0.1 to 1)\n");
            }
        }
    }

    if (mode == IO_FILE) {
        fclose(fin);
        fclose(fout);
    }

    return 0;
}