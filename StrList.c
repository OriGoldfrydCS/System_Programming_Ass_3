#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


/*----------------------------------------------------------*/
/* Node structure represents an element withing the StrList */
/*----------------------------------------------------------*/
typedef struct Node 
{
    char* data;
    struct Node* next;
} Node;


/*A structure that represents StrList*/
struct _StrList 
{
    Node* head;
    size_t size;
};

typedef struct _StrList StrList;


/*----------------------------------------------------------*/
/* This function allocates memory for a new StrList,        */
/* initialize its properties, and returns a pointer to it   */
/*----------------------------------------------------------*/
StrList* StrList_alloc() 
{
    StrList* string_list = (StrList*)malloc(sizeof(StrList));       // Allocates for a string_list with a size of StrList structure, as defined
    if(string_list == NULL)                                         // This "if-statement" check whether the memory allocated successfully 
    {
        return NULL;
    }
    
    // Initialize the string_list properties when initialized to prevent mistakes in future
    string_list->head = NULL;
    string_list->size = 0;
    return string_list;
}


/*----------------------------------------------------------*/
/* This function frees the memory that used by a StrList    */
/*----------------------------------------------------------*/
void StrList_free(StrList* StrList) 
{
    // if a pointer to StrList does not exists, nothing to be done regarding freeing memory
    if(!StrList)       
    {
            return;
    } 
    Node* current = StrList->head;      // Set the pointer of the StrList to a variable
    while(current)                      // Go through all nodes and free: (1) the node's data; (2) the memory allocated to that node (string) as a structure
    {
        Node* mid_node = current;
        current = current->next;
        free(mid_node->data);
        free(mid_node);
    }
    free(StrList);
}


/*----------------------------------------------------------*/
/* This function returns the StrList's size                 */
/*----------------------------------------------------------*/
size_t StrList_size(const StrList* StrList) 
{
    if(StrList == NULL) 
    {
        return 0;           // If the StrList is empty (NULL), return 0 
    }
    return StrList->size;   // Else, return property "size" that stores the StrList
}


/*----------------------------------------------------------*/
/* This function inserts a string node at the StrList's end */
/*----------------------------------------------------------*/
void StrList_insertLast(StrList* StrList, const char* data) 
{
    // Initial check: if the pointer of the StrList or the data is null, return nothing
    if(StrList == NULL || data == NULL)
    {
        return;
    } 

    Node* node = newNode(data);         // Create a new node (see auxiliary function below)
    
    // Check if the node gets a pointer successfully
    if(node == NULL)                            
    {
        return;
    } 

    // Check if the head StrList's node exists 
    if(!StrList->head) 
    {
        StrList->head = node;
    } 

    // Place the new node at the end of the StrList
    else 
    {
        Node* current = StrList->head;      // Store the current head node
        while(current->next)                // Go through all nodes and place the new node after the first node which it next is null (means it is the last one at that time)
        {
            current = current->next;
        }
        current->next = node;
    }
    StrList->size++;                        // Resize the StrList
}

/*-----------------------------------------------------------*/
/* This function inserts a new string node at a specific     */
/* index in the StrList, and considers two cases:            */
/* (1) Insert the new string in the middle or at the end of  */
/* the StrList                                               */
/* (2) Insert the new string at the begining of the StrList  */
/*-----------------------------------------------------------*/

void StrList_insertAt(StrList* StrList, const char* data, int index) 
{
    // Initially check if the given index is valid, the data exists and the StrList already initialized
    if (index < 0 || data == NULL || StrList == NULL) 
    {
        return; 
    }

    Node* node = newNode(data);     // Create a newNode with the given data (see auxiliary function below)
    
    // Check if the memory allocation for the newNode succeeded or not
    if(node == NULL) 
    {
        return; 
    }

    // Case 1: Insert the new string node in the middle or at the end of the StrList
    if(index > 0) 
    {
        Node* current = StrList->head;                          // "Pull-out" the first string node
        for(int i = 1; current != NULL && i < index; i++)       // Go through all nodes and check if StrList's size > index
        {
            current = current->next;
        }

        if(current == NULL)             // StrList's size > index
        {
            free(node->data); 
            free(node); 
            return;
        }

        // Insert the string node in the middle or at the end
        node->next = current->next;
        current->next = node;
    }

    // Case 2: Insert the new string node at the begining of the StrList
    if(index == 0) 
    {
        node->next = StrList->head;
        StrList->head = node;
    } 

    StrList->size++;    // Resize the StrList
}


/*-----------------------------------------------------------*/
/* This function returns the StrList first string node       */
/*-----------------------------------------------------------*/

char* StrList_firstData(const StrList* StrList)
{
    // Initial check: if the pointer of the StrList or the head is null, return nothing
    if(StrList->head == NULL || StrList == NULL)
    {
        return NULL;
    }
    
    Node* first_node = StrList->head;       // "Pull-out" the pointer of the StrList's head 
    if(first_node == NULL)                  // Check validity of the pointer
    {
        return NULL;
    }

    return first_node->data;
}


/*-----------------------------------------------------------*/
/* This function prints the full StrList                     */
/*-----------------------------------------------------------*/
void StrList_print(const StrList* StrList) 
{
    // Initial check for valitidy
    if(StrList == NULL || StrList->head == NULL) 
    {
        printf("StrList is empty with strings\n");
        return;
    }

    printf("The story (StrList) is:\n");
    Node* current = StrList->head;          // Pull-out" the pointer of the StrList's head
    while(current != NULL)                  // Go through all nodes untill the end of the StrList 
    {
        printf("%s\n", current->data);      // Print the data
        current = current->next;            // Move to pointer to the next string node
    }
}


/*-----------------------------------------------------------*/
/* This function prints a string node at a specific index    */
/*-----------------------------------------------------------*/
void StrList_printAt(const StrList* StrList, int index) 
{
    // Check if the given index is out of bounds
    if(index < 0 || index >= StrList->size) 
    {
        printf("The givne index is out of bounds\n");
        return;
    }

    Node* current = StrList->head;          // Pull-out" the pointer of the StrList's head    

    for(int i = 0; i < index; i++)          // Go through all nodes until the given index 
    {
        current = current->next;            // Move the pointer to the next string node
    }

    printf("%s\n", current->data);
}


/*-----------------------------------------------------------*/
/* This function returns the amount of chars in the Strlist  */
/*-----------------------------------------------------------*/
int StrList_printLen(const StrList* StrList)
{
    // Initial check for valitidy. If conditions meet, return an amount of zero
    if(StrList == NULL || StrList->head == NULL) 
    {
        printf("StrList is empty with strings\n");
        return 0;
    }

    int total_chars = 0;             // A counter for summing the total chars in the Strlist 
    Node* current = StrList->head;   // Pull-out" the pointer of the StrList's head   

    while(current)
    {
        total_chars += strlen(current->data);   // Add the amount of chars in the specific string (by using strlen) to the counter
        current = current->next;                // Move the pointer to the next string node
    }
    
    return total_chars;

}


/*-----------------------------------------------------------*/
/* This function returns the number of times a given string  */
/* exists in the Strlist                                     */
/*-----------------------------------------------------------*/
int StrList_count(StrList* StrList, const char* data) 
{
// Initial check: if the pointer of the StrList or the data is null, return 0
    if(StrList == NULL || data == NULL)    
    {
        return 0;
    }

    int instances = 0;                  // A counter for summing the total chars in the Strlist
    Node* current = StrList->head;      // Pull-out" the pointer of the StrList's head  
    
    while (current) 
    {
        if (strcmp(current->data, data) == 0)   // compare the given string (data) to the data of the current node
        {
            instances++;                        // Increment the counter
        }
        current = current->next;                // Move the pointer to the next string node
    }

    return instances;
}


/*-----------------------------------------------------------*/
/* This function removes all the appearences of a given      */
/* string in the StrList                                     */
/*-----------------------------------------------------------*/
void StrList_remove(StrList* StrList, const char* data) 
{
    Node **current = &StrList->head;        // Initiate a pointer to the StrList head's pointer
    Node *node_to_remove = NULL;            // Prepare a pointer the removed node

    while(*current != NULL) 
    {
        if (strcmp((*current)->data, data) == 0)    // compare the given string (data) to the data of the current node
        {
            node_to_remove = *current;              // Assign the current node to node_to_remove 
            *current = (*current)->next;            // Connect the previous node the the next node
            free(node_to_remove->data);             // free the memory of the node_to_remove's data
            free(node_to_remove);                   // free the memory of node_to_remove (means remove it)
            StrList->size--;                        // Resize the StrList
        } 
        else 
        {
            current = &(*current)->next;            // Move the pointer to the next string node
        }
    }
}


/*-----------------------------------------------------------*/
/* This function removes the string at a given index         */
/*-----------------------------------------------------------*/
void StrList_removeAt(StrList* StrList, int index) 
{
    // Check if the given index is out of bounds
    if(index < 0 || index >= StrList->size || StrList == NULL) 
    {
        return; // Out of bounds
    }

    Node *tmp = StrList->head;          // A temporary pointer to the StrList's head
    Node *prev = NULL;                  // Initiate a variable to store a pointer to the previous node
    
    // Case 1: remove the first string node
    if(index == 0) 
    {
        StrList->head = tmp->next;     // heads will point to the next node of tmp
    } 

    // Case 2: remove a string node in the middle or at the end of the StrList
    else
    {
        for(int i = 0; tmp != NULL && i < index; i++)     // Go through all nodes until reached to the end of the StrList or until index (The smallest among them)  
        {
            prev = tmp;                 // Update prev to tmp (which is the next string node)
            tmp = tmp->next;            // Update tmp to the next string node
        }

        if (tmp == NULL)                // If position is more than number of nodes
        {
            return; 
        }

        prev->next = tmp->next;         // Update the next string node of prev node
    }

    free(tmp->data);        // Free memory
    free(tmp);
    StrList->size--;        // Resize the StrList
}


/*-----------------------------------------------------------*/
/* This function checks if two StrLists have the same string */
/* nodes; and returns 1 for TRUE, otherwise 0 for FALSE      */
/*-----------------------------------------------------------*/
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    Node* current1 = StrList1->head;        // Initiate a pointer to the StrList1 head's pointer 
    Node* current2 = StrList2->head;        // Initiate a pointer to the StrList2 head's pointer

    while(current1 != NULL && current2 != NULL)          // Go through all nodes in the two StrList simultaneously
    {
        if(strcmp(current1->data, current2->data) != 0)  // compare the strings (data) of the two StrList in the current position
        {
            return 0;                                    // If comparison failed, return 0 (FALSE)
        }

        // Move the pointers to the next string nodes
        current1 = current1->next;
        current2 = current2->next;
    }

    // If the two StrList reached to the end at the same time, return 1 (TRUE)
    if(current1 == NULL && current2 == NULL)
    {
        return 1;
    }
    return 0;
}


/*-----------------------------------------------------------*/
/* This function clones the given StrList                    */
/*-----------------------------------------------------------*/
StrList* StrList_clone(const StrList* StrList)
{
    // Initial check: if StrList does not exist, clone cannot be performed
    if (StrList == NULL) 
    {
        return NULL;
    }

    Node* cloned = (Node*)malloc(sizeof(StrList));

    // Check if allocation succeeded or not
    if (cloned == NULL)
    {
        return NULL;     
    }

    Node* current = StrList->head;
    while(current != NULL) 
    {
        // Use a hypothetical StrList_insertLast function to add each node's data to the clone
        StrList_insertLast(cloned, current->data);
        current = current->next;
    }

    return cloned;
}


/*-----------------------------------------------------------*/
/* This function reverces the given StrList                  */
/*-----------------------------------------------------------*/

void StrList_reverse(StrList* StrList) 
{
   Node *prev = NULL;               // Initiate a variable to store a pointer to the previous node
   Node *current = StrList->head;   // Initiate a pointer to the StrList head's pointer   
   Node *next = NULL;               // Initiate a variable to store a pointer to the next node

    while (current != NULL) 
    {
        next = current->next;  // Store the next node
        current->next = prev;  // Reverse the current node's 'next' pointer to point to the previous node
        prev = current;        // Update 'prev' to be the current node, moving it one step ahead for the next iteration
        current = next;        // Move to the next node in the original list order
    }
    
    StrList->head = prev;      // After the loop, 'prev' will be the new head of the list
}


/*-----------------------------------------------------------*/
/* This function sorta a given list in lexi. order           */
/*-----------------------------------------------------------*/
void StrList_sort(StrList* StrList) 
{
    // Case 1: an empty list or single element is considered sorted
    if (StrList == NULL || StrList->head == NULL || StrList->head->next == NULL) 
    {
        return; 
    }

    int swapped;                // A flag to indicate in any string nodes were swapped during a loop
    Node *p1;                   // p1 used for traversing the StrList
    Node *p2 = NULL;            // p2 indicates the StrList's end

    // Using bubble sort
    do {
        swapped = 0;            // Reset flag
        p1 = StrList->head;     // Start from the beginning of the StrList for each pass

        while (p1->next != p2)  // Iterate until the last sorted element reached
        {
            if (strcmp(p1->data, p1->next->data) > 0)       // Compare to neighborhood goods
            {
                // Preform swap
                char *temp = p1->data;
                p1->data = p1->next->data;
                p1->next->data = temp;
                swapped = 1;
            }
            p1 = p1->next;      // Move to the next node for comparison
        }
        p2 = p1;                // Update the last sorted element

    } while (swapped);
}


/*-----------------------------------------------------------*/
/* This function checks if a given StrList is sorted in      */
/* lexi. order, and returns 1 for sorted or 0 otherwise      */
/*-----------------------------------------------------------*/
int StrList_isSorted(StrList* StrList) 
{
    // Case 1: an empty list or single element is considered sorted
    if (StrList->head == NULL || StrList->head->next == NULL) 
    {
        return 1; 
    }

    // Case 2: compare pairs of nodes
    Node* current = StrList->head;   // "Pull-out" the pointer of the StrList's head    
    while(current->next != NULL)     // Go hrough all nodes in the StrList
    {
        if (strcmp(current->data, current->next->data) > 0)     // Compare to neighrhood nodes' data
        {
            return 0;               // Not sorted
        }

        current = current->next;    // Move the pointer to the next string node
    }

    return 1;                       // Sorted
}


/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/* Auxiliary functions                                      */ 
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/

/*This function creates a new string node*/
Node* newNode(const char* data) 
{
    Node* newNode = (Node*)malloc(sizeof(newNode));   // Allocate memory for the new string node
    if (newNode == NULL)                              // Check if memory allocation succeeded or not
    {
        return NULL;
    } 
    newNode->data = strdup(data);                     // use strdup to copy the string
    newNode->next = NULL;                             // Initiate the next pointer to null
    return newNode;
}


char* StrList_getAtIndex(const StrList* StrList, int index)
{
    // Check for a null list or negative index
    if (StrList == NULL || index < 0) 
    {
        return NULL;
    }

    Node* current = StrList->head;
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