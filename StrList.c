#include "StrList.h"
#include <stdio.h>
#include <string.h>
//#include <stdio.h>
typedef struct Node {
    char* data;
    struct Node* next;
} Node;

typedef struct _StrList {
    Node* head;
    int size;
} StrList;

static char* my_strdup(const char* s) {
    char* d = (char*)malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

static Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = my_strdup(data);
    newNode->next = NULL;
    return newNode;
}

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    list->head = NULL;
    list->size = 0;
    return list;
}
/** 
void StrList_free(StrList* list) {
    if (!list) return;
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    free(list);
}
*/
void Node_free(Node *node) {
  if (node != NULL) {
    free(node->data);
    free(node);
  }
}
void StrList_free(StrList *list) {
  if (list == NULL) return;
  Node *p1 = list->head;  
  Node *p2;              
  while (p1) {
    p2 = p1;         
    p1 = p1->next;  
    Node_free(p2);   
  }
  free(list);
}

size_t StrList_size(const StrList* list) {
    return list->size;
}

void StrList_insertLast(StrList* list, const char* data) {
    Node* newNode = createNode(data);
    if (!list->head) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    list->size++;
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (!list || index < 0 || index > list->size) return;
    if (index == list->size) {
        StrList_insertLast(list, data);
        return;
    }
    Node* newNode = createNode(data);
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
/** 
void StrList_print(const StrList* list) {
    Node* temp = list->head;
    while (temp) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    if(temp!=NULL){
		printf("%s",temp->data);
	}
    printf("\n");
}
*/
void StrList_print(const StrList* StrList){
    if(StrList->head!= NULL){
    Node* p = StrList->head;
	while(p->next!=NULL) {
        printf("%s ",p->data);
		p = p->next;
	}
	if(p!=NULL){
        printf("%s",p->data);
	}
    }
	printf("\n");
}

void StrList_printAt(const StrList* list, int index) {
    if (index >= list->size) return;
    Node* temp = list->head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    printf("%s\n",temp->data);
}

int StrList_printLen(const StrList* list) {
    int length = 0;
    Node* temp = list->head;
    while (temp) {
        length += strlen(temp->data);
        temp = temp->next;
    }
    //printf("%d\n", length);
    printf("%d\n",length);
    
    return length;
}

int StrList_count(StrList* list, const char* data) {
    int count = 0;
    Node* temp = list->head;
    while (temp) {
        if (strcmp(temp->data, data) == 0) {
            count++;
        }
        temp = temp->next;
    }
    return count;
}
void StrList_remove(StrList* list, const char* data){//hadar
	char *str = list->head->data;
	Node* p = list->head;
	Node* prev = NULL;
	while (p!=NULL){
		if(strcmp(str,data) == 0){
			if (prev == NULL) {
					// If the match is in the first node
					list->head = p->next;
				}
			else {
				// If the match is in a subsequent node
					prev->next = p->next;
				}
				free(p);
				--(list->size);
				return;
			}
		prev = p;
		p = p->next;
		str = p->data;
	}
}



/**void StrList_remove(StrList* list, const char* data) {
    Node* temp = list->head;
    Node* prev = NULL;
    while (temp) {
        if (strcmp(temp->data, data) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                list->head = temp->next;
            }
            free(temp->data);
            free(temp);
            list->size--;
            temp = (prev) ? prev->next : list->head;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}*/
 
void StrList_removeAt(StrList* list, int index) {
    if (index >= list->size) return;
    Node* temp = list->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (prev) {
        prev->next = temp->next;
    } else {
        list->head = temp->next;
    }
    free(temp->data);
    free(temp);
    list->size--;
}
/** 
void StrList_removeAt(StrList* StrList, int index){
    if (index >= StrList->size) return;
  	Node* p = StrList->head;
	Node* prev = NULL;
	for (int i = 0; i<index; i++){
		if(i==index){
			if (prev == NULL) {
					StrList->head = p->next;
				}
			else {
				prev->next = p->next;
				}
				free(p->data);
				free(p);
		}
		prev = p;
		p = p->next;
	}
}
*/
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
    for (Node* i = list->head; i != NULL; i = i->next) {
        for (Node* j = i->next; j != NULL; j = j->next) {
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
    Node* temp = list->head;
    while (temp->next) {
        if (strcmp(temp->data, temp->next->data) > 0) return 0;
        temp = temp->next;
    }
    return 1;
}
