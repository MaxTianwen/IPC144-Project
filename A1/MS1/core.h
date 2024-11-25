/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 1
Full Name  : Tianwen Wang
Student ID#: 151583226
Email      : twang118@myseneca.ca
Section    : ZAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

//--------------------------------------------
/* prototypes of input validation functions
 * core.h
 */
 //--------------------------------------------

#define STR_LEN 2000
#define FMT_LEN 20
#define NUM_DIGITS 10

// Clear the standard input buffer
void clearInputBuffer(void); 

// Wait for user to input the "enter" key to continue
void suspend(void);

// Get a valid integer input
int inputInt(void);

// Get a valid positive integer input
int inputIntPositive(void);

// Get an integer input within the specified range
int inputIntRange(int lowerBound, int upperBound);

// Get a char input matches any of the characters in the specified C string array
char inputCharOption(const char cStringArr[]);

// Get a C string input with a length between specified range
void inputCString(char* ptrCString, int minLen, int maxLen);

// Display a formatted phone number that has exact 10 digits
void displayFormattedPhone(const char* ptrCString);
