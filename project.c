#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure definition
struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    int roomNumber;
    int days;
    float dailyRate;
    float medicineCost;
};

// Function declarations
void addPatient();
void displayPatients();
void searchPatient();
void updatePatient();
void generateBill();

int main() {
    int choice;

    while (1) {
        printf("\n====================================\n");
        printf("  HOSPITAL PATIENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Patient\n");
        printf("2. Display All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient Info\n");
        printf("5. Generate Patient Bill\n");
        printf("6. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                updatePatient();
                break;
            case 5:
                generateBill();
                break;
            case 6:
                printf("\nExiting program. Thank you!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}

// 1. Add Patient to Text File
void addPatient() {
    struct Patient p;
    FILE *file = fopen("patients.txt", "a");

    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\n--- Add New Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);

    printf("Enter Patient Name (Single word or use underscores): ");
    scanf("%s", p.name);

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("Enter Disease/Condition: ");
    scanf("%s", p.disease);

    printf("Enter Room Number: ");
    scanf("%d", &p.roomNumber);

    printf("Enter Days Admitted: ");
    scanf("%d", &p.days);

    printf("Enter Daily Room Charge: ");
    scanf("%f", &p.dailyRate);

    printf("Enter Medicine Cost: ");
    scanf("%f", &p.medicineCost);

    // Save as plain text
    fprintf(file, "%d %s %d %s %d %d %.2f %.2f\n",
            p.id, p.name, p.age, p.disease, p.roomNumber, p.days, p.dailyRate, p.medicineCost);

    fclose(file);
    printf("\nPatient added successfully!\n");
}

// 2. Display All Patients
void displayPatients() {
    struct Patient p;
    FILE *file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nNo patient records found!\n");
        return;
    }

    printf("\n--- All Patient Records ---\n");
    printf("%-5s %-15s %-5s %-15s %-8s %-5s\n", "ID", "Name", "Age", "Disease", "Room", "Days");
    printf("----------------------------------------------------------\n");

    while (fscanf(file, "%d %s %d %s %d %d %f %f",
                  &p.id, p.name, &p.age, p.disease, &p.roomNumber, &p.days, &p.dailyRate, &p.medicineCost) != EOF) {
        printf("%-5d %-15s %-5d %-15s %-8d %-5d\n",
               p.id, p.name, p.age, p.disease, p.roomNumber, p.days);
    }

    fclose(file);
}

// 3. Search Patient by ID
void searchPatient() {
    struct Patient p;
    int searchId, found = 0;
    FILE *file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &searchId);

    while (fscanf(file, "%d %s %d %s %d %d %f %f",
                  &p.id, p.name, &p.age, p.disease, &p.roomNumber, &p.days, &p.dailyRate, &p.medicineCost) != EOF) {
        if (p.id == searchId) {
            printf("\n--- Patient Found ---");
            printf("\nID:           %d", p.id);
            printf("\nName:         %s", p.name);
            printf("\nAge:          %d", p.age);
            printf("\nDisease:      %s", p.disease);
            printf("\nRoom Number:  %d", p.roomNumber);
            printf("\nDays:         %d", p.days);
            printf("\nDaily Rate:   %.2f", p.dailyRate);
            printf("\nMedicine:     %.2f\n", p.medicineCost);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nPatient with ID %d not found.\n", searchId);
    }

    fclose(file);
}

// 4. Update Patient Information (Using simple file replacement)
void updatePatient() {
    struct Patient p;
    int targetId, found = 0;
    FILE *file = fopen("patients.txt", "r");
    FILE *tempFile = fopen("temp.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("\nError opening records!\n");
        return;
    }

    printf("\nEnter Patient ID to update: ");
    scanf("%d", &targetId);

    while (fscanf(file, "%d %s %d %s %d %d %f %f",
                  &p.id, p.name, &p.age, p.disease, &p.roomNumber, &p.days, &p.dailyRate, &p.medicineCost) != EOF) {
        if (p.id == targetId) {
            found = 1;
            printf("\n--- Enter New Details for ID %d ---\n", targetId);

            printf("Enter New Name: ");
            scanf("%s", p.name);

            printf("Enter New Age: ");
            scanf("%d", &p.age);

            printf("Enter New Disease: ");
            scanf("%s", p.disease);

            printf("Enter New Room Number: ");
            scanf("%d", &p.roomNumber);

            printf("Enter New Days Admitted: ");
            scanf("%d", &p.days);

            printf("Enter New Daily Rate: ");
            scanf("%f", &p.dailyRate);

            printf("Enter New Medicine Cost: ");
            scanf("%f", &p.medicineCost);
        }
        // Write each record (updated or old) into the temporary file
        fprintf(tempFile, "%d %s %d %s %d %d %.2f %.2f\n",
                p.id, p.name, p.age, p.disease, p.roomNumber, p.days, p.dailyRate, p.medicineCost);
    }

    fclose(file);
    fclose(tempFile);

    // Replace original file with updated temp file
    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) {
        printf("\nPatient record updated successfully!\n");
    } else {
        printf("\nPatient with ID %d not found.\n", targetId);
    }
}

// 5. Calculate and Print the Bill
void generateBill() {
    struct Patient p;
    int targetId, found = 0;
    FILE *file = fopen("patients.txt", "r");

    if (file == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\nEnter Patient ID to generate bill: ");
    scanf("%d", &targetId);

    while (fscanf(file, "%d %s %d %s %d %d %f %f",
                  &p.id, p.name, &p.age, p.disease, &p.roomNumber, &p.days, &p.dailyRate, &p.medicineCost) != EOF) {
        if (p.id == targetId) {
            found = 1;
            float roomTotal = p.days * p.dailyRate;
            float grandTotal = roomTotal + p.medicineCost;

            printf("\n====================================\n");
            printf("            PATIENT BILL            \n");
            printf("====================================\n");
            printf("Patient ID:    %d\n", p.id);
            printf("Patient Name:  %s\n", p.name);
            printf("Room Number:   %d\n", p.roomNumber);
            printf("------------------------------------\n");
            printf("Room Charges:  %d days x %.2f = %.2f\n", p.days, p.dailyRate, roomTotal);
            printf("Medicine Cost: %.2f\n", p.medicineCost);
            printf("------------------------------------\n");
            printf("TOTAL AMOUNT:  %.2f\n", grandTotal);
            printf("====================================\n");
            break;
        }
    }

    if (!found) {
        printf("\nPatient with ID %d not found.\n", targetId);
    }

    fclose(file);
}
