#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <windows.h>
#include <conio.h>
#include "addictional_functions.h"

int input_integer() {

    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    char buffer[256];
    char *endptr;
    long number;

    while (1) {
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Ошибка ввода. Попробуйте ещё раз.\n");
            continue;
        }

        if (buffer[0] == '\n') {return INT_MIN;}

        buffer[strcspn(buffer, "\n")] = 0;

        errno = 0;
        number = strtol(buffer, &endptr, 10);

        if (endptr == buffer) {
            printf("Ошибка: нужно ввести число, а не текст.\n");
            continue;
        }

        while (*endptr != '\0') {
            if (!isspace((unsigned char)*endptr)) {
                printf("Ошибка: ввод содержит лишние символы.\n");
                continue;
            }
            endptr++;
        }

        if ((errno == ERANGE) || (number <= INT_MIN) || (number > INT_MAX)) {
            printf("Ошибка: число выходит за допустимые границы (%d до %d).\n", INT_MIN+1, INT_MAX);
            continue;
        }

        return (int)number;
    }
}

void print_task() {
    printf("Лабораторная работа номер 7 - Бинарные деревья\n\n");

    printf("Введите :\n");

    printf("1 - для заполнения дерева\n\n");

    printf("2 - для удаления элемента дерева\n\n");

    printf("3 - Для отрисовки дерева\n\n");

    printf("4 - За минимальное кол-во удалений сделать из дерева строго бинарное\n\n");

    printf("5 - Выход\n\n");

}

char user_choice(char n, char m) {
    char c = -1;
    while (c < n || c > m) {
        c = _getch();
    }
    return c;
}

void input_leaf_text() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    printf("\n\nВведите значение узла ( или Enter для завершения ) : ");
}

void delete_leaf_text() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    printf("\n\nВыбирайте на стрелочки, какой узел вы хотите удалить (ESC - выход):");
}