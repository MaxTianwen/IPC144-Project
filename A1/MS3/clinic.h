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

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H


//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10



// MS#3 Additional macro's:
// Records and data field
#define ALL_RECORDS 1
#define NOT_ALL_RECORDS 0
#define DATA_FIELD 1
#define NO_DATA_FIELD 0

// DateTime
#define DATETIME_LEN 12

// Date
// Day
#define FIRST_DAY 1

// Month
#define FIRST_MONTH 1
#define LAST_MONTH 12

// Time
#define OPER_START 1000
#define OPER_END 1400

// Hour
#define MIN_HOUR 0
#define MAX_HOUR 23

// Minute
#define MIN_MINUTE 0
#define MAX_MINUTE 59
#define INTERVAL_MINUTE 30



//////////////////////////////////////
// Structures
//////////////////////////////////////

// Data type: Phone
struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

// Data type: Patient 
struct Patient
{
    int patientNumber;
    char name[NAME_LEN + 1];
    struct Phone phone;
};

// ------------------- MS#3 -------------------

// Data type: Time
struct Time
{
    int hour;
    int min;
};


// Data type: Date
struct Date
{
    int year;
    int month;
    int day;
};


// Data type: Appointment
struct Appointment
{
    int patientNumber;
    struct Date date;
    struct Time time;
};


// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);



//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);



// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(const struct ClinicData* data);

// View appointment schedule for the user input date
void viewAppointmentSchedule(const struct ClinicData* data);

// Add an appointment record to the appointment array
void addAppointment(struct Appointment appoints[], int maxAppointments,
                    struct Patient patients[], int maxPatient);

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment appoints[], int maxAppointments,
                       struct Patient patients[], int maxPatient);



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Patient Utility Functions
// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max);

// Check if the specified patient number exists in the patient array (return 0 if not exists)
int checkHasPatientNum(int patientNumber, const struct Patient patient[], int max);


// Appointment Utility Functions
// Sort appointments by datetime using selection sort (ascending)
void sortAppointmentsByDateTime(struct Appointment appoints[], int max);

// search and display the specified appointment record by date
void searchAppointmentIndexByDate(const struct Date searchDate, struct Appointment appoints[], 
                                  int maxAppointments, struct Patient patients[], int maxPatient);

// find the available position index for new appointment (return -1 if not found)
int findAppointmentIndexByPatientNum(int patientNumber, 
                                     const struct Appointment appoints[], int max);

// Check if the entered appointment time slot has been occupied;
int checkTimeSlotByDateTime(long long int dateTime, const struct Appointment appoints[], int max);

// Concatenate date and time to an integer type called dateTime
long long int concatDateTime(const struct Date* date, const struct Time* time);



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);

// Get user input for date
void inputDate(struct Date* date);

// Get user input for time
void inputTime(struct Time* time);



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max);


#endif // !CLINIC_H
