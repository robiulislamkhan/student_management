#include <stdio.h>
#include <string.h>

#define MAX 100

// ----------------- Structure -----------------
typedef struct {
    int id;
    char name[50];
    float marks[5];
    float average;
    char grade;
    int totalClasses;
    int attendedClasses;
    float attendancePercent;
} Student;

Student students[MAX];
int count = 0;

// ----------------- Function Prototypes -----------------
void addStudent();
void enterMarks();
void calculateResult(int index);
void updateAttendance();
void showStudentRecord();
void showAllStudents();
char calculateGrade(float avg);

// ----------------- Main Menu -----------------
int main() {
    int choice;
    while (1) {
        printf("\n===== STUDENT RESULT & ATTENDANCE MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Enter Marks\n");
        printf("3. Update Attendance\n");
        printf("4. Show Single Student Record\n");
        printf("5. Show All Students\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: enterMarks(); break;
            case 3: updateAttendance(); break;
            case 4: showStudentRecord(); break;
            case 5: showAllStudents(); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

// ----------------- Add Student -----------------
void addStudent() {
    if (count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &students[count].id);
    printf("Enter Student Name: ");
    getchar();
    fgets(students[count].name, 50, stdin);
    students[count].name[strcspn(students[count].name, "\n")] = '\0';

    students[count].totalClasses = 0;
    students[count].attendedClasses = 0;

    printf("\nStudent added successfully!\n");
    count++;
}

// ----------------- Enter Marks -----------------
void enterMarks() {
    int id, found = -1;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter Marks for 5 Subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &students[found].marks[i]);
    }

    calculateResult(found);
}

// ----------------- Calculate Result -----------------
void calculateResult(int index) {
    float sum = 0;
    for (int i = 0; i < 5; i++)
        sum += students[index].marks[i];

    students[index].average = sum / 5.0;
    students[index].grade = calculateGrade(students[index].average);

    printf("Marks updated! Average: %.2f | Grade: %c\n",
           students[index].average, students[index].grade);
}

// ----------------- Attendance System -----------------
void updateAttendance() {
    int id, found = -1;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student not found!\n");
        return;
    }

    int total, attended;
    printf("Enter Total Classes: ");
    scanf("%d", &total);
    printf("Enter Attended Classes: ");
    scanf("%d", &attended);

    students[found].totalClasses += total;
    students[found].attendedClasses += attended;

    students[found].attendancePercent =
        (students[found].attendedClasses * 100.0) / students[found].totalClasses;

    printf("Attendance Updated! Current Attendance: %.2f%%\n",
           students[found].attendancePercent);
}

// ----------------- Show Single Student Record -----------------
void showStudentRecord() {
    int id, found = -1;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student not found!\n");
        return;
    }

    Student s = students[found];

    printf("\n----- Student Record -----\n");
    printf("ID: %d\n", s.id);
    printf("Name: %s\n", s.name);

    printf("Marks: ");
    for (int i = 0; i < 5; i++)
        printf("%.1f ", s.marks[i]);

    printf("\nAverage: %.2f\n", s.average);
    printf("Grade: %c\n", s.grade);
    printf("Attendance: %.2f%% (%d/%d)\n",
           s.attendancePercent, s.attendedClasses, s.totalClasses);
}

// ----------------- Show All Students -----------------
void showAllStudents() {
    if (count == 0) {
        printf("No students added yet!\n");
        return;
    }

    printf("\n===== ALL STUDENT RECORDS =====\n");
    for (int i = 0; i < count; i++) {
        printf("\nID: %d | Name: %s | Avg: %.2f | Grade: %c | Attendance: %.2f%%\n",
               students[i].id,
               students[i].name,
               students[i].average,
               students[i].grade,
               students[i].attendancePercent);
    }
}

char calculateGrade(float avg) {
    if (avg >= 90) return 'A';
    if (avg >= 80) return 'B';
    if (avg >= 70) return 'C';
    if (avg >= 60) return 'D';
    return 'F';
}
