#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100

void loadEmployees();
void saveEmployees();
int getIntInput(char *prompt);
float getFloatInput(char *prompt);
void getStringInput(char *prompt, char *buffer, int size);
int isDuplicateID(int id);
int findEmployeeIndexById(int id);
void getRankInput(char *rank);
void addEmployee();
void markAttendance();
void addPerformanceReview();
void processPayroll();
void addTrainingStatus();
void viewEmployeeDetails();
void displayEmployees();
void editEmployeeDetails();
void searchEmployee();
void deleteEmployee();
void deleteAllEmployees();
void promoteEmployee();
void demoteEmployee();

struct Employee {
    int id;
    char name[50];
    float salary;
    char department[50];
    char rank[50];
    int attendance;
    float performance;
    int trainingStatus;
};

struct Employee employees[MAX_EMPLOYEES];

int main() {
    loadEmployees();
    while (1) {
        printf("\n--- Employee Management System ---\n\n");
        printf("1.  Add Employee\n");
        printf("2.  Mark Attendance\n");
        printf("3.  Add Performance Review\n");
        printf("4.  Process Payroll\n");
        printf("5.  Add Training Status\n");
        printf("6.  View Employee Details\n");
        printf("7.  View All Employees\n");
        printf("8.  Edit Employee Details\n");
        printf("9.  Search Employee\n");
        printf("10. Delete Employee\n");
        printf("11. Delete All Employees\n");
        printf("12. Promote Employee\n");
        printf("13. Demote Employee\n");
        printf("14. Exit\n");

        int choice = getIntInput("\nEnter your choice (1-14): ");

        if (choice < 1 || choice > 14) {
            printf("Invalid choice! Please select an option between 1 and 14.\n");
            continue;
        }

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: markAttendance(); break;
            case 3: addPerformanceReview(); break;
            case 4: processPayroll(); break;
            case 5: addTrainingStatus(); break;
            case 6: viewEmployeeDetails(); break;
            case 7: displayEmployees(); break;
            case 8: editEmployeeDetails(); break;
            case 9: searchEmployee(); break;
            case 10: deleteEmployee(); break;
            case 11: deleteAllEmployees(); break;
            case 12: promoteEmployee(); break;
            case 13: demoteEmployee(); break;
            case 14:
                printf("Exiting Employee Management System. Goodbye!\n");
                saveEmployees();
                exit(0);
            default:
                printf("Unexpected error occurred. Try again.\n");
        }
    }
}

void loadEmployees()
{
    FILE *file = fopen("employees.txt", "rb");
    if (file)
        {
            fread(employees, sizeof(struct Employee), MAX_EMPLOYEES, file);
            fclose(file);
        }
    else
        {
            printf("No existing data found. Initializing new data.\n");
            memset(employees, -1, sizeof(employees));
        }
}

void saveEmployees()
{
    FILE *file = fopen("employees.txt", "wb");
    if (file)
        {
            fwrite(employees, sizeof(struct Employee), MAX_EMPLOYEES, file);
            fclose(file);
        }
    else
        {
            printf("Error: Unable to save employees to file.\n");
        }
}

int getIntInput(char *prompt)
{
    int value;
    char buffer[100];
    while (1)
        {
            printf("%s", prompt);
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%d", &value) == 1)
                {
                    if (value >= 0)
                        {
                            return value;
                        }
                    else
                        {
                            printf("Error: Value cannot be negative. Please enter a valid integer.\n");
                        }
                }
            else
                {
                    printf("Invalid input. Please enter a valid integer.\n");
                }
        }
}

float getFloatInput(char *prompt)
{
    float value;
    char buffer[100];
    while (1)
        {
            printf("%s", prompt);
            if (fgets(buffer, sizeof(buffer), stdin) && sscanf(buffer, "%f", &value) == 1)
                {
                    return value;
                }
            else
                {
                    printf("Invalid input. Please enter a valid number.\n");
                }
        }
}

void getStringInput(char *prompt, char *buffer, int size)
{
    printf("%s", prompt);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

int isDuplicateID(int id)
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].id == id)
                return 1;
        }
    return 0;
}

int findEmployeeIndexById(int id)
{
    for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].id == id) return i;
        }
    return -1;
}

void getRankInput(char *rank)
{
    char choice;
    printf("\nSelect Employee Rank:\n");
    printf("S - Senior\n");
    printf("M - Mid-Level\n");
    printf("J - Junior\n");

    while (1)
        {
            printf("Enter choice (S/M/J): ");
            scanf(" %c", &choice);
            switch (choice)
                {
                    case 'S':
                    case 's':
                        strcpy(rank, "Senior");
                        return;
                    case 'M':
                    case 'm':
                        strcpy(rank, "Mid-Level");
                        return;
                    case 'J':
                    case 'j':
                        strcpy(rank, "Junior");
                        return;
                    default:
                        printf("Invalid input! Please enter S, M, or J.\n");
                }
        }
}

void addEmployee()
{
    int id = getIntInput("\nEnter Employee ID: ");
    if (isDuplicateID(id))
        {
            printf("Error: Employee with ID %d already exists.\n", id);
            return;
        }

    char name[50], department[50], rank[50];
    getStringInput("Enter Name: ", name, sizeof(name));
    getStringInput("Enter Department: ", department, sizeof(department));
    getRankInput(rank);
    fflush(stdin);

    float salary;
    while (1)
        {
            salary = getFloatInput("Enter Salary: ");
            if (salary >= 0)
                {
                    break;
                }
            else
                {
                    printf("Error: Salary cannot be negative. Please enter a valid salary.\n");
                }
        }

    for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].id == -1)
            {
                employees[i] = (struct Employee){id, "", salary, "", "", 0, 0, 0};
                strcpy(employees[i].name, name);
                strcpy(employees[i].department, department);
                strcpy(employees[i].rank, rank);
                printf("Employee %s added successfully.\n", name);
                saveEmployees();
                return;
            }
        }
    printf("Error: Employee list is full.\n");
}

void markAttendance()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to mark attendance: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            int attendance;
            while (1)
                {
                attendance = getIntInput("Enter Attendance (1 for Present, 0 for Absent): ");
                if (attendance == 0 || attendance == 1)
                    {
                        employees[idx].attendance = attendance;
                        printf("Attendance for %s updated.\n", employees[idx].name);
                        saveEmployees();
                        return;
                    }
                else
                    {
                        printf("Invalid input! Attendance must be 0 or 1.\n");
                    }
                }
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void addPerformanceReview()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID for performance review: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            float score;
            while (1)
                {
                    score = getFloatInput("Enter Performance score (0 to 10): ");
                    if (score >= 0.0 && score <= 10.0)
                        {
                            employees[idx].performance = score;
                            printf("Performance for %s updated.\n", employees[idx].name);
                            saveEmployees();
                            return;
                        }
                    else
                        {
                            printf("Invalid input! Performance score must be between 0 and 10.\n");
                        }
                }
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void processPayroll()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to process payroll: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            float payroll = employees[idx].salary;
            if (employees[idx].attendance == 0) payroll *= 0.9;
            printf("Payroll for %s: %.2f\n", employees[idx].name, payroll);
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void addTrainingStatus()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to update training status: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            int status;
            while (1)
                {
                    status = getIntInput("Enter Training Status (0 for Not Completed, 1 for Completed): ");
                    if (status == 0 || status == 1)
                        {
                            employees[idx].trainingStatus = status;
                            printf("Training status for %s updated.\n", employees[idx].name);
                            saveEmployees();
                            return;
                        }
                    else
                        {
                            printf("Invalid input! Training status must be 0 or 1.\n");
                        }
                }
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void viewEmployeeDetails()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to view details: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            struct Employee e = employees[idx];
            printf("\n--- Employee Details ---\n");
            printf("ID: %d\nName: %s\nDepartment: %s\nRank: %s\nSalary: %.2f\nAttendance: %d\nPerformance: %.2f\nTraining Status: %d\n",
                    e.id, e.name, e.department, e.rank, e.salary, e.attendance, e.performance, e.trainingStatus);
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void displayEmployees()
{
    printf("\n--- All Employees ---\n\n");
    printf("%-5s %-20s %-15s %-15s\n", "ID", "Name", "Department", "Rank");
    for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].id != -1)
                {
                    printf("%-5d %-20s %-15s %-15s\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rank);
                }
        }
}

void editEmployeeDetails() {
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to edit details: ");
    int idx = findEmployeeIndexById(id);

    if (idx != -1) {
        printf("\n--- Editing Details for %s ---\n", employees[idx].name);

        printf("Current Name: %s\n", employees[idx].name);
        getStringInput("Enter New Name: ", employees[idx].name, sizeof(employees[idx].name));

        printf("Current Department: %s\n", employees[idx].department);
        getStringInput("Enter New Department: ", employees[idx].department, sizeof(employees[idx].department));

        printf("Current Rank: %s\n", employees[idx].rank);
        printf("Select a new rank:\n");
        getRankInput(employees[idx].rank);
        fflush(stdin);
        printf("Current Salary: %.2f\n", employees[idx].salary);
        float salary = getFloatInput("Enter New Salary: ");
        if (salary >= 0) {
            employees[idx].salary = salary;
        }

        printf("Employee details updated successfully.\n");
        saveEmployees();
    } else {
        printf("Employee not found.\n");
    }
}

void searchEmployee()
{
    int option;

    do
        {
            printf("\nSearch by:\n");
            printf("1. Name\n");
            printf("2. Department\n");
            printf("3. Rank\n");

            option = getIntInput("Enter your choice (1-3): ");

            if (option < 1 || option > 3)
                {
                    printf("Invalid choice! Please select between 1 and 3.\n");
                }
        }
    while (option < 1 || option > 3);

    char searchQuery[50];
    getStringInput("Enter search keyword: ", searchQuery, sizeof(searchQuery));

    printf("\n--- Search Results ---\n");
    printf("%-5s %-20s %-15s %-15s\n", "ID", "Name", "Department", "Rank");

    int found = 0;

    for (int i = 0; i < MAX_EMPLOYEES; i++)
        {
            if (employees[i].id != -1)
                {
                    switch (option)
                        {
                            case 1:
                                if (strstr(employees[i].name, searchQuery))
                                    {
                                        printf("%-5d %-20s %-15s %-15s\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rank);
                                        found = 1;
                                    }
                                break;
                            case 2:
                                if (strstr(employees[i].department, searchQuery))
                                    {
                                        printf("%-5d %-20s %-15s %-15s\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rank);
                                        found = 1;
                                    }
                                break;
                                                        case 3:
                                if (strstr(employees[i].rank, searchQuery))
                                    {
                                        printf("%-5d %-20s %-15s %-15s\n", employees[i].id, employees[i].name, employees[i].department, employees[i].rank);
                                        found = 1;
                                    }
                                break;
                        }
                }
        }

    if (!found)
        {
            printf("No employees matched the search criteria.\n");
        }
}

void deleteEmployee()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to delete: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            employees[idx].id = -1;
            printf("Employee with ID %d deleted.\n", id);
            saveEmployees();
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void deleteAllEmployees()
{
    memset(employees, -1, sizeof(employees));
    printf("All employees deleted.\n");
    saveEmployees();
}

void promoteEmployee()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to promote: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            if (strcmp(employees[idx].rank, "Junior") == 0)
                {
                    strcpy(employees[idx].rank, "Mid-Level");
                }
            else if (strcmp(employees[idx].rank, "Mid-Level") == 0)
                {
                    strcpy(employees[idx].rank, "Senior");
                }
            else
                {
                    printf("%s is already at the highest rank.\n", employees[idx].name);
                    return;
                }
            printf("%s promoted to %s.\n", employees[idx].name, employees[idx].rank);
            saveEmployees();
        }
    else
        {
            printf("Employee not found.\n");
        }
}

void demoteEmployee()
{
    displayEmployees();
    int id = getIntInput("\nEnter Employee ID to demote: ");
    int idx = findEmployeeIndexById(id);
    if (idx != -1)
        {
            if (strcmp(employees[idx].rank, "Senior") == 0)
                {
                    strcpy(employees[idx].rank, "Mid-Level");
                }
            else if (strcmp(employees[idx].rank, "Mid-Level") == 0)
                {
                    strcpy(employees[idx].rank, "Junior");
                }
            else
                {
                    printf("%s is already at the lowest rank.\n", employees[idx].name);
                    return;
                }
            printf("%s demoted to %s.\n", employees[idx].name, employees[idx].rank);
            saveEmployees();
        }
    else
        {
            printf("Employee not found.\n");
        }
}
