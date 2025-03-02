#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structure for Student
struct Student {
    int id;
    char name[50];
    float marks;
};

// Function to add a student record
void addStudent() {
    struct Student s;
    FILE *file = fopen("students.dat", "ab");

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name); // Reads string with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, file);
    fclose(file);
    printf("✅ Student record added successfully!\n");
}

// Function to view all student records
void viewStudents() {
    struct Student s;
    FILE *file = fopen("students.dat", "rb");

    if (!file) {
        printf("❌ No student records found!\n");
        return;
    }

    printf("\n📜 Student Records:\n");
    printf("----------------------------------\n");

    while (fread(&s, sizeof(s), 1, file)) {
        printf("🆔 ID: %d | 🏷 Name: %s | 📊 Marks: %.2f\n", s.id, s.name, s.marks);
    }

    printf("----------------------------------\n");
    fclose(file);
}

// Function to search for a student by ID
void searchStudent() {
    struct Student s;
    int searchId, found = 0;
    FILE *file = fopen("students.dat", "rb");

    if (!file) {
        printf("❌ No student records found!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(s), 1, file)) {
        if (s.id == searchId) {
            printf("✅ Student Found: ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("❌ Student with ID %d not found!\n", searchId);
    }

    fclose(file);
}

// Function to delete a student record by ID
void deleteStudent() {
    struct Student s;
    int deleteId, found = 0;
    FILE *file = fopen("students.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (!file) {
        printf("❌ No student records found!\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteId);

    while (fread(&s, sizeof(s), 1, file)) {
        if (s.id == deleteId) {
            printf("✅ Student with ID %d deleted successfully!\n", deleteId);
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (!found) {
        printf("❌ Student with ID %d not found!\n", deleteId);
    }
}

// Function to export student data to a readable text file
void exportStudentsToText() {
    struct Student s;
    FILE *file = fopen("students.dat", "rb");

    if (!file) {
        printf("❌ No student records found to export!\n");
        return;
    }

    FILE *textFile = fopen("students.txt", "w");
    fprintf(textFile, "📜 Student Records\n");
    fprintf(textFile, "-----------------------------\n");

    while (fread(&s, sizeof(s), 1, file)) {
        fprintf(textFile, "🆔 ID: %d | 🏷 Name: %s | 📊 Marks: %.2f\n", s.id, s.name, s.marks);
    }

    fprintf(textFile, "-----------------------------\n");
    fclose(file);
    fclose(textFile);

    printf("✅ Student records exported to students.txt successfully!\n");
}

// Function to export student data to a CSV file
void exportStudentsToCSV() {
    struct Student s;
    FILE *file = fopen("students.dat", "rb");

    if (!file) {
        printf("❌ No student records found to export!\n");
        return;
    }

    FILE *csvFile = fopen("students.csv", "w");
    fprintf(csvFile, "ID,Name,Marks\n");

    while (fread(&s, sizeof(s), 1, file)) {
        fprintf(csvFile, "%d,%s,%.2f\n", s.id, s.name, s.marks);
    }

    fclose(file);
    fclose(csvFile);

    printf("✅ Student records exported to students.csv successfully!\n");
}

// Main function with menu-driven options
int main() {
    int choice;

    while (1) {
        printf("\n📌 Student Management System\n");
        printf("1️⃣ Add Student\n");
        printf("2️⃣ View Students\n");
        printf("3️⃣ Search Student\n");
        printf("4️⃣ Delete Student\n");
        printf("5️⃣ Export to Text File\n");
        printf("6️⃣ Export to CSV\n");
        printf("7️⃣ Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exportStudentsToText(); break;
            case 6: exportStudentsToCSV(); break;
            case 7: exit(0);
            default: printf("❌ Invalid option! Please try again.\n");
        }
    }

    return 0;
}
