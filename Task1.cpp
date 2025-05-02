#include "Problem1.h"
#include <limits>

void displayMenu()
{
    cout << "Employee Management System\n";
    cout << "1. Add Employee\t\t\t";
    cout << "2. Add Project to Employee\n";
    cout << "3. Remove Employee\t\t";
    cout << "4. Update Employee with New Project \n";
    cout << "5. Display Employee Record\t";
    cout << "6. Display All Employees\n";
    cout << "7. Exit\n";
}

bool getIsCompleted()
{
    int isCompleted;
    while (true)
    {
        cout << "Is Completed (1 = Yes, 0 = No): ";
        cin >> isCompleted;
        if (isCompleted == 0 || isCompleted == 1)
        {
            return static_cast<bool>(isCompleted);
        }
        else
        {
            cout << "Invalid input. Please enter 1 for Yes or 0 for No.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    EmployeeList empList;
    int choice;
    string id, name, projectName, projectCode;
    int isCompleted;

    do
    {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            if (empList.addEmployee(id, name))
                cout << "Employee added.\n\n";
            else
                cout << "Employee ID already exists.\n\n";
            break;
        case 2:
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter Project Name: ";
            cin.ignore();
            getline(cin, projectName);
            cout << "Enter Project Code: ";
            cin >> projectCode;
            cout << "Is Completed (1 = Yes, 0 = No): ";
            cin >> isCompleted;
            if (empList.addProject(id, projectName, projectCode, getIsCompleted()))
                cout << "Project added.\n\n";
            else
                cout << "Failed to add project. Employee doesn't exists or Project code already exists.\n\n";
            break;
        case 3:
            cout << "Enter Employee ID: ";
            cin >> id;
            if (empList.removeEmployee(id))
                cout << "Employee removed.\n\n";
            else
                cout << "Employee not found.\n\n";
            break;
        case 4:
            cout << "Enter Employee ID: ";
            cin >> id;
            cout << "Enter New Project Name: ";
            cin.ignore();
            getline(cin, projectName);
            if (empList.updateEmployee(id, projectName, getIsCompleted()))
            {
                cout << "Employee updated.\n\n";
            }
            else
            {
                cout << "Employee not found.\n\n";
            }
            break;
        case 5:
            cout << "Enter Employee ID: ";
            cin >> id;
            empList.displayEmployee(id);
            break;
        case 6:
            int order;
            cout << "Display Order (0 = Ascending, other for Descending): ";
            cin >> order;
            empList.displayAllEmployees(order);
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n\n";
        }
    } while (choice != 7);

    return 0;
}
