#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.h"

int main() 
{
    StrList* StrList = StrList_alloc();  // Allocate memory for the user's story 
    char words[300];                     // A buffer for the user's word or sentence input for his story
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
        getchar(); 
        
        // Handle the user's decision
        switch (decision) 
        {
            // (1) Build your story by inserting word or sentence at the end
            case 1:
                int numberOfWords;
                scanf("%d", &numberOfWords);
                for (int i = 0; i < numberOfWords; i++)
                {
                    scanf("%s", words);
                    StrList_insertLast(StrList, words);
                }
                
                break;

            // (2) Insert your word or sentence at a spcific index
            case 2:
                int index;
                scanf("%d", &index);
                getchar();                                  // Remove new line (if needed)
                scanf("%300s", words);
                getchar();                                  // Remove new line (if needed)
                StrList_insertAt(StrList, words, index);
                break;
            
            // (3) Print your story
            case 3:
                StrList_print(StrList);
                break;
            
            // (4) Print length of your story
            case 4:
                printf("%zu\n", StrList_size(StrList));
                break;
            
            // (5) Print a word or sentence at a specific index
            case 5:
                scanf("%d", &index);
                printf("%s\n", StrList_getAtIndex(StrList, index));
                break;
            
            // (6) Print the total number of characters in your story
            case 6:
                int chars;                            
                chars = StrList_printLen(StrList);
                printf("%d\n", chars);
                break;
            
            // (7) Count occurrences of a string in your story
            case 7:
                scanf("%300s", words);
                getchar();                                   // Remove new line (if needed)
                int occurrences = StrList_count(StrList, words);
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
                printf("\n");
                return 0;
            
            // Dafault case
            default:
                printf("Invalid decision! Make another try...\n");
        }
    }

    return 0;
}