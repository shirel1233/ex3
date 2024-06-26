#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

void printMenu() {
    printf("1 - Add strings to list (A)\n");
    printf("2 - Insert string at index (B)\n");
    printf("3 - Print list (C)\n");
    printf("4 - Print list length (D)\n");
    printf("5 - Print string at index (E)\n");
    printf("6 - Print total characters (F)\n");
    printf("7 - Count occurrences of string (G)\n");
    printf("8 - Remove all occurrences of string (H)\n");
    printf("9 - Remove string at index (I)\n");
    printf("10 - Reverse list (J)\n");
    printf("11 - Delete entire list (K)\n");
    printf("12 - Sort list lexicographically (L)\n");
    printf("13 - Check if list is sorted (M)\n");
    printf("0 - Exit (Q)\n");
}

int main() {
    StrList* list = StrList_alloc();
    char input[256];
    int choice;

    do {
        printMenu();
        printf("Enter your choice: ");
        fgets(input, sizeof(input), stdin);
        choice = atoi(input);

        switch (choice) {
            case 1: {
                printf("Enter strings separated by spaces: ");
                fgets(input, sizeof(input), stdin);
                char* token = strtok(input, " \n");
                while (token) {
                    StrList_insertLast(list, token);
                    token = strtok(NULL, " \n");
                }
                break;
            }
            case 2: {
                int index;
                char str[256];
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter string: ");
                scanf("%s", str);
                StrList_insertAt(list, str, index);
                break;
            }
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("List length: %zu\n", StrList_size(list));
                break;
            case 5: {
                int index;
                printf("Enter index: ");
                scanf("%d", &index);
                StrList_printAt(list, index);
                break;
            }
            case 6:
                printf("Total characters: %d\n", StrList_printLen(list));
                break;
            case 7: {
                char str[256];
                printf("Enter string: ");
                scanf("%s", str);
                printf("Occurrences: %d\n", StrList_count(list, str));
                break;
            }
            case 8: {
                char str[256];
                printf("Enter string: ");
                scanf("%s", str);
                StrList_remove(list, str);
                break;
            }
            case 9: {
                int index;
                printf("Enter index: ");
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            }
            case 10:
                StrList_reverse(list);
                break;
            case 11:
                StrList_free(list);
                list = StrList_alloc();
                break;
            case 12:
                StrList_sort(list);
                break;
            case 13:
                printf("List is sorted: %d\n", StrList_isSorted(list));
                break;
            case 0:
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
        getchar();  // clear the newline character from the buffer
    } while (choice != 0);

    StrList_free(list);
    return 0;
}
