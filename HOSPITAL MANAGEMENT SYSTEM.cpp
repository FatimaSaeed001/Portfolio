#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 100
#define MAX_PATIENTS 100
#define MAX_STAFF 50
#define MAX_APPOINTMENTS 100

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char gender;
    char diagnosis[MAX_NAME_LEN];
} Patient;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char position[MAX_NAME_LEN];
    char department[MAX_NAME_LEN];
} Staff;

typedef struct {
    int id;
    int patientId;
    int staffId;
    char date[MAX_NAME_LEN];
    char time[MAX_NAME_LEN];
} Appointment;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

Staff staff[MAX_STAFF];
int staffCount = 0;

Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

void bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("Appointment limit reached.\n");
        return;
    }
    Appointment newAppointment;
    printf("Enter Appointment ID: ");
    scanf("%d", &newAppointment.id);
    printf("Enter Patient ID: ");
    scanf("%d", &newAppointment.patientId);
    printf("Enter Staff ID: ");
    scanf("%d", &newAppointment.staffId);
    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%s", newAppointment.date);
    printf("Enter Time (HH:MM): ");
    scanf("%s", newAppointment.time);
    appointments[appointmentCount++] = newAppointment;
    printf("Appointment booked successfully.\n");
}

void savePatientRecords() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Patient limit reached.\n");
        return;
    }
    Patient newPatient;
    printf("Enter Patient ID: ");
    scanf("%d", &newPatient.id);
    printf("Enter Patient Name: ");
    scanf("%s", newPatient.name);
    printf("Enter Patient Age: ");
    scanf("%d", &newPatient.age);
    printf("Enter Patient Gender (M/F): ");
    scanf(" %c", &newPatient.gender);
    printf("Enter Patient Diagnosis: ");
    scanf("%s", newPatient.diagnosis);
    patients[patientCount++] = newPatient;
    printf("Patient record saved successfully.\n");
}

void viewHospitalStaff() {
    for (int i = 0; i < staffCount; i++) {
        printf("ID: %d, Name: %s, Position: %s, Department: %s\n", 
                staff[i].id, staff[i].name, staff[i].position, staff[i].department);
    }
}

void viewPatientInformation() {
    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %c, Diagnosis: %s\n", 
                patients[i].id, patients[i].name, patients[i].age, patients[i].gender, patients[i].diagnosis);
    }
}

void updatePatientInformation() {
    int id;
    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            printf("Enter New Name: ");
            scanf("%s", patients[i].name);
            printf("Enter New Age: ");
            scanf("%d", &patients[i].age);
            printf("Enter New Gender (M/F): ");
            scanf(" %c", &patients[i].gender);
            printf("Enter New Diagnosis: ");
            scanf("%s", patients[i].diagnosis);
            printf("Patient record updated successfully.\n");
            return;
        }
    }
    printf("Patient ID not found.\n");
}

void deletePatientInformation() {
    int id;
    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < patientCount - 1; j++) {
                patients[j] = patients[j + 1];
            }
            patientCount--;
            printf("Patient record deleted successfully.\n");
            return;
        }
    }
    printf("Patient ID not found.\n");
}

void printMenu() {
    printf("Hospital Management System\n");
    printf("1. Book Appointment\n");
    printf("2. Save Patient Records\n");
    printf("3. View Hospital Staff Information\n");
    printf("4. Update Patient Information\n");
    printf("5. Delete Patient Information\n");
    printf("6. View Patient Information\n");
    printf("7. Exit\n");
}

int main() {
    int choice;
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                bookAppointment();
                break;
            case 2:
                savePatientRecords();
                break;
            case 3:
                viewHospitalStaff();
                break;
            case 4:
                updatePatientInformation();
                break;
            case 5:
                deletePatientInformation();
                break;
            case 6:
                viewPatientInformation();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 7);

    return 0;
}
