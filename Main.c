#include <stdio.h>
#include <string.h>
#include "StrList.h"
/** 
 * This is what this class does:
    printf("1. Insert strings into the list\n");
    printf("2. Insert a string at a certain index\n");
    printf("3. Print the list\n");
    printf("4. Print the length of the list\n");
    printf("5. Print a string at a certain index\n");
    printf("6. Print the total number of characters in the list\n");
    printf("7. Print how many times a string appears in the list\n");
    printf("8. Delete all occurrences of a string from the list\n");
    printf("9. Delete a string at a certain index\n");
    printf("10. Reverse the list\n");
    printf("11. Delete the entire list\n");
    printf("12. Sort the list in lexicographical order\n");
    printf("13. Check if the list is arranged in lexicographical order\n");
    printf("0. Exit the program\n");
}
*/

int main() {
    StrList* list = StrList_alloc(); // Initialize an empty list
    
    int choice;
    int numWords;
    char input[100];

    do {
        // printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Insert strings into the list
                // printf("Enter the number of words: ");
                scanf("%d", &numWords);
                // printf("Enter %d words separated by space:\n", numWords);
                for (int i = 0; i < numWords; i++) {
                    char input[50];
                    scanf("%s", input);
                    StrList_insertLast(list, input);
                }
                break;
            case 2:
                // Insert a string at a certain index
                // printf("Enter the index: ");
                int index;
                scanf("%d", &index);
                if (scanf("%s", input) >= 0) {
                    StrList_insertAt(list, input, index);
                }
                break;
            case 3:
                // Print the list
                // printf("List:\n");
                StrList_print(list);
                break;
            case 4:
                // Print the length of the list
                printf("%zu\n", StrList_size(list));
                break;
            case 5:
                // Print a string at a certain index
                // printf("Enter the index: ");
                scanf("%d", &index);
                // printf("String at index %d: ", index);
                StrList_printAt(list, index);
                break;
            case 6:
                // Print the total number of characters in the list
                StrList_printLen(list);
                break;
            case 7:
                // Print how many times a string appears in the list
                // printf("Enter the string to search for: ");
                scanf("%s", input);
                printf("%d\n", StrList_count(list, input));
                break;
            case 8:
                // Delete all occurrences of a string from the list
                // printf("Enter the string to delete: ");
                scanf("%s", input);
                StrList_remove(list, input);
                
                break;
            case 9:
                // Delete a string at a certain index
                // printf("Enter the index of the string to delete: ");
                scanf("%d", &index);
                StrList_removeAt(list, index);
                break;
            case 10:
                // Reverse the list
                StrList_reverse(list);
                // printf("List reversed.\n");
                break;
            case 11:
                
                int size = StrList_size(list);
                int i = (size)-1;
                while(i>0){
                StrList_removeAt(list,i);
                i--;
                }
                list = StrList_alloc();
                break;
            case 12:
                // Sort the list in lexicographical order
                StrList_sort(list);
                // printf("List sorted in lexicographical order.\n");
                break;
            case 13:
                // Check if the list is arranged in lexicographical order
                if (StrList_isSorted(list)) {
                    printf("true\n");
                } else {
                    printf("false\n");
                }
                break;
            case 0:
                // printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    // Free memory allocated for the list
    StrList_free(list);

    return 0;
}
