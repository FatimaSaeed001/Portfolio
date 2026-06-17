#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TOTAL_SLOTS 5
#define FILE_NAME "parking_data.txt"
#define REPORT_FILE "daily_report.txt"
#define PASSWORD "admin123"

typedef struct {
    int slotNo;
    char carNumber[20];
    time_t entryTime;
    int isOccupied;
} ParkingSlot;

ParkingSlot slots[TOTAL_SLOTS];
void loadData() {
    FILE *fp = fopen(FILE_NAME, "r");

    for(int i = 0; i < TOTAL_SLOTS; i++) {
        slots[i].slotNo = i + 1;
        slots[i].isOccupied = 0;
        strcpy(slots[i].carNumber, "");
        slots[i].entryTime = 0;
    }
    if(fp == NULL) return;
    for(int i = 0; i < TOTAL_SLOTS; i++) {
        fscanf(fp, "%d %s %ld %d",
               &slots[i].slotNo,
               slots[i].carNumber,
               &slots[i].entryTime,
               &slots[i].isOccupied);
    }
    fclose(fp);
}

void saveData() {
    FILE *fp = fopen(FILE_NAME, "w");

    for(int i = 0; i < TOTAL_SLOTS; i++) {
        fprintf(fp, "%d %s %ld %d\n",
                slots[i].slotNo,
                slots[i].carNumber,
                slots[i].entryTime,
                slots[i].isOccupied);
    }
    fclose(fp);
}

void saveReport(char car[], double bill) {
    FILE *fp = fopen(REPORT_FILE, "a");
    time_t now = time(NULL);

    fprintf(fp, "Car: %s | Bill: %.2f | Time: %s",
            car, bill, ctime(&now));
    fclose(fp);
}
void showStatus() {
    int occupied = 0;
    printf("\n----- PARKING STATUS -----\n");
    for(int i = 0; i < TOTAL_SLOTS; i++) {
        if(slots[i].isOccupied) {
            printf("Slot %d: OCCUPIED | Car: %s\n",
                   slots[i].slotNo, slots[i].carNumber);
            occupied++;
        } else {
            printf("Slot %d: EMPTY\n", slots[i].slotNo);
        }
    }
    printf("\nTotal Cars: %d", occupied);
    printf("\nFree Slots: %d\n", TOTAL_SLOTS - occupied);
}

void parkCar() {
    char carNum[20];
    printf("\nEnter Car Number: ");
    scanf("%s", carNum);
    for(int i = 0; i < TOTAL_SLOTS; i++) {
        if(slots[i].isOccupied == 0) {
            slots[i].isOccupied = 1;
            strcpy(slots[i].carNumber, carNum);
            slots[i].entryTime = time(NULL);
            printf("\nCar Parked at Slot %d\n", slots[i].slotNo);
            saveData();
            return;
        }
    }
    printf("\nParking Full!\n");
}

void removeCar() {
    char carNum[20];
    printf("\nEnter Car Number: ");
    scanf("%s", carNum);
    for(int i = 0; i < TOTAL_SLOTS; i++) {
        if(slots[i].isOccupied && strcmp(slots[i].carNumber, carNum) == 0) {
            time_t exitTime = time(NULL);
            double seconds = difftime(exitTime, slots[i].entryTime);
            double hours = seconds / 3600;
            double rate = 50.0;
            double bill = hours * rate;
            printf("\nCar Removed from Slot %d\n", slots[i].slotNo);
            printf("Time: %.2f hours\n", hours);
            printf("Bill: Rs %.2f\n", bill);
            saveReport(carNum, bill);
            slots[i].isOccupied = 0;
            strcpy(slots[i].carNumber, "");
            slots[i].entryTime = 0;
            saveData();
            return;
        }
    }
    printf("\nCar Not Found!\n");
}

void searchCar() {
    char carNum[20];
    printf("\nEnter Car Number to Search: ");
    scanf("%s", carNum);
    for(int i = 0; i < TOTAL_SLOTS; i++) {
        if(slots[i].isOccupied && strcmp(slots[i].carNumber, carNum) == 0) {
            printf("\nCar Found!\n");
            printf("Slot No: %d\n", slots[i].slotNo);
            return;
        }
    }
    printf("\nCar Not Found!\n");
}

int login() {
    char pass[20];
    printf("Enter Admin Password: ");
    scanf("%s", pass);
    if(strcmp(pass, PASSWORD) == 0)
        return 1;
    return 0;
}

int main() {
    int choice;
    if(!login()) {
        printf("Wrong Password! Access Denied.\n");
        return 0;
    }
    loadData();
    
    while(1) {
        printf("\n===== CAR PARKING SYSTEM =====\n");
        printf("1. Park Car\n");
        printf("2. Remove Car (Billing)\n");
        printf("3. Show Status\n");
        printf("4. Search Car\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: parkCar(); break;
            case 2: removeCar(); break;
            case 3: showStatus(); break;
            case 4: searchCar(); break;
            case 5:
                saveData();
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid Choice!\n");
        }
    }
}