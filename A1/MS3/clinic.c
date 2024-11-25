/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);
            suspend();
            break;
        }
    } while (selection);
}



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
        yesOrNo = inputCharOption("yn");

        if (yesOrNo == 'y')
        {
            // set the patient record to empty
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



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data)
{
    int i;
    int patientIndex;

    // table header
    displayScheduleTableHeader(&(data->appointments->date), ALL_RECORDS);

    // loop all the appointments
    for (i = 0; i < data->maxAppointments; ++i)
    {
        patientIndex = findPatientIndexByPatientNum(data->appointments[i].patientNumber,
                                                    data->patients, data->maxPatient);
        if (patientIndex != -1)
        {
            displayScheduleData(&(data->patients[patientIndex]), &(data->appointments[i]),
                                DATA_FIELD);
        }
    }
    putchar('\n');
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data)
{
    struct Date searchDate = { 0 };

    // get input of searching date
    inputDate(&searchDate);

    // search appointment by date and display the result
    searchAppointmentIndexByDate(searchDate, data->appointments, data->maxAppointments,
                                 data->patients, data->maxPatient);
}


// Add an appointment record to the appointment array
void addAppointment(struct Appointment appoints[], int maxAppointments,
                    struct Patient patients[], int maxPatient)
{
    int appointIndex;
    int valid = 0, available, completeAdding = 0;
    long long int dateTime;

    struct Appointment tempAppoint = { 0 };

    // check if appointment list is not full
    appointIndex = findAppointmentIndexByPatientNum(0, appoints, maxAppointments);
    if (appointIndex != -1)
    {
        do {
            // get valid (existed) patient number from user
            while (!valid)
            {
                // get input of patient number
                printf("Patient Number: ");
                tempAppoint.patientNumber = inputIntPositive();

                // check if the input patient number exists
                valid = checkHasPatientNum(tempAppoint.patientNumber, patients, maxPatient);
                if (!valid)
                {
                    putchar('\n');
                    printf("ERROR: Patient number does not exist."
                           "Adding Patient before making an appointment!\n\n");
                }
            }
            // get input of date and time
            inputDate(&tempAppoint.date);
            inputTime(&tempAppoint.time);

            // convert date and time to dateTime type
            dateTime = concatDateTime(&tempAppoint.date, &tempAppoint.time);

            // check if appointment timeslot is available
            available = checkTimeSlotByDateTime(dateTime, appoints, maxAppointments);
            if (available)
            {
                // add the appointment to the list
                appoints[appointIndex] = tempAppoint;
                putchar('\n');
                printf("*** Appointment scheduled! ***\n\n");
                completeAdding = 1;

                // sort the appointment list after adding new appointment
                sortAppointmentsByDateTime(appoints, maxAppointments);
            }
            else
            {
                putchar('\n');
                printf("ERROR: Appointment timeslot is not available!\n\n");
            }

        } while (!completeAdding);
    }
    else
    {
        putchar('\n');
        printf("ERROR: Appointment listing is FULL!\n\n");
    }
}


// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appoints[], int maxAppointments,
                       struct Patient patients[], int maxPatient)
{
    int patientIndex;
    int i, hasRecord;

    char yesOrNo;   // used to store user confirmation

    struct Appointment tempAppoint = { 0 };     // temporary appointment variable to hold the input values
    struct Appointment emptyAppoint = { 0 };        // declare an empty patient structure for resetting appointment

    printf("Patient Number: ");
    tempAppoint.patientNumber = inputIntPositive();
    
    // check if the input patient number has appointment records
    hasRecord = checkHasPatientNum(tempAppoint.patientNumber, patients, maxPatient);
    if (hasRecord)
    {
        // get input date
        inputDate(&tempAppoint.date);
        putchar('\n');

        // search matched appointment in the list
        for (i = 0; i < maxAppointments; ++i)
        {
            // check if user input date matches any appointments date
            if (tempAppoint.patientNumber == appoints[i].patientNumber &&
                tempAppoint.date.year == appoints[i].date.year &&
                tempAppoint.date.month == appoints[i].date.month &&
                tempAppoint.date.day == appoints[i].date.day)
            {
                // find the patient number and display
                patientIndex = findPatientIndexByPatientNum(tempAppoint.patientNumber,
                                                            patients, maxPatient);
                displayPatientData(&patients[patientIndex], FMT_FORM);

                // ask user to confirm removing
                printf("Are you sure you want to remove this appointment (y,n): ");
                yesOrNo = inputCharOption("yn");
                putchar('\n');

                // check the user input to determine if removing
                if (yesOrNo == 'y')
                {
                    // remove the specified appointment
                    appoints[i] = emptyAppoint;
                    printf("Appointment record has been removed!\n\n");
                }
                else
                {
                    printf("Operation aborted.\n\n");
                }
            }
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

// Patient Utility Functions
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

    // search for matches
    found = 0;
    for (i = 0; i < max; ++i)
    {
        if (!strcmp(phoneNum, patient[i].phone.number))
        {
            found = 1;
            displayPatientData(&patient[i], FMT_TABLE);
        }
    }

    // no matches
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
int findPatientIndexByPatientNum(int patientNum, const struct Patient patient[], int max)
{
    int i, index = -1;

    // search the matched element
    for (i = 0; i < max && (index == -1); ++i)
    {
        if (patientNum == patient[i].patientNumber)
        {
            index = i;
        }
    }

    // return the actual patient index
    return index;
}


// Check if the specified patient number exists in the patient array (return 0 if not exists)
int checkHasPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int i, hasPatient = 0;
    
    for (i = 0; i < max && !hasPatient; ++i)
    {
        if (patientNumber == patient[i].patientNumber)
        {
            hasPatient = 1;
        }
    }

    return hasPatient;
}



// Appointment Utility Functions
// Sort the appointments by dateTime using selection sort (ascending)
void sortAppointmentsByDateTime(struct Appointment appoints[], int max)
{
    int i, j, minIndex;

    struct Appointment temp = { 0 };    // temporary variable for value exchanging

    // selection sort (ascending)
    for (i = 0; i < (max - 1); ++i)
    {
        // check if patientNumber is 0 before sorting
        if (appoints[i].patientNumber)
        {
            minIndex = i;
            for (j = i + 1; j < max; ++j)
            {
                if (appoints[j].patientNumber && 
                   (concatDateTime(&appoints[j].date, &appoints[j].time) < 
                    concatDateTime(&appoints[minIndex].date, &appoints[minIndex].time)))
                {
                    minIndex = j;
                }
            }
            // swap the value if it is needed
            if (minIndex != i)
            {
                temp = appoints[i];
                appoints[i] = appoints[minIndex];
                appoints[minIndex] = temp;
            }
        }
    }
}


// Search and display appointment record by date;
void searchAppointmentIndexByDate(const struct Date searchDate, struct Appointment appoints[], 
                                  int maxAppointments, struct Patient patients[], int maxPatient)
{
    int i, index; 
    int hasRecord = 0;

    // display table header
    putchar('\n');
    displayScheduleTableHeader(&searchDate, NOT_ALL_RECORDS);

    for (i = 0; i < maxAppointments; ++i)
    {
        // check if user input date matches any appointments date
        if (searchDate.year == appoints[i].date.year &&
            searchDate.month == appoints[i].date.month &&
            searchDate.day == appoints[i].date.day)
        {
            hasRecord = 1;
            // get the patient index for display
            index = findPatientIndexByPatientNum(appoints[i].patientNumber, patients, maxPatient);

            // check and display the result
            if (index != -1)
            {
                displayScheduleData(&(patients[index]), &(appoints[i]), NO_DATA_FIELD);
            }
        }
    }
    // no matches
    if (!hasRecord)
    {
        printf("***No records found ***\n");
    }
    putchar('\n');
}



// find the available position index for new appointment (return -1 if not found)
int findAppointmentIndexByPatientNum(int patientNumber, 
                                        const struct Appointment appoints[], int max)
{
    int i, found = 0;

    // traverse appointment list to find empty
    for (i = 0; i < max && !found; ++i)
    {
        if (patientNumber == appoints[i].patientNumber)
        {
            found = 1;
        }
    }
    // if no available position, set i = 0 (return -1)
    if (!found)
    {
        i = 0;
    }
    // return the empty index (return -1 if not found)
    return i - 1;
}



// Check if the entered appointment slot has been occupied;
int checkTimeSlotByDateTime(long long int dateTime, const struct Appointment appoints[], int max)
{
    int i, available = 1;

    for (i = 0; i < max && available; ++i)
    {
        if (dateTime == concatDateTime(&appoints[i].date, &appoints[i].time))
        {
            available = 0;
        }
    }

    return available;
}



// Concatenate date and time to an integer type called dateTime
long long concatDateTime(const struct Date* date, const struct Time* time)
{
    long long int dateTime;

    char stringDateTime[DATETIME_LEN + 1] = { 0 };

    // concatenate date and time to a C string
    sprintf(stringDateTime, "%04d%02d%02d%02d%02d",
            date->year, date->month, date->day, time->hour, time->min);

    // convert dateTime from string to long long int type
    sscanf(stringDateTime, "%lld", &dateTime);

    return dateTime;
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

// Get user input for date;
void inputDate(struct Date* date)
{
    int isLeapYear;
    int lastDay;

    // Get input of year and month
    printf("Year        : ");
    date->year = inputIntPositive();
    printf("Month (%d-%d): ", FIRST_MONTH, LAST_MONTH);
    date->month = inputIntRange(FIRST_MONTH, LAST_MONTH);

    // check input month to determine the input date range
    if (date->month == 2)
    {
        // check if it's a leap year
        isLeapYear = checkLeapYear(date->year);
        if (isLeapYear)
        {
            lastDay = 29;
        }
        else
        {
            lastDay = 28;
        }
    }
    else if (date->month == 4 || date->month == 6 || date->month == 9 || date->month == 11)
    {
        lastDay = 30;
    }
    else
    {
        lastDay = 31;
    }
    // Get input of day
    printf("Day (1-%d)  : ", lastDay);
    date->day = inputIntRange(1, lastDay);
}


// Get user input for time;
void inputTime(struct Time* time)
{
    int valid = 0;

    // get input of hour and minute until valid
    do {
        int timeSlot;

        // hour
        printf("Hour (%d-%d)  : ", MIN_HOUR, MAX_HOUR);
        time->hour = inputIntRange(MIN_HOUR, MAX_HOUR);

        // minute
        printf("Minute (%d-%d): ", MIN_MINUTE, MAX_MINUTE);
        time->min = inputIntRange(MIN_MINUTE, MAX_MINUTE);

        // concatenate the input hour and minute to one variable
        timeSlot = (100 * time->hour) + time->min;

        // check if appointment time is valid
        if ((timeSlot >= OPER_START && timeSlot <= OPER_END) && !(time->min % INTERVAL_MINUTE))
        {
            valid = 1;
        }
        else
        {
            printf("ERROR: Time must be between %02d:%02d and %02d:%02d "
                   "in %0d minute intervals.\n\n",
                   OPER_START / 100, OPER_START % 100, OPER_END / 100, OPER_END % 100,
                   INTERVAL_MINUTE);
        }
    } while (!valid);
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int i = 0;
    char fmt[FMT_LEN + 1] = { 0 };  // format array

    // save format into the fmt array for using in fscanf statement
    sprintf(fmt, "%%%d[^|]|", NAME_LEN);

    // initialize FILE pointer for reading the data
    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        // check whether number of records exceeds the array size and there are more
        // patients number to be read
        for (i = 0; i < max && fscanf(fp, "%d|", &patients[i].patientNumber) == 1; ++i)
        {
            fscanf(fp, fmt, patients[i].name);
            fscanf(fp, "%[^|]|%[^\n]", patients[i].phone.description, patients[i].phone.number);
            
            // read the new line character
            fgetc(fp);
        }
        // clean up the buffer, close the file, and release the memory
        fflush(fp);
        fclose(fp);
        fp = NULL;
    }
    else
    {
        puts("ERROR accessing file.");
    }

    // return the actual number of records
    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int i = 0;

    // declare pointers for shortening statement
    struct Date* ptrDate = NULL;
    struct Time* ptrTime = NULL;

    FILE* fp = NULL;
    fp = fopen(datafile, "r");

    if (fp != NULL)
    {
        // loop and read patient number until reaching the max number or no more patient
        for (i = 0; i < max && fscanf(fp, "%d,", &appoints[i].patientNumber) == 1; ++i)
        {
            // Store date and time to the temporary pointers
            ptrDate = &appoints[i].date;
            ptrTime = &appoints[i].time;

            // read date and time
            fscanf(fp, "%d,%d,%d,%d,%d",
                   &(ptrDate->year), &(ptrDate->month), &(ptrDate->day),
                   &(ptrTime->hour), &(ptrTime->min));

            // read the newline symbol
            fgetc(fp);
        }

        // clean up the buffer, close the file, and release the memory
        fflush(fp);
        fclose(fp);
        fp = NULL;

        // sort the appointment list after reading
        sortAppointmentsByDateTime(appoints, max);
    }
    else
    {
        puts("ERROR accessing file.\n");
    }

    // return the actual number of records
    return i;
}
