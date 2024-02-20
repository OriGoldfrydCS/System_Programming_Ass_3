#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"


/*----------------------------------------------------------*/
/* Node structure represents a string within the StrList    */
/*----------------------------------------------------------*/
typedef struct Node 
{
    char* data;
    struct Node* next;
} Node;

/*----------------------------------------------------------*/
/* A structure that represents StrList                      */
/*----------------------------------------------------------*/
struct _StrList 
{
    Node* head;
    unsigned int size;
};

typedef struct _StrList StrList;


/*----------------------------------------------------------*/
/* This function allocates memory for a new StrList,        */
/* initialize its properties, and returns a pointer to it   */
/*----------------------------------------------------------*/
StrList* StrList_alloc() 
{
    StrList* str_list = (StrList*)malloc(sizeof(StrList));       // Allocates for a string_list with a size of StrList structure, as defined
    if(str_list == NULL)                                         // This "if-statement" check whether the memory allocated successfully 
    {
        return NULL;
    }
    
    // Initialize the string_list properties when initialized to prevent mistakes in future
    str_list->head = NULL;
    str_list->size = 0;
    
    return str_list;
}


/*----------------------------------------------------------*/
/* This function frees the memory that used by a StrList    */
/*----------------------------------------------------------*/
void StrList_free(StrList* StrList) 
{
    // if a pointer to StrList does not exists, nothing to be done regarding freeing memory
    if(StrList == NULL)       
    {
            return;
    } 

    Node* thisNode = StrList->head;      // Set the StrList's pointer to a variable
    while(thisNode)                      // Go through all nodes and free: (1) the node's data; (2) the memory allocated to that node (string) as a structure
    {
        Node* mid_node = thisNode->next;
        free(mid_node->data);
        free(mid_node);
        thisNode = mid_node;

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

    int size = StrList->size;
    return size;   // Else, return property "size" that stores the StrList
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

    Node* InsertedNode = newNode(data);         // Create a new node (see auxiliary function below)
    
    // Check if the node gets a pointer successfully
    if(InsertedNode == NULL)                            
    {
        return;
    } 

    // Check if the head StrList's node exists; If not - made the new node ad the head 
    if(StrList->head == NULL) 
    {
        StrList->head = InsertedNode;
    } 

    // Place the new node at the end of the StrList
    else 
    {
        Node* thisNode = StrList->head;      // Store the current head node
        while(thisNode->next)                // Go through all nodes and place the new node after the first node which it next is null (means it is the last one at that time)
        {
            thisNode = thisNode->next;
        }
        thisNode->next = InsertedNode;               // Place the new node at the end
    }
    StrList->size++;                        // Resize the StrList
}

/*-----------------------------------------------------------*/
/* This function inserts a new string node at a specific     */
/* index in the StrList, and considers two cases:            */
/* (1) Inserts the new string in the middle or at the end of */
/* the StrList                                               */
/* (2) Inserts the new string at the begining of the StrList */
/*-----------------------------------------------------------*/
void StrList_insertAt(StrList* StrList, const char* data, int index) 
{
    // Initially check if the given index is valid, the sring exists and the StrList already initialized
    if (index < 0 || data == NULL || StrList == NULL) 
    {
        return; 
    }

    Node* InsertedNode = newNode(data);     // Create a new node with the given data (see auxiliary function below)
    
    // Check if the memory allocation for the new node succeeded or not
    if(InsertedNode == NULL) 
    {
        return; 
    }

    // Case 1: Insert the new string node in the middle or at the end of the StrList
    if(index > 0) 
    {
        Node* thisNode = StrList->head;                        // "Pull-out" the first string node's pointer
        for(int i = 1; thisNode != NULL && i < index; i++)     // Go through all nodes until index or the end of the StrList, to find the specific place to insert the new node
        {
            thisNode = thisNode->next;
        }

        if(thisNode == NULL)             // StrList's size < index
        {
            free(InsertedNode->data); 
            free(InsertedNode); 
            return;
        }

        // Insert the string node in the middle or at the end
        InsertedNode->next = thisNode->next;
        thisNode->next = InsertedNode;
    }

    // Case 2: Insert the new string node at the begining of the StrList
    if(index == 0) 
    {
        InsertedNode->next = StrList->head;
        StrList->head = InsertedNode;
    } 

    StrList->size++;    // Resize the StrList
}


/*-----------------------------------------------------------*/
/* This function returns the StrList first string node       */
/*-----------------------------------------------------------*/
char* StrList_firstData(const StrList* StrList)
{
    // Initial check: if the pointer to StrList or the head is null, return nothing
    if(StrList->head == NULL || StrList == NULL)
    {
        return NULL;
    }
    
    Node* first_srt = StrList->head;       // "Pull-out" the pointer of the StrList's head 
    
    if(first_srt == NULL)                  // Check validity of the pointer
    {
        return NULL;
    }

    return first_srt->data;
}


/*-----------------------------------------------------------*/
/* This function prints the full StrList                     */
/*-----------------------------------------------------------*/
void StrList_print(const StrList* StrList) 
{
    // Initial check for valitidy
    if(StrList == NULL || StrList->head == NULL) 
    {
        return;
    }
    
    Node* thisNode = StrList->head;          // Pull-out" the pointer of the StrList's head
    while(thisNode != NULL)                  // Go through all nodes untill the end of the StrList 
    {
        printf("%s", thisNode->data);        // Print the data
        thisNode = thisNode->next;           // Move to pointer to the next string node

        if(thisNode != NULL)
        {
            printf(" ");
        }
    }
    printf("\n");
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

    Node* thisNode = StrList->head;         // Pull-out" the pointer of the StrList's head    

    for(int i = 0; i < index; i++)          // Go through all nodes until the given index 
    {
        thisNode = thisNode->next;          // Move the pointer to the next string node
    }

    printf("%s\n", thisNode->data);
}


/*-----------------------------------------------------------*/
/* This function returns the amount of chars in the Strlist  */
/*-----------------------------------------------------------*/
int StrList_printLen(const StrList* StrList)
{
    // Initial check for valitidy. If conditions meet, return an amount of zero
    if(StrList == NULL || StrList->head == NULL) 
    {
        return 0;
    }

    int total_chars = 0;             // A counter for summing the total chars in the Strlist 
    Node* thisNode = StrList->head;  // Pull-out" the pointer of the StrList's head   

    while(thisNode)
    {
        total_chars += strlen(thisNode->data);   // Add the amount of chars in the specific string (by using strlen) to the counter
        thisNode = thisNode->next;              // Move the pointer to the next string node
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
    Node* thisNode = StrList->head;     // Pull-out" the pointer of the StrList's head  
    
    while(thisNode) 
    {
        if (strcmp(thisNode->data, data) == 0)   // compare the given string (data) to the data of the current node
        {
            instances++;                        // Increment the counter
        }
        thisNode = thisNode->next;              // Move the pointer to the next string node
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
        if (strcmp((*current)->data, data) == 0)   // compare the given string (data) to the data of the current node
        {
            node_to_remove = *current;             // Assign the current node to node_to_remove 
            *current = (*current)->next;           // Connect the previous node the the next node
            free(node_to_remove->data);            // free the memory of the node_to_remove's data
            free(node_to_remove);                  // free the memory of node_to_remove (means remove it)
            StrList->size--;                       // Resize the StrList
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

    Node *thisNode = StrList->head;     // A temporary pointer to the StrList's head
    Node *prev = NULL;                  // Initiate a variable to store a pointer to the previous node
    
    // Case 1: remove the first string node
    if(index == 0) 
    {
        StrList->head = thisNode->next;     // heads will point to the next node of tmp
    } 

    // Case 2: remove a string node in the middle or at the end of the StrList
    else
    {
        for(int i = 0; thisNode != NULL && i < index; i++)     // Go through all nodes until reached to the end of the StrList or until index (The smallest among them)  
        {
            prev = thisNode;                 // Update prev to tmp (which is the next string node)
            thisNode = thisNode->next;       // Update tmp to the next string node
        }

        if (thisNode == NULL)                // If position is more than number of nodes
        {
            return; 
        }

        prev->next = thisNode->next;         // Update the next string node of prev node
    }

    free(thisNode->data);    // Free memory
    free(thisNode);
    StrList->size--;        // Resize the StrList
}


/*-----------------------------------------------------------*/
/* This function checks if two StrLists have the same string */
/* nodes; and returns 1 for TRUE, otherwise 0 for FALSE      */
/*-----------------------------------------------------------*/
int StrList_isEqual(const StrList* StrList1, const StrList* StrList2)
{
    Node* thisNode1 = StrList1->head;        // Initiate a pointer to the StrList1 head's pointer 
    Node* thisNode2 = StrList2->head;        // Initiate a pointer to the StrList2 head's pointer

    while(thisNode1 != NULL && thisNode2 != NULL)        // Go through all nodes in the two StrList simultaneously
    {
        if(strcmp(thisNode1->data, thisNode2->data) != 0)  // compare the strings (data) of the two StrList in the current position
        {
            return 0;                                    // If comparison failed, return 0 (FALSE)
        }

        // Move the pointers to the next string nodes
        thisNode1 = thisNode1->next;
        thisNode2 = thisNode2->next;
    }

    // If the two StrList reached to the end at the same time, return 1 (TRUE)
    if(thisNode1 == NULL && thisNode2 == NULL)
    {
        return 1;
    }
    return 0;
}


/*-----------------------------------------------------------*/
/* This function clones the given StrList                    */
/*-----------------------------------------------------------*/
// Global variable
StrList* cloned_list;

StrList* StrList_clone(const StrList* StrList)
{
    // Initial check: if StrList does not exist, clone cannot be performed
    if (StrList == NULL) 
    {
        return NULL;
    }

    cloned_list = StrList_alloc();
    
    // Check if allocation succeeded or not
    if (cloned_list == NULL)
    {
        return NULL;     
    }

    Node* thisNode = StrList->head;
    while(thisNode != NULL) 
    {
        // Use StrList_insertLast function to add each node to the clone
        StrList_insertLast(cloned_list, thisNode->data);
        thisNode = thisNode->next;
    }

    return cloned_list;
}


/*-----------------------------------------------------------*/
/* This function reverces the given StrList                  */
/*-----------------------------------------------------------*/
void StrList_reverse(StrList* StrList) 
{
   Node *prev = NULL;               // Initiate a variable to store a pointer to the previous node
   Node *thisNode = StrList->head;  // Initiate a pointer to the StrList head's pointer   
   Node *next = NULL;               // Initiate a variable to store a pointer to the next node

    while (thisNode != NULL) 
    {
        next = thisNode->next;  // Store the next node
        thisNode->next = prev;  // Reverse the current node's 'next' pointer to point to the previous node
        prev = thisNode;        // Update 'prev' to be the current node, moving it one step ahead for the next iteration
        thisNode = next;        // Move to the next node in the original list order
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
        swapped = 0;            // Reset the flag
        p1 = StrList->head;     // Start from the beginning of the StrList for each pass

        while (p1->next != p2)  // through all nodes until the last sorted node reached
        {
            if (strcmp(p1->data, p1->next->data) > 0)       // Compare to neighborhoods
            {
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
    Node* thisNode = StrList->head;   // "Pull-out" the pointer of the StrList's head    
    while(thisNode->next != NULL)     // Go hrough all nodes in the StrList
    {
        if (strcmp(thisNode->data, thisNode->next->data) > 0)     // Compare to neighrhood nodes' data
        {
            return 0;                 // Not sorted
        }

        thisNode = thisNode->next;    // Move the pointer to the next string node
    }

    return 1;                         // Sorted
}


/*----------------------------------------------------------*/
/*----------------------------------------------------------*/
/* Auxiliary functions                                      */ 
/*----------------------------------------------------------*/
/*----------------------------------------------------------*/

/*This function creates a new string node*/
Node* newNode(const char* data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node)); // Allocate memory for the new node
    if (newNode == NULL)         // Check if memory allocation succeeded or not
    {
        return NULL;
    }
    
    // Allocate memory for the string data
    newNode->data = (char*)malloc(strlen(data) + 1); // +1 for the null terminator
    if (newNode->data == NULL)   // Check if string memory allocation succeeded
    {
        free(newNode);           // If string allocation failed, clean up the node allocation before returning
        return NULL;
    }

    strcpy(newNode->data, data); // Copy the string data into the newly allocated memory
    newNode->next = NULL;        // Initialize the next pointer to null
    return newNode;
}

/*This functions return the data at a specific node in StrList*/
char* StrList_getAtIndex(const StrList* StrList, int index)
{
    // Check for a null list or negative index
    if (StrList == NULL || index < 0) 
    {
        return NULL;
    }

    Node* thisNode = StrList->head;
    int thisNodeIndex = 0;

    // Go through all the list until the index is reached
    while (thisNode != NULL && thisNodeIndex < index) 
    {
        thisNode = thisNode->next;
        thisNodeIndex++;
    }

    // Check if the current node is null, which means the index was out of bounds
    if (thisNode == NULL) 
    {
        return NULL;
    }
    return thisNode->data;       // Return the data at the node, which is at the given index
}