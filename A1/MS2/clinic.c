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
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    int hasData = 0;

    // check whether it is a table format 
    if (fmt == FMT_TABLE)
    {
        displayPatientTableHeader();
    }
    
    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber)
        {
            displayPatientData(&patient[i], fmt);
            hasData = 1;
        }
    }

    // if no eligible records to display
    if (!hasData)
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {
        // display search menu header
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");

        // get user input of search option
        printf("Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max);
        }
        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max);
        }

    } while (selection);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int index;
    
    // look for an available position in patient list
    index = findPatientIndexByPatientNum(0, patient, max);

    // add new patient data if there's a position available
    if (index != -1)
    {
        patient[index].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}



// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int patientNum, index;

    // get input of patient number
    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    // search the patient number
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    // check the search result
    if (index == -1)
    {
        printf("ERROR: Patient record not found!\n\n");
    }
    else
    {
        menuPatientEdit(&patient[index]);
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int patientNum, index;

    char yesOrNo;
    char cString[] = "yn";

    struct Patient emptyPatient = { 0 };

    // get input of patient number
    printf("Enter the patient number: ");
    patientNum = inputIntPositive();
    putchar('\n');

    // search the patient number
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    // check the search result
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        yesOrNo = inputCharOption(cString);

        if (yesOrNo == 'y')
        {
            patient[index] = emptyPatient;
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int patientNum, index;

    // get input of patient number
    printf("Search by patient number: ");
    patientNum = inputIntPositive();

    // search by patient number
    index = findPatientIndexByPatientNum(patientNum, patient, max);

    // display the search result
    putchar('\n');
    if (index != -1)
    {
        displayPatientData(&patient[index], FMT_FORM);
    }
    else
    {
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int i;
    int found;

    char phoneNum[PHONE_LEN + 1] = { 0 };

    // get input of patient number
    printf("Search by phone number: ");
    inputCString(phoneNum, PHONE_LEN, PHONE_LEN);
    putchar('\n');

    // display table header of result
    displayPatientTableHeader();

    // search for matchs
    found = 0;
    for (i = 0; i < max; ++i)
    {
        if (!strcmp(phoneNum, patient[i].phone.number))
        {
            found = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }

    // no matchs
    if (found == 0)
    {
        putchar('\n');
        printf("*** No records found ***\n");
    }
    putchar('\n');
    suspend();
}


// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int i;
    int largestNum = 0;

    for (i = 0; i < max; ++i)
    {
        if (patient[i].patientNumber > largestNum)
        {
            largestNum = patient[i].patientNumber;
        }
    }

    return largestNum + 1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    int found = 0;

    // search the matched element
    for (i = 0; i < max && !(found); ++i)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            found = 1;
        }
    }

    // no matchs
    if (!found)
    {
        i = 0;
    }

    // return the actual patient index
    return i - 1;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    // header
    printf("Patient Data Input\n");
    printf("------------------\n");

    // get input of new patient's name
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');

    // get input of new patient's phone
    inputPhoneData(&(patient->phone));
}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int phoneType;

    // header
    printf("Phone Information\n");
    printf("-----------------\n");

    // prompt for choosing phone type
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    phoneType = inputIntRange(1, 4);
    putchar('\n');

    // check phone type
    switch (phoneType) 
    {
    case 1:
            strcpy(phone->description, "CELL");
            break;
    case 2:
            strcpy(phone->description, "HOME");
            break;    
    case 3:
            strcpy(phone->description, "WORK");
            break;
    case 4:
            strcpy(phone->description, "TBD");
            strcpy(phone->number, "");
            break;
    }

    // input phone number if phone type is not TBD
    if (phoneType != 4)
    {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
    }
}
