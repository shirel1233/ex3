#include "StrList.h"
#include <stdio.h>
#include <string.h>

// Structure for a node in the linked list
typedef struct Node {
    char* data;           // Data stored in the node
    struct Node* next;    // Pointer to the next node
} Node;

// Structure for the string list
typedef struct _StrList {
    Node* head;  // Pointer to the head of the list
    int size;    // Size of the list
} StrList;

// Duplicate a string, similar to strdup
static char* my_strdup(const char* s) {
    char* d = (char*)malloc(strlen(s) + 1);  // Allocate memory for the string
    if (d == NULL) return NULL;              // Check for allocation failure
    strcpy(d, s);                            // Copy the string
    return d;
}

// Create a new node with the given data
static Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Allocate memory for the node
    newNode->data = my_strdup(data);              // Duplicate the data
    newNode->next = NULL;                         // Initialize next to NULL
    return newNode;
}

// Allocate memory for a new string list
StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));  // Allocate memory for the list
    list->head = NULL;                                  // Initialize head to NULL
    list->size = 0;                                     // Initialize size to 0
    return list;
}

// Free a node
void Node_free(Node *node) {
    if (node != NULL) {
        free(node->data);  // Free the data
        free(node);        // Free the node
    }
}

// Free the entire string list
void StrList_free(StrList *list) {
    if (list == NULL) return;
    Node *p1 = list->head;  // Pointer to traverse the list
    Node *p2;               // Temporary pointer for freeing nodes
    while (p1) {
        p2 = p1;            // Store current node
        p1 = p1->next;      // Move to next node
        Node_free(p2);      // Free the stored node
    }
    free(list);             // Free the list structure
}

// Get the size of the list
size_t StrList_size(const StrList* list) {
    return list->size;
}

// Insert data at the end of the list
void StrList_insertLast(StrList* list, const char* data) {
    Node* newNode = createNode(data);  // Create a new node
    if (!list->head) {
        list->head = newNode;          // If list is empty, set new node as head
    } else {
        Node* temp = list->head;       // Traverse to the end of the list
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;          // Append the new node at the end
    }
    list->size++;
}

// Insert data at a specific index
void StrList_insertAt(StrList* list, const char* data, int index) {
    if (!list || index < 0 || index > list->size) return;  // Check for valid index
    if (index == list->size) {
        StrList_insertLast(list, data);  // Insert at the end if index is size
        return;
    }
    Node* newNode = createNode(data);  // Create a new node
    if (index == 0) {
        newNode->next = list->head;    // Insert at the head
        list->head = newNode;
    } else {
        Node* current = list->head;    // Traverse to the position
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next; // Insert the new node
        current->next = newNode;
    }
    list->size++;
}

// Print all elements of the list
void StrList_print(const StrList* StrList) {
    if (StrList->head != NULL) {
        Node* p = StrList->head;       // Start from the head
        while (p->next != NULL) {      // Traverse the list
            printf("%s ", p->data);
            p = p->next;
        }
        if (p != NULL) {
            printf("%s", p->data);     // Print the last element
        }
    }
    printf("\n");
}

// Print the element at a specific index
void StrList_printAt(const StrList* list, int index) {
    if (index >= list->size) return;   // Check for valid index
    Node* temp = list->head;           // Start from the head
    for (int i = 0; i < index; i++) {
        temp = temp->next;             // Traverse to the index
    }
    printf("%s\n", temp->data);        // Print the data
}

// Calculate and print the total length of all strings
int StrList_printLen(const StrList* list) {
    int length = 0;
    Node* temp = list->head;           // Start from the head
    while (temp) {
        length += strlen(temp->data);  // Sum the lengths of strings
        temp = temp->next;
    }
    printf("%d\n", length);            // Print the total length
    return length;
}

// Count occurrences of a specific string
int StrList_count(StrList* list, const char* data) {
    int count = 0;
    Node* temp = list->head;           // Start from the head
    while (temp) {
        if (strcmp(temp->data, data) == 0) {
            count++;                   // Increment count if match found
        }
        temp = temp->next;
    }
    return count;
}

// Remove the first occurrence of a specific string
void StrList_remove(StrList* list, const char* data) {
    char *str = list->head->data;      // Get data from the head
    Node* p = list->head;
    Node* prev = NULL;
    while (p != NULL) {
        if (strcmp(str, data) == 0) {
            if (prev == NULL) {
                // If the match is in the first node
                list->head = p->next;
            } else {
                // If the match is in a subsequent node
                prev->next = p->next;
            }
            free(p);
            --(list->size);            // Decrement size
            return;
        }
        prev = p;
        p = p->next;
        str = p->data;
    }
}

// Remove the element at a specific index
void StrList_removeAt(StrList* list, int index) {
    if (index >= list->size) return;   // Check for valid index
    Node* temp = list->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (prev) {
        prev->next = temp->next;       // Bypass the node to be removed
    } else {
        list->head = temp->next;       // Update head if first node is removed
    }
    free(temp->data);                  // Free data and node
    free(temp);
    list->size--;
}

// Reverse the order of the list
void StrList_reverse(StrList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    while (current) {
        next = current->next;          // Store next node
        current->next = prev;          // Reverse the link
        prev = current;
        current = next;
    }
    list->head = prev;                 // Update head to the new first node
}

// Sort the list in ascending order
void StrList_sort(StrList* list) {
    if (!list->head || !list->head->next) return;  // Return if list is empty or has one element
    for (Node* i = list->head; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->data, j->data) > 0) {
                char* temp = i->data;  // Swap data if out of order
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// Check if the list is sorted
int StrList_isSorted(StrList* list) {
    if (!list->head || !list->head->next) return 1;  // Return true if list is empty or has one element
    Node* temp = list->head;
    while (temp->next) {
        if (strcmp(temp->data, temp->next->data) > 0) return 0;  // Return false if out of order
        temp = temp->next;
    }
    return 1;  // Return true if sorted
}
