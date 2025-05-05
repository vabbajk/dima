#ifndef TREE_H
#define TREE_H

#include <conio.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "addictional_functions.h"

struct Leaf {
    struct Leaf * left;
    struct Leaf * right;
    struct Leaf * parent;
    int level;
    int value;
};

struct Tree {
    struct Leaf * root;
    int size;
};

int InitTree(struct Tree * tree) {
    tree->root = NULL;
    tree->size = 0;
    return 0;
}

struct Leaf * CreateLeaf(int value, struct Leaf * parent, int level) {
    struct Leaf * newLeaf = (struct Leaf *)malloc(sizeof(struct Leaf));
    newLeaf->left = NULL;
    newLeaf->right = NULL;
    newLeaf->value = value;
    newLeaf->parent = parent;
    newLeaf->level = level + 1;
    return newLeaf;
}

int Insert(struct Tree *tree, int value) {
    struct Leaf *currentLeaf = tree->root;
    struct Leaf *parent = NULL;
    int depth = 1;

    if (currentLeaf == NULL) {
        tree->root = CreateLeaf(value, NULL, 0);
        tree->size = 1;
        return 0;
    }

    while (currentLeaf != NULL) {
        parent = currentLeaf;
        if (value <= currentLeaf->value) {
            currentLeaf = currentLeaf->left;
        } else {
            currentLeaf = currentLeaf->right;
        }
        depth++;
    }

    struct Leaf *newLeaf = CreateLeaf(value, parent, parent->level + 1);
    if (value <= parent->value) {
        parent->left = newLeaf;
    } else {
        parent->right = newLeaf;
    }

    if (depth > tree->size) {
        tree->size = depth;
    }

    return 1;
}

void print_tree(struct Leaf *node, const char *prefix, int is_left) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    SetConsoleOutputCP(65001);
    if (node == NULL) return;

    if (node->right) {
        char new_prefix[1000];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "|   " : "    ");
        print_tree(node->right, new_prefix, 0);
    }

    printf("%s%s%d\n", prefix, is_left ? "|,,,," : "|````", node->value);

    if (node->left) {
        char new_prefix[1000];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "    " : "|   ");
        print_tree(node->left, new_prefix, 1);
    }
}

void visualize_tree(struct Tree *tree) {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    if (tree == NULL || tree->root == NULL) {
        printf("Дерево пустое!\n");
        return;
    }

    print_tree(tree->root, "", 1);
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}

int InputTree(struct Tree *tree) {

    while (1) {

        system("cls");

        visualize_tree(tree);

        input_leaf_text();

        int new_value = input_integer();

        if (new_value == INT_MIN) {
            system("cls");
            break;
        }
        else{Insert(tree, new_value);}
    }
}

int print_tree_with_highlight(struct Leaf *node, const char *prefix, int is_left, struct Leaf *highlight) {
    SetConsoleOutputCP(65001);

    if (node == NULL){SetConsoleOutputCP(1251); printf("Дерево пустое!\n"); system("pause"); return 1;};

    if (node->right) {
        char new_prefix[1000];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "|   " : "    ");
        print_tree_with_highlight(node->right, new_prefix, 0, highlight);
    }

    if (node == highlight) {
        printf("%s%s[%d]\n", prefix, is_left ? "|,,,," : "|````", node->value);
    } else {
        printf("%s%s%d\n", prefix, is_left ? "|,,,, " : "|````", node->value);
    }

    if (node->left) {
        char new_prefix[1000];
        snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "    " : "|   ");
        print_tree_with_highlight(node->left, new_prefix, 1, highlight);
    }
}

struct Leaf * navigate_tree(struct Leaf *root) {
    struct Leaf *current = root;
    char ch;
    while (1) {

        system("cls");
        if (print_tree_with_highlight(root, "", 0, current)){return NULL;}

        ch = _getch();

        if (ch == 80) {
            if (current->left) {
                current = current->left;
            }
        }
        else if (ch == 72) {
            if (current->right) {
                current = current->right;
            }
        }else if (ch == 75) {
            if (current->parent != NULL) {current = current->parent;}
        } else if (ch == 27) {
            return NULL;
        } else if (ch == 13) {
            return current;
        }

    }

}

void DeleteLeaf(struct Leaf *node) {
    if (node == NULL) return;

    DeleteLeaf(node->left);
    DeleteLeaf(node->right);

    if (node->parent == NULL){ node = NULL; return;}
    if (node == node->parent->left){node->parent->left = NULL;}
    if (node == node->parent->right){node->parent->right = NULL;}
    free(node);
}

int DeletingMode(struct Tree * tree) {

    struct Leaf * curr = navigate_tree(tree->root);

    if (curr == NULL) {return -1;}

    delete_leaf_text();

    if (curr == tree->root) {
        DeleteLeaf(curr->left);
        DeleteLeaf(curr->right);
        tree->root = NULL; return 1;
    }

    DeleteLeaf(curr);

    return 0;
}

void delete_subtree(struct Leaf *node, int *counter) {
    if (!node) return;
    delete_subtree(node->left, counter);
    delete_subtree(node->right, counter);
    free(node);
    (*counter)++;
}



struct Leaf* optimize_strict_binary(struct Leaf *node, int *removed_count) {
    if (!node) return NULL;

    // Проверим количество потомков
    int has_left = node->left != NULL;
    int has_right = node->right != NULL;

    // Если только один потомок — сразу обрубаем его
    if (has_left && !has_right) {
        printf("Оптимально удалено поддерево от %d (одиночный левый)\n", node->left->value);
        delete_subtree(node->left, removed_count);
        node->left = NULL;
    } else if (!has_left && has_right) {
        printf("Оптимально удалено поддерево от %d (одиночный правый)\n", node->right->value);
        delete_subtree(node->right, removed_count);
        node->right = NULL;
    } else if (has_left && has_right) {
        // Если два потомка — продолжаем рекурсивно
        node->left = optimize_strict_binary(node->left, removed_count);
        node->right = optimize_strict_binary(node->right, removed_count);
    }

    return node;
}

int remove_non_full(struct Tree *tree) {
    int removed = 0;
    tree->root = optimize_strict_binary(tree->root, &removed);
    tree->size -= removed;
    return removed;
}

void cut_off_some_leaves(struct Tree *tree) {
    system("cls");
    visualize_tree(tree);
    printf("\n\n------------------------------------------------------\n\n");
    int a = remove_non_full(tree);
    printf("\n\n");
    visualize_tree(tree);
    system("pause");
}



#endif
