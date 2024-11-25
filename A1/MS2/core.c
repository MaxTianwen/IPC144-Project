/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : Tianwen Wang
Student ID#: 151583226
Email      : twang118@myseneca.ca
Section    : ZAA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>

#include "core.h"

//
// Copy your work done from Milestone #1 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// - Also copy the commented "sections" to help with finding functions quickly!
//

// Clear the standard input buffer 
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer: 
    while (getchar() != '\n')
    {
        ; // do nothing! 
    }
}

// Wait for user to input the "enter" key to continue 
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// Get a valid integer input and return it
int inputInt(void)
{
    int intValue, valid;
    char charValue = 'x';

    do {
        valid = 1;
        scanf("%d%c", &intValue, &charValue);

        if (charValue != '\n')
        {
            valid = 0;
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    } while (!valid);

    return intValue;
}

// Get a valid positive integer input and return it
int inputIntPositive(void)
{
    int intPositive, valid;

    do {
        intPositive = inputInt();
        valid = 1;

        if (intPositive < 0)
        {
            valid = 0;
            printf("ERROR! Value must be > 0: ");
        }
    } while (!valid);

    return intPositive;
}

// Get an integer input within the specified range
int inputIntRange(int lowerBound, int upperBound)
{
    int intValue, valid;

    do {
        intValue = inputInt();
        valid = 1;

        if (intValue < lowerBound || intValue > upperBound)
        {
            valid = 0;
            printf("ERROR! Value must be between %d and %d inclusive: ",
                lowerBound, upperBound);
        }
    } while (!valid);

    return intValue;
}


// Get a char input matches any of the characters in the specified C string array
char inputCharOption(const char cString[])
{
    int valid, i;
    char search, charValue = 'x';

    do {
        valid = 0;
        scanf("%c%c", &search, &charValue);

        // clear input buffer if it is not empty
        if (charValue != '\n')
        {
            clearInputBuffer();
        }
        else
        {
            // check if the input character in the specified C string array
            for (i = 0; cString[i] != '\0' && !valid; ++i)
            {
                if (search == cString[i])
                {
                    valid = 1;
                }
            }
        }

        // if the input character is invalid, display error message
        if (!valid)
        {
            printf("ERROR: Character must be one of [%s]: ", cString);
        }
    } while (!valid);

    return search;
}

// Get a C string input with a length between specified range
void inputCString(char cString[], int minLen, int maxLen)
{
    int i, valid;
    char str[STR_LEN + 1] = { 0 };
    char fmt[FMT_LEN + 1] = { 0 };

    do {
        valid = 1;

        // save format into the fmt array and use it int the scanf statement
        sprintf(fmt, "%%%d[^\n]", FMT_LEN);
        scanf(fmt, str);
        clearInputBuffer();     // clear input buffer if it is not empty

        // get the number of characters in the char array
        for (i = 0; str[i] != '\0'; ++i)
        {
            ;
        }

        // determine whether the C string is valid
        if ((minLen == maxLen) && (i != minLen))
        {
            valid = 0;
            printf("ERROR: String length must be exactly %d chars: ", minLen);
        }
        else if (i > maxLen)
        {
            valid = 0;
            printf("ERROR: String length must be no more than %d chars: ", maxLen);
        }
        else if (i < minLen)
        {
            valid = 0;
            printf("ERROR: String length must be between %d and %d chars: ", minLen, maxLen);
        }
        else
        {
            for (i = 0; str[i] != '\0'; ++i)
            {
                cString[i] = str[i];
            }
            cString[i] = '\0';
        }
    } while (!valid);
}

// Display a formatted phone number that has exact 10 digits
void displayFormattedPhone(const char cString[])
{
    int i;
    int valid = 1;

    if (cString == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        // calculate the number of characters
        for (i = 0; cString[i] != '\0' && valid; ++i)
        {
            if (!isdigit(cString[i]))
            {
                valid = 0;
            }
        }

        if (valid && i == NUM_DIGITS)
        {
            printf("(%3.3s)%3.3s-%4.4s", cString, cString + 3, cString + 6);
        }
        else
        {
            printf("(___)___-____");
        }
    }
}
