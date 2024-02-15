#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

typedef struct Node 
{
    char* data;
    struct Node* next;
} Node;

struct _StrList 
{
    Node* head;
    size_t size;
};

// Utility function to create a new node
static Node* newNode(const char* data) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = strdup(data); // strdup allocates memory and copies the string
    node->next = NULL;
    return node;
}

// Implement StrList_alloc
StrList* StrList_alloc() 
{
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

// Implement StrList_free
void StrList_free(StrList* StrList) 
{
    if (!StrList) return;
    Node* current = StrList->head;
    while (current) 
    {
        Node* temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }
    free(StrList);
}

size_t StrList_size(const StrList* StrList) 
{
    if (StrList == NULL) 
    {
        return 0; // Return 0 if the list is NULL
    }
    return StrList->size; // Return the size field of the list
}


// Implement StrList_insertLast
void StrList_insertLast(StrList* StrList, const char* data) 
{
    if (!StrList || !data) return;
    Node* node = newNode(data);
    if (!node) return;
    if (!StrList->head) 
    {
        StrList->head = node;
    } 
    else 
    {
        Node* current = StrList->head;
        while (current->next) 
        {
            current = current->next;
        }
        current->next = node;
    }
    StrList->size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) 
{
    if (StrList == NULL || data == NULL || index < 0) 
    {
        return; // Input validation
    }

    Node* node = newNode(data); // Utilize the newNode helper function to create a new node
    if (!node) 
    {
        return; // Memory allocation for newNode failed
    }

    if (index == 0) 
    {
        // Inserting at the beginning
        node->next = StrList->head;
        StrList->head = node;
    } 
    else 
    {
        Node* current = StrList->head;
        for (int i = 1; current != NULL && i < index; i++) 
        {
            current = current->next;
        }

        if (current == NULL) 
        {
            // If the index is greater than the size of the list,
            // the node will not be inserted. Free the allocated memory for node
            free(node->data); // Free the duplicated string
            free(node); // Free the node itself
            return;
        }

        // Inserting in the middle or at the end
        node->next = current->next;
        current->next = node;
    }

    StrList->size++; // Increment the size of the list
}


void StrList_sort(StrList* list) 
{
    if (!list || !list->head || !list->head->next) 
    {
        return; // List is empty or has one element
    }

    int swapped;
    Node *ptr1, *lptr = NULL;

    // Using a bubble sort algorithm for simplicity
    do {
        swapped = 0;
        ptr1 = list->head;

        while (ptr1->next != lptr) 
        {
            if (strcmp(ptr1->data, ptr1->next->data) > 0) 
            {
                char *temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Placeholder for StrList_isSorted was already provided

// Implement StrList_count as requested
int StrList_count(StrList* StrList, const char* data) 
{
    if (!StrList || !data) 
    {
        return 0;
    }

    int count = 0;
    Node* current = StrList->head;
    while (current) 
    {
        if (strcmp(current->data, data) == 0) 
        {
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_removeAt(StrList* list, int index) 
{
    if (!list || index < 0 || index >= list->size) 
    {
        return; // Out of bounds
    }

    Node *temp = list->head, *prev = NULL;
    if (index == 0) 
    {
        list->head = temp->next; // Change head
    } 
    else
    {
        for (int i = 0; temp != NULL && i < index; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) return; // If position is more than number of nodes
        prev->next = temp->next;
    }
    free(temp->data);
    free(temp);
    list->size--;
}

char* StrList_getAtIndex(const StrList* list, int index)
{
    // Check for a null list or negative index
    if (list == NULL || index < 0) 
    {
        return NULL;
    }

    Node* current = list->head;
    int currentIndex = 0;

    // Iterate through the list until the desired index is reached
    while (current != NULL && currentIndex < index) 
    {
        current = current->next;
        currentIndex++;
    }

    // Check if the current node is null, which means the index was out of bounds
    if (current == NULL) 
    {
        return NULL;
    }

    // Return the data at the current node, which is at the specified index
    return current->data;
}


// Implement StrList_totalChars as requested
size_t StrList_totalChars(const StrList* list) 
{
    if (!list) 
    {
        return 0;
    }

    size_t totalChars = 0;
    Node* current = list->head;
    while (current) 
    {
        totalChars += strlen(current->data);
        current = current->next;
    }
    return totalChars;
}

void StrList_remove(StrList* list, const char* data) 
{
    Node **current = &list->head, *temp = NULL;
    while (*current != NULL) 
    {
        if (strcmp((*current)->data, data) == 0) 
        {
            temp = *current;
            *current = (*current)->next;
            free(temp->data);
            free(temp);
            list->size--;
        } 
        else 
        {
            current = &(*current)->next;
        }
    }
}

void StrList_reverse(StrList* list) 
{
    Node *prev = NULL, *current = list->head, *next = NULL;
    while (current != NULL) 
    {
        next = current->next;  // Store next
        current->next = prev;  // Reverse current node's pointer
        prev = current;        // Move pointers one position ahead
        current = next;
    }
    list->head = prev;
}

int StrList_isSorted(StrList* list) 
{
    if (!list->head || !list->head->next) 
    {
        return 1; // Empty list or single element is considered sorted
    }
    Node* current = list->head;
    while (current->next != NULL) 
    {
        if (strcmp(current->data, current->next->data) > 0) 
        {
            return 0; // Not sorted
        }
        current = current->next;
    }
    return 1; // Sorted
}

void StrList_print(const StrList* StrList) 
{
    if (StrList == NULL || StrList->head == NULL) 
    {
        printf("The list is empty.\n");
        return; // Early exit if the list is NULL or empty
    }

    printf("List contents:\n");
    Node* current = StrList->head; // Start from the head of the list
    while (current != NULL) 
    {
        printf("%s\n", current->data); // Print the data of the current node
        current = current->next; // Move to the next node
    }
}


void StrList_printAt(const StrList* list, int index) 
{
    if (index < 0 || index >= list->size) 
    {
        printf("Index out of bounds\n");
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) 
    {
        current = current->next;
    }
    printf("%s\n", current->data);
}
