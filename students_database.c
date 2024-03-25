#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS 100

struct Student {
    char name[50];
    char surname[50];
    char street[100];
    char city[50];
    int year_of_study;
};

void inputStudent(struct Student *student) {
    printf("Enter student name: ");
    scanf("%s", student->name);

    printf("Enter student surname: ");
    scanf("%s", student->surname);

    printf("Enter student street: ");
    scanf("%s", student->street);

    printf("Enter student city: ");
    scanf("%s", student->city);

    printf("Enter year of study: ");
    scanf("%d", &student->year_of_study);
}

void displayStudents(struct Student students[], int numStudents, const char universityName[]) {
    printf("\nUniversity: %s\n", universityName);
    printf("\nStudent Database:\n");

    for (int i = 0; i < numStudents; ++i) {
        printf("\nStudent %d:\n", i + 1);
        printf("Name: %s %s\n", students[i].name, students[i].surname);
        printf("Street: %s\n", students[i].street);
        printf("City: %s\n", students[i].city);
        printf("Year of Study: %d\n", students[i].year_of_study);
    }
}

void deleteLastStudent(const char *filename) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int numStudents;
    fscanf(file, "%d", &numStudents);

    if (numStudents > 0) {
        fseek(file, -sizeof(struct Student), SEEK_END);
        numStudents--;


        fprintf(file, "%d", numStudents);
        fflush(file);
        fclose(file);
        printf("Last student deleted successfully.\n");
    } else {
        fclose(file);
        printf("No students to delete.\n");
    }
}

int main() {
    FILE *fptr;
    int numStudents;
    char universityName[100];
    char command;

    printf("Enter the following commands: 'g' to gather data, 'd' to display data, 'x' to delete the last student: ");
    scanf(" %c", &command);
    if (command == 'g') {
        fptr = fopen("C:/Users/Admin/Desktop/lab_8/students.txt", "a");

        if (fptr == NULL) {
            printf("Error opening file.\n");
            return 1;
        }

        printf("Enter the number of students: ");
        scanf("%d", &numStudents);

        printf("Enter the name of the university: ");
        scanf("%s", universityName);

        struct Student students[MAX_STUDENTS];

        fprintf(fptr, "%d\n", numStudents);

        for (int i = 0; i < numStudents; ++i) {
            printf("\nEnter information for student %d:\n", i + 1);
            inputStudent(&students[i]);
        }

        displayStudents(students, numStudents, universityName);

        for (int i = 0; i < numStudents; ++i) {
            fprintf(fptr, "\nSTStudent%d:", i + 1);
            fprintf(fptr, "Name:%s %s", students[i].name, students[i].surname);
            fprintf(fptr, ", Street:%s", students[i].street);
            fprintf(fptr, ", City:%s", students[i].city);
            fprintf(fptr, ", Year of Study:%d", students[i].year_of_study);
        }

        fclose(fptr);
    } else if (command == 'd') {
        fptr = fopen("C:/Users/Admin/Desktop/lab_8/students.txt", "r");

        if (fptr == NULL) {
            printf("Error opening file.\n");
            return 1;
        }

        fscanf(fptr, "%d", &numStudents);

        struct Student students[MAX_STUDENTS];

        for (int i = 0; i < numStudents; ++i) {
            fscanf(fptr, "\nSTStudent%d:", &i);
            fscanf(fptr, "Name:%s %s", students[i].name, students[i].surname);
            fscanf(fptr, ", Street:%s", students[i].street);
            fscanf(fptr, ", City:%s", students[i].city);
            fscanf(fptr, ", Year of Study:%d", &students[i].year_of_study);
        }

        printf("\nDisplaying student information from file:\n");
        displayStudents(students, numStudents, "Unknown University");

        fclose(fptr);
    } else if (command == 'x') {
        deleteLastStudent("C:/Users/Admin/Desktop/lab_8/students.txt");
    } else {
        printf("Invalid command.\n");
    }

    return 0;
}
