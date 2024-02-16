#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main() 
{
    StrList* StrList = StrList_alloc(); // Allocate memory for the string list
    char data[45];                     // A buffer for user input (the largest word in Englsh has 45 latter which is the upper bound)
    int decision;                       // A variable for the user decision

    while (1) 
    {
        printf("\n--- Creat your own story ---\n");
        printf("1: Insert string at the end\n");
        printf("2: Insert string at the index\n");
        printf("3: Print list\n");
        printf("4: Print length of the list\n");
        printf("5: Print a string at a given index\n");
        printf("6: Print the total number of characters\n");
        printf("7: Count occurrences of a string\n");
        printf("8: Delete all occurrences of a string\n");
        printf("9: Delete string at a given index\n");
        printf("10: Reverse the list\n");
        printf("11: Delete the entire list\n");
        printf("12: Sort the list\n");
        printf("13: Check if the list is sorted\n");
        printf("0: Exit\n");
        printf("Please insert your choice: ");
        scanf("%d", &decision);
        getchar(); 


        // Handle you user's decision
        switch (decision) 
        {
            case 1:
                printf("Enter string (or single character): ");
                // Read a line of text, effectively capturing single characters or strings
                fgets(data, sizeof(data), stdin);
                // Remove newline character, if present
                size_t len = strlen(data);
                if (len > 0 && data[len - 1] == '\n') 
                {
                    data[len - 1] = '\0';
                }
                StrList_insertLast(StrList, data);
                break;
            case 2:
                int index;
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter string: ");
                scanf("%255s", data);
                getchar(); // Consume newline
                StrList_insertAt(StrList, data, index);
                break;
            case 3:
                StrList_print(StrList);
                break;
            case 4:
                printf("Length of the list: %zu\n", StrList_size(StrList));
                break;
            case 5:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("String at index %d: %s\n", index, StrList_getAtIndex(StrList, index));
                break;
            case 6:
                int numChars;                            
                numChars = StrList_printLen(StrList);
                printf("Total characters in the list: %d\n", numChars);
                break;
            case 7:
                int count;
                printf("Enter string to count: ");
                scanf("%45s", data);
                getchar(); // Consume newline
                count = StrList_count(StrList, data);
                printf("Occurrences of '%s': %d\n", data, count);
                break;
            case 8:
                printf("Enter string to delete: ");
                scanf("%45s", data);
                getchar(); // Consume newline
                StrList_remove(StrList, data);
                break;
            case 9:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                getchar(); // Consume newline
                StrList_removeAt(StrList, index);
                break;
            case 10:
                StrList_reverse(StrList);
                printf("List has been reversed.\n");
                break;
            case 11:
                StrList_free(StrList);      // Free the entire StrList
                StrList = StrList_alloc();  // Reallocate a new empty list
                printf("List has been deleted.\n");
                break;
            case 12:
                StrList_sort(StrList);
                printf("List has been sorted.\n");
                break;
            case 13:
                if (StrList_isSorted(StrList)) 
                {
                    printf("The list is sorted.\n");
                } else 
                {
                    printf("The list is not sorted.\n");
                }
                break;
            case 0:
                StrList_free(StrList);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}