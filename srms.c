#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// ------------------ STRUCT & GLOBALS ------------------
typedef struct
{
    int roll_number;
    char first_name[20];
    char last_name[20];
    char email[30];
    char course_code[10];
    float marks;
} Student;

Student *students = NULL;
int studentCount = 0;
bool ProgramIsRunning = true;
const char *FILENAME = "studentrecords.txt"; // default file

// ------------------ FUNCTION DECLARATIONS ------------------
void Menu();
void ShowAllStudents();
void AddStudent();
void SearchStudent();
void ModifyStudent();
void RemoveStudent();
void RemoveAllStudents();
void LoadStudentRecords();
void SaveToFile();
void GoBackOrExit();
int isValidEmail(const char *email);
void greet();

// ------------------ MAIN FUNCTION ------------------
int main()
{
    system("cls");
    printf("Welcome!\n");
    printf("Student Management System is starting...\n\n");
    LoadStudentRecords(); // auto load from studentrecords.txt

    while (ProgramIsRunning)
    {
        Menu();
        int Option;
        scanf("%d", &Option);

        switch (Option)
        {
        case 0:
            ProgramIsRunning = false;
            break;
        case 1:
            system("cls");
            ShowAllStudents();
            GoBackOrExit();
            break;
        case 2:
            system("cls");
            AddStudent();
            GoBackOrExit();
            break;
        case 3:
            system("cls");
            SearchStudent();
            GoBackOrExit();
            break;
        case 4:
            system("cls");
            ModifyStudent();
            GoBackOrExit();
            break;
        case 5:
            system("cls");
            RemoveStudent();
            GoBackOrExit();
            break;
        case 6:
            system("cls");
            RemoveAllStudents();
            GoBackOrExit();
            break;
        case 7:
            system("cls");
            LoadStudentRecords();
            GoBackOrExit();
            break;
        case 8:
            system("cls");
            SaveToFile();
            GoBackOrExit();
            break;
        default:
            system("cls");
            printf("\nInvalid choice! Please enter a number between 0 and 8.\n");
            break;
        }
    }

    SaveToFile(); // auto-save before exit
    printf("\nAll records saved. Exiting program...\n");
    return 0;
}

// ------------------ FUNCTIONS ------------------

/*void greet()
{
    char name[50];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    if (name[0] == '\n')
        fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("\nWelcome, %s!\n", name);
    printf("Student Management System is starting...\n\n");
}*/

void Menu()
{
    printf("\n\t==============================\n");
    printf("\t        MAIN MENU\n");
    printf("\t==============================\n");
    printf("\t[1] Show All Students\n");
    printf("\t[2] Add A New Student\n");
    printf("\t[3] Search For A Student\n");
    printf("\t[4] Modify Student Details\n");
    printf("\t[5] Remove A Student\n");
    printf("\t[6] Remove All Students\n");
    printf("\t[7] Load Student Records\n");
    printf("\t[8] Save To File\n");
    printf("\t[0] Exit The Program\n");
    printf("\t==============================\n");
    printf("\tEnter Your Choice: ");
}

int isValidEmail(const char *email)
{
    const char *at = strchr(email, '@');
    if (!at || at == email)
        return 0;

    const char *dot = strrchr(at, '.');
    if (!dot || dot < at + 2)
        return 0;

    for (int i = 0; email[i]; i++)
        if (isspace(email[i]))
            return 0;

    return 1;
}

void ShowAllStudents()
{
    if (studentCount == 0)
    {
        printf("\nNo student records available.\n");
        return;
    }

    printf("\n%-6s %-12s %-12s %-25s %-10s %-7s\n", "Roll", "First Name", "Last Name", "Email", "Course", "Marks");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < studentCount; i++)
    {
        printf("%-6d %-12s %-12s %-25s %-10s %.2f\n",
               students[i].roll_number,
               students[i].first_name,
               students[i].last_name,
               students[i].email,
               students[i].course_code,
               students[i].marks);
    }
}

void AddStudent()
{
    studentCount++;
    students = realloc(students, studentCount * sizeof(Student));
    if (!students)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    Student *s = &students[studentCount - 1];

    printf("Enter Roll Number: ");
    scanf("%d", &s->roll_number);
    printf("Enter First Name: ");
    scanf("%s", s->first_name);
    printf("Enter Last Name: ");
    scanf("%s", s->last_name);

    do
    {
        printf("Enter Email: ");
        scanf("%s", s->email);
        if (!isValidEmail(s->email))
            printf("Invalid email format!\n");
    } while (!isValidEmail(s->email));

    printf("Enter Course Code: ");
    scanf("%s", s->course_code);

    do
    {
        printf("Enter Marks (0-100): ");
        scanf("%f", &s->marks);
    } while (s->marks < 0 || s->marks > 100);

    printf("\n✅ Student added successfully!\n");
}

void SearchStudent()
{
    if (studentCount == 0)
    {
        printf("No records available.\n");
        return;
    }

    int roll;
    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].roll_number == roll)
        {
            printf("\nStudent Found:\n");
            printf("Name: %s %s\nEmail: %s\nCourse: %s\nMarks: %.2f\n",
                   students[i].first_name, students[i].last_name,
                   students[i].email, students[i].course_code,
                   students[i].marks);
            return;
        }
    }
    printf("Student not found!\n");
}

void ModifyStudent()
{
    if (studentCount == 0)
    {
        printf("No records.\n");
        return;
    }

    int roll, found = -1;
    printf("Enter Roll Number to modify: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++)
        if (students[i].roll_number == roll)
            found = i;

    if (found == -1)
    {
        printf("Student not found.\n");
        return;
    }

    printf("Enter New First Name: ");
    scanf("%s", students[found].first_name);
    printf("Enter New Last Name: ");
    scanf("%s", students[found].last_name);
    printf("Enter New Email: ");
    scanf("%s", students[found].email);
    printf("Enter New Course Code: ");
    scanf("%s", students[found].course_code);
    printf("Enter New Marks: ");
    scanf("%f", &students[found].marks);

    printf("\n✅ Student details updated!\n");
}

void RemoveStudent()
{
    if (studentCount == 0)
    {
        printf("No records.\n");
        return;
    }

    int roll, found = -1;
    printf("Enter Roll Number to remove: ");
    scanf("%d", &roll);

    for (int i = 0; i < studentCount; i++)
        if (students[i].roll_number == roll)
            found = i;

    if (found == -1)
    {
        printf("Student not found.\n");
        return;
    }

    for (int i = found; i < studentCount - 1; i++)
        students[i] = students[i + 1];
    studentCount--;
    students = realloc(students, studentCount * sizeof(Student));

    printf("✅ Student removed successfully.\n");
}

void RemoveAllStudents()
{
    free(students);
    students = NULL;
    studentCount = 0;
    printf("✅ All student records deleted.\n");
}

void LoadStudentRecords()
{
    FILE *file = fopen(FILENAME, "r");
    if (!file)
    {
        printf("No existing record file found. Starting fresh.\n");
        return;
    }

    Student temp;
    studentCount = 0;
    students = NULL;

    while (fscanf(file, "%d %s %s %s %s %f",
                  &temp.roll_number,
                  temp.first_name,
                  temp.last_name,
                  temp.email,
                  temp.course_code,
                  &temp.marks) == 6)
    {
        studentCount++;
        students = realloc(students, studentCount * sizeof(Student));
        students[studentCount - 1] = temp;
    }

    fclose(file);
    printf("✅ %d student record(s) loaded from %s.\n", studentCount, FILENAME);
}

void SaveToFile()
{
    FILE *file = fopen(FILENAME, "w");
    if (!file)
    {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < studentCount; i++)
    {
        fprintf(file, "%d %s %s %s %s %.2f\n",
                students[i].roll_number,
                students[i].first_name,
                students[i].last_name,
                students[i].email,
                students[i].course_code,
                students[i].marks);
    }

    fclose(file);
    printf("✅ All records saved to %s.\n", FILENAME);
}

void GoBackOrExit()
{
    char opt;
    printf("\nPress 'b' to go back or '0' to exit: ");
    scanf(" %c", &opt);
    if (opt == '0')
        ProgramIsRunning = false;
    system("cls");
}
