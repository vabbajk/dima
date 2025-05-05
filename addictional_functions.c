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
            printf("������ �����. ���������� ��� ���.\n");
            continue;
        }

        if (buffer[0] == '\n') {return INT_MIN;}

        buffer[strcspn(buffer, "\n")] = 0;

        errno = 0;
        number = strtol(buffer, &endptr, 10);

        if (endptr == buffer) {
            printf("������: ����� ������ �����, � �� �����.\n");
            continue;
        }

        while (*endptr != '\0') {
            if (!isspace((unsigned char)*endptr)) {
                printf("������: ���� �������� ������ �������.\n");
                continue;
            }
            endptr++;
        }

        if ((errno == ERANGE) || (number <= INT_MIN) || (number > INT_MAX)) {
            printf("������: ����� ������� �� ���������� ������� (%d �� %d).\n", INT_MIN+1, INT_MAX);
            continue;
        }

        return (int)number;
    }
}

void print_task() {
    printf("������������ ������ ����� 7 - �������� �������\n\n");

    printf("������� :\n");

    printf("1 - ��� ���������� ������\n\n");

    printf("2 - ��� �������� �������� ������\n\n");

    printf("3 - ��� ��������� ������\n\n");

    printf("4 - �� ����������� ���-�� �������� ������� �� ������ ������ ��������\n\n");

    printf("5 - �����\n\n");

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

    printf("\n\n������� �������� ���� ( ��� Enter ��� ���������� ) : ");
}

void delete_leaf_text() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    printf("\n\n��������� �� ���������, ����� ���� �� ������ ������� (ESC - �����):");
}