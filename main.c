#include <stdio.h>
#include <windows.h>
#include "Tree.h"
#include "addictional_functions.h"
int main(void) {



    struct Tree * tree = (struct Tree *)malloc(sizeof(struct Tree));

    InitTree(tree);

    while (1) {
        SetConsoleOutputCP(1251);
        SetConsoleCP(1251);
        print_task();

        char c = user_choice('1', '5');

        switch (c) {
            case '1':
                InputTree(tree);
                break;
            case '2':
                DeletingMode(tree);
                break;
            case '3':
                system("cls");
                visualize_tree(tree);
                system("pause");
                break;
            case '4':
                cut_off_some_leaves(tree);
                break;
        }

        system("cls");
    }

    return 0;
}
