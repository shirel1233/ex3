#include "StrList.h"
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

struct _StrList {
    Node* head;
    size_t size;
};

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

void StrList_free(StrList* list) {
    if (list) {
        Node* current = list->head;
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        free(list);
    }
}

size_t StrList_size(const StrList* list) {
    return list->size;
}

void StrList_insertLast(StrList* list, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = NULL;
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (index < 0 || index > list->size) return;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = strdup(data);
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

char* StrList_firstData(const StrList* list) {
    if (list->head) {
        return list->head->data;
    }
    return NULL;
}

void StrList_print(const StrList* list) {
    Node* current = list->head;
    while (current) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList* list, int index) {
    if (index < 0 || index >= list->size) return;
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    if (current) {
        printf("%s\n", current->data);
    }
}

int StrList_printLen(const StrList* list) {
    int length = 0;
    Node* current = list->head;
    while (current) {
        length += strlen(current->data);
        current = current->next;
    }
    return length;
}

int StrList_count(StrList* list, const char* data) {
    int count = 0;
    Node* current = list->head;
    while (current) {
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList* list, const char* data) {
    Node* current = list->head;
    Node* prev = NULL;
    while (current) {
        if (strcmp(current->data, data) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                list->head = current->next;
            }
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void StrList_removeAt(StrList* list, int index) {
    if (index < 0 || index >= list->size) return;
    Node* current = list->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (prev) {
        prev->next = current->next;
    } else {
        list->head = current->next;
    }
    free(current->data);
    free(current);
    list->size--;
}

int StrList_isEqual(const StrList* list1, const StrList* list2) {
    if (list1->size != list2->size) return 0;
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    while (current1 && current2) {
        if (strcmp(current1->data, current2->data) != 0) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* list) {
    StrList* newList = StrList_alloc();
    Node* current = list->head;
    while (current) {
        StrList_insertLast(newList, current->data);
        current = current->next;
    }
    return newList;
}

void StrList_reverse(StrList* list) {
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void StrList_sort(StrList* list) {
    if (!list->head || !list->head->next) return;
    for (Node* i = list->head; i->next; i = i->next) {
        for (Node* j = i->next; j; j = j->next) {
            if (strcmp(i->data, j->data) > 0) {
                char* temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int StrList_isSorted(StrList* list) {
    if (!list->head || !list->head->next) return 1;
    Node* current = list->head;
    while (current->next) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}
