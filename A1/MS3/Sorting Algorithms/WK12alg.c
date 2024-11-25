/***************************************************************************
Course:         IPC144
Description:    Demonstrates Sorting Algorithms:
                - Selection
                - Bubble
				
				-NOTE: Check out the links for animated examples of how
				       these algorithms work (below in function comments)
					   
***************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>  // Used in C String array sorting

#define MAXSIZE 5
#define MAX_STR_LEN 50

void selectionSort(int array[], int arrayLength);                  // selection sort algorithm
void bubbleSortEndBeg(int array[], int arrayLength);               // bubble sort algorithm (processes from END to beginning)
void bubbleSortBegEnd(int array[], int arrayLength);               // bubble sort algorithm (processes from BEGINNING to end)
void bubbleSortCStr(char strArray[][MAX_STR_LEN + 1], int rowNums);// bubble sort algorithm (C String sort example)

// Helper display functions
void displayIntArray(const char *title, int array[], int arrayLength);
void displayStrArray(const char *title, char strArray[][MAX_STR_LEN + 1], int rowNums);

int algmain(void)
{
    int i;
    int skuSel[] = { 2, 6, 4, 3, 5 };
    int skuBub1[] = { 2, 6, 4, 3, 5 };
    int skuBub2[] = { 2, 6, 4, 3, 5 };
	
    // 2-DIMENSION C STRING ARRAY: 5 WORDS, EACH WORD UP TO 50 MEANINGFUL CHARACTERS (+1 FOR NULL)
    char cstrArray[MAXSIZE][MAX_STR_LEN + 1] = {
        "Young Name",
        "Middle-aged Name",
        "Teenage Name",
        "Baby Name",
        "Old-aged Name" };

    // Display UNSORTED...
    displayIntArray("Selection sort (BEFORE sort):", skuSel, MAXSIZE);
    // Sort the array
    selectionSort(skuSel, MAXSIZE);
    // Display sorted!
    displayIntArray("    SORTED (ascending order):", skuSel, MAXSIZE);

    // Display UNSORTED...
    displayIntArray("Bubble sort (BEFORE sort):", skuBub1, MAXSIZE);
    // Sort the array
    bubbleSortEndBeg(skuBub1, MAXSIZE);
    // Display sorted!
    displayIntArray("    SORTED (ascending order [End to Beginning]):", skuBub1, MAXSIZE);

    // Display UNSORTED...
    displayIntArray("Bubble sort (BEFORE sort):", skuBub2, MAXSIZE);
    // Sort all the array
    bubbleSortBegEnd(skuBub2, MAXSIZE);
    // Display sorted!
    displayIntArray("    SORTED (ascending order [Beginning to End]):", skuBub2, MAXSIZE);

    // Display UNSORTED...
    displayStrArray("Bubble sort (BEFORE sort):", cstrArray, MAXSIZE);
    // Sort the array
    bubbleSortCStr(cstrArray, MAXSIZE);
    // Display sorted!
    displayStrArray("SORTED (ascending order [Beginning word to Last word]):", cstrArray, MAXSIZE);

    return 0;
}

// selection sort algorithm (ascending)
// Check Visual Animation: http://cathyatseneca.github.io/DSAnim/web/selection.html
void selectionSort(int array[], int arrayLength)
{
    int iterIdx, tstElemIdx, curMinIdx;
    int tempVal;

    for (iterIdx = 0; iterIdx < arrayLength; iterIdx++) 
    {
        curMinIdx = iterIdx;

        for (tstElemIdx = iterIdx + 1; tstElemIdx < arrayLength; tstElemIdx++) 
        {
            // check if the test element is < our current marked lowest value
            if (array[tstElemIdx] < array[curMinIdx]) 
            {
                curMinIdx = tstElemIdx; // mark the test element index as the next lowest
            }
        }
        // Swap needs to be done!
        if (curMinIdx != iterIdx) 
        {
            tempVal = array[iterIdx];
            array[iterIdx] = array[curMinIdx];
            array[curMinIdx] = tempVal;
        }
    }
}

// Bubble Sort (ascending)
// - Processes from END to beginning
// As shown in course notes: http://scs.senecacollege.ca/~ipc144/pages/content/sorts.html#sor
void bubbleSortEndBeg(int array[], int arrayLength)
{
    int curPass, iterIdx;
    int tmpVal;

    // Start: @end of array and work towards the beginning
    for (curPass = arrayLength - 1; curPass > 0; curPass--)
    {
        for (iterIdx = 0; iterIdx < curPass; iterIdx++)
        {
            if (array[iterIdx] > array[iterIdx + 1])
            {
                tmpVal = array[iterIdx];
                array[iterIdx] = array[iterIdx + 1];
                array[iterIdx + 1] = tmpVal;
            }
        }
    }
}

// Bubble Sort (ascending): 
// - Processes from BEGINNING to end
// Check Visual Animation: http://cathyatseneca.github.io/DSAnim/web/bubble.html
void bubbleSortBegEnd(int array[], int arrayLength)
{
    int curPass, iterIdx, tmpVal;
    int maxPasses = arrayLength - 1;  // Will only ever have to loop 1 less than the number of elements

    // Total number of passes will be the array length - 1 (Start @BEGINNING)
    for (curPass = 0; curPass < maxPasses; curPass++)
    {
        // Within each pass; check each neighbouring values and swap accordingly
        // - start at beginning and work up to the end less the number of passes completed
        for (iterIdx = 0; iterIdx < (maxPasses - curPass); iterIdx++)
        {
            // Compare the current number with the next one in the list (the neighbour)
            // - Move the number from the left-side to the right-side neighbouring element if it is greater
            if (array[iterIdx] > array[iterIdx + 1])
            {
                // Swap neighbouring values
                tmpVal = array[iterIdx];
                array[iterIdx] = array[iterIdx + 1];
                array[iterIdx + 1] = tmpVal;
            }
        }
    }
}

// Bubble Sort (ascending):
// C String sort example (processes from BEGINNING word to last word)
void bubbleSortCStr(char strArray[][MAX_STR_LEN + 1], int rowNums)
{
    int i, j;
    char temp[MAX_STR_LEN + 1] = { '\0' };

    for (i = 0; i < rowNums; i++)
    {
        for (j = 0; j < (rowNums - i - 1); j++)
        {
            // String compare with adjacent indexed word (if current element word is > the next, swap them):
            if (strcmp(strArray[j], strArray[j + 1]) > 0)
            {
                // Swap position in the "rows" (words) dimension
                strcpy(temp, strArray[j]);           // use string copy to move c string values
                strcpy(strArray[j], strArray[j + 1]);
                strcpy(strArray[j + 1], temp);
            }
        }
    }
}


//----------------------------------------------------------------------
// Display functions
//----------------------------------------------------------------------

void displayIntArray(const char *title, int array[], int arrayLength)
{
    int i;

    puts(title);
    for (i = 0; i < arrayLength; i++)
    {
        printf("%5d", array[i]);
    }
    puts("\n");
}

void displayStrArray(const char *title, char strArray[][MAX_STR_LEN + 1], int rowNums)
{
    int i;

    puts(title);
    for (i = 0; i < rowNums; i++)
    {
        printf("%d) %s\n", i + 1, strArray[i]);
    }
    puts("\n");
}
