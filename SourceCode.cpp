#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to store student details
struct Student {
    int rollNumber;
    char name[50];
    char attendance[20];  // Present / Absent
};

// Function to add a student record
void addStudent(struct Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }
    printf("\nEnter Roll Number: ");
    scanf("%d", &students[*count].rollNumber);
    printf("Enter Name: ");
    scanf(" %[^\n]s", students[*count].name);
    strcpy(students[*count].attendance, "Absent");  // Default attendance is "Absent"
    (*count)++;
    printf("Student added successfully!\n");
}

// Function to mark attendance
void markAttendance(struct Student students[], int count) {
    int roll;
    printf("\nEnter Roll Number to mark attendance: ");
    scanf("%d", &roll);
    
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == roll) {
            printf("Mark attendance for %s (P/A): ", students[i].name);
            char status;
            scanf(" %c", &status);
            if (status == 'P' || status == 'p')
                strcpy(students[i].attendance, "Present");
            else
                strcpy(students[i].attendance, "Absent");
            printf("Attendance updated!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

// Function to display attendance records
void viewAttendance(struct Student students[], int count) {
    printf("\nAttendance Record:\n");
    printf("Roll No\tName\t\tAttendance\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%s\t\t%s\n", students[i].rollNumber, students[i].name, students[i].attendance);
    }
}

// Function to save attendance data to a file
void saveToFile(struct Student students[], int count) {
    FILE *file = fopen("attendance.txt", "w");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s\n", students[i].rollNumber, students[i].name, students[i].attendance);
    }
    fclose(file);
    printf("Attendance saved successfully!\n");
}

// Function to load attendance data from a file
int loadFromFile(struct Student students[]) {
    FILE *file = fopen("attendance.txt", "r");
    if (!file) {
        return 0; // No previous data
    }
    int count = 0;
    while (fscanf(file, "%d %s %s", &students[count].rollNumber, students[count].name, students[count].attendance) != EOF) {
        count++;
    }
    fclose(file);
    return count;
}

int main() {
    struct Student students[MAX_STUDENTS];
    int count = loadFromFile(students); // Load existing data if available
    int choice;

    while (1) {
        printf("\n--- Student Attendance System ---\n");
        printf("1. Add Student\n2. Mark Attendance\n3. View Attendance\n4. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: addStudent(students, &count); break;
            case 2: markAttendance(students, count); break;
            case 3: viewAttendance(students, count); break;
            case 4: saveToFile(students, count); exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}
