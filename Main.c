#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main() 
{
    StrList* list = StrList_alloc();
    char input[256]; // Buffer for user input
    int choice, index;
    size_t numChars;
    int count;

    while (1) 
    {
        printf("\n--- Menu ---\n");
        printf("1 - Insert string at end\n");
        printf("2 - Insert string at index\n");
        printf("3 - Print list\n");
        printf("4 - Print length of the list\n");
        printf("5 - Print a string at a given index\n");
        printf("6 - Print the total number of characters\n");
        printf("7 - Count occurrences of a string\n");
        printf("8 - Delete all occurrences of a string\n");
        printf("9 - Delete string at a given index\n");
        printf("10 - Reverse the list\n");
        printf("11 - Delete the entire list\n");
        printf("12 - Sort the list\n");
        printf("13 - Check if the list is sorted\n");
        printf("0 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline left in the input buffer

        switch (choice) 
        {
            case 1:
                printf("Enter string (or single character): ");
                // Read a line of text, effectively capturing single characters or strings
                fgets(input, sizeof(input), stdin);
                // Remove newline character, if present
                size_t len = strlen(input);
                if (len > 0 && input[len - 1] == '\n') 
                {
                    input[len - 1] = '\0';
                }
                StrList_insertLast(list, input);
                break;
            case 2:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter string: ");
                scanf("%255s", input);
                getchar(); // Consume newline
                StrList_insertAt(list, input, index);
                break;
            case 3:
                StrList_print(list);
                break;
            case 4:
                printf("Length of the list: %zu\n", StrList_size(list));
                break;
            case 5:
                printf("Enter index: ");
                scanf("%d", &index);
                getchar(); // Consume newline
                printf("String at index %d: %s\n", index, StrList_getAtIndex(list, index));
                break;
            case 6:
                numChars = StrList_printLen(list);
                printf("Total characters in the list: %zu\n", numChars);
                break;
            case 7:
                printf("Enter string to count: ");
                scanf("%255s", input);
                getchar(); // Consume newline
                count = StrList_count(list, input);
                printf("Occurrences of '%s': %d\n", input, count);
                break;
            case 8:
                printf("Enter string to delete: ");
                scanf("%255s", input);
                getchar(); // Consume newline
                StrList_remove(list, input);
                break;
            case 9:
                printf("Enter index to delete: ");
                scanf("%d", &index);
                getchar(); // Consume newline
                StrList_removeAt(list, index);
                break;
            case 10:
                StrList_reverse(list);
                printf("List has been reversed.\n");
                break;
            case 11:
                StrList_free(list);  // Free the entire list
                list = StrList_alloc();  // Reallocate a new empty list
                printf("List has been deleted.\n");
                break;
            case 12:
                StrList_sort(list);
                printf("List has been sorted.\n");
                break;
            case 13:
                if (StrList_isSorted(list)) 
                {
                    printf("The list is sorted.\n");
                } else 
                {
                    printf("The list is not sorted.\n");
                }
                break;
            case 0:
                StrList_free(list);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}