#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main() 
{
    StrList* StrList = StrList_alloc();         // Allocate memory for the user's story 
    int initialSize = 300;                      // An initial buffer for the user's word or sentence input for his story
    char* buffer = (char*)malloc(initialSize);  // Allocate initial buffer
    if (buffer == NULL) 
    {
        printf("Failed to allocate memory\n");
        StrList_free(StrList);
        return -1;
    }
    int bufferSize = initialSize;
    char words[300];                     // In cases that the user requested to insert a word, allocate small size of memory
    int decision;                        // A variable for the user decision what option to choose in the menu
    
    printf("\n--------------------------------------------------------------");
    printf("\n------------------ Build your own story ----------------------");
    printf("\n--------------------------- MENU -----------------------------\n");
    printf("--------------------------------------------------------------\n");
    printf("(1) Build your story by inserting word or sentence at the end\n");
    printf("(2) Insert your word or sentence at a spcific index\n");
    printf("(3) Print your story\n");
    printf("(4) Print length of your story\n");
    printf("(5) Print a word or sentence at a specific index\n");
    printf("(6) Print the total number of characters in your story\n");
    printf("(7) Count occurrences of a string in your story\n");
    printf("(8) Delete all occurrences of a string\n");
    printf("(9) Delete string at a specific index\n");
    printf("(10) Reverse your story\n");
    printf("(11) Delete all of your story\n");
    printf("(12) Sort the story\n");
    printf("(13) Check if your story is sorted\n");
    printf("(0) Exit the program\n");
    printf("--------------------------------------------------------------\n");

    while(1) 
    {
        scanf("%d", &decision);
        getchar();      // Remove newLine character (if needed)

        // Reset buffer
        memset(buffer, 0, bufferSize);
        
        switch (decision) 
        {
            // (1) Build your story by inserting word or sentence at the end
            case 1:
            
                int numberOfWords;

                scanf("%d", &numberOfWords);
                getchar();                              // Remove newLine character (if needed)

                if (buffer[strlen(buffer) - 1] != '\n') // Handle the situation where the buffer is too small
                { 
                    int newSize = bufferSize * 2;       // Double the buffer size
                    char* newBuffer = realloc(buffer, newSize);
                    if (newBuffer == NULL) 
                    {
                        printf("Failed to expand the buffer.\n");
                        break;
                    }
                    buffer = newBuffer;
                    bufferSize = newSize;

                    // Continue reading the input
                    fgets(buffer + strlen(buffer), newSize - strlen(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character (if needed)
                }

                // Use token to read the user input
                char* token = strtok(buffer, " ");
                while (token != NULL && numberOfWords-- > 0) 
                {
                    StrList_insertLast(StrList, token); // Insert each word as a separate node
                    token = strtok(NULL, " ");
                }
                break;

            // (2) Insert your word or sentence at a spcific index
            case 2:
                int index;
                scanf("%d", &index);
                getchar();                                  // Remove new line (if needed)
                
                memset(buffer, 0, bufferSize);              // Clear existing buffer content
                
                if (buffer[strlen(buffer) - 1] != '\n')     // Handle the situation where the buffer is too small
                { 
                    int newSize = bufferSize * 2;           // Double the buffer size
                    char* newBuffer = realloc(buffer, newSize);
                    if (newBuffer == NULL) 
                    {
                        printf("Failed to expand the buffer.\n");
                        break;
                    }
                    buffer = newBuffer;
                    bufferSize = newSize;

                    // Continue reading the input
                    fgets(buffer + strlen(buffer), newSize - strlen(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = 0;          // Remove newline character (if needed)
                    StrList_insertAt(StrList, buffer, index);   // Inserts a string at the specified index
                }
                break;
            
            // (3) Print your story
            case 3:
                StrList_print(StrList);
                // printf("\n");
                break;
            
            // (4) Print length of your story
            case 4:
                printf("%zu\n", StrList_size(StrList));
                break;
            
            // (5) Print a word or sentence at a specific index
            case 5:
                scanf("%d", &index);
                printf("%s\n", StrList_getAtIndex(StrList, index));
                // printf("\n");
                break;
            
            // (6) Print the total number of characters in your story
            case 6:
                int chars;                            
                chars = StrList_printLen(StrList);
                printf("%d\n", chars);
                break;
            
            // (7) Count occurrences of a string in your story
            case 7:
                char str[100];
                scanf("%s", str);
                getchar();                                   // Remove new line (if needed)
                
                int occurrences = StrList_count(StrList, str);
                printf("%d\n", occurrences);
                break;
            
            // Delete all occurrences of a string
            case 8:
                scanf("%300s", words);
                getchar();                                  // Remove new line (if needed)
                StrList_remove(StrList, words);
                break;
            
            // (9) Delete string at a specific index
            case 9:
                scanf("%d", &index);
                getchar();                                  // Remove new line (if needed)
                StrList_removeAt(StrList, index);
                break;
            
            // (10) Reverse your story
            case 10:
                free(buffer); 
                StrList_reverse(StrList);
                break;
            
            // (11) Delete all of your story
            case 11:
                StrList_free(StrList);                      // Free the entire StrList
                StrList = StrList_alloc();                  // Reallocate a new empty list
                break;
            
            // (12) Sort the story
            case 12:
                StrList_sort(StrList);
                break;
            
            // (13) Check if your story is sorted 
            case 13:
                if (StrList_isSorted(StrList) == 1) 
                {
                    printf("true\n");
                } 
                else if(StrList_isSorted(StrList) == 0) 
                {
                    printf("false\n");
                }
                break;
            
            // (0) Exit the program
            case 0:
                StrList_free(StrList);                       // Free the entire StrList  
                // printf("\n");
                return 0;
            
            // Dafault case
            default:
                printf("Invalid decision! Make another try...\n");
        }

        // Reset buffer to its initial size after each run if needed
        if (bufferSize != initialSize) 
        {
            char* temp = realloc(buffer, initialSize);
            if (temp == NULL) 
            {
                printf("Failed to reallocate buffer to the initial size.\n");
                break; 
            }
            bufferSize = initialSize; // Ensure bufferSize is updated
            memset(buffer, 0, bufferSize); // Clear the buffer after resizing
        }
    }

    return 0;
}