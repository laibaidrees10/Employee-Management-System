#include <iostream>
#include <string>
using namespace std;

struct Project
{
    string name;
    string code;
    bool completed;
    Project *next;

    Project(const string &pname, const string &pcode, bool status)
        : name(pname), code(pcode), completed(status), next(nullptr) {}
};

struct EmployeeInfo
{
    string name;
    string id;
    Project *projects;

    EmployeeInfo(const string &ename, const string &eid)
        : name(ename), id(eid), projects(nullptr) {}
};

class Employee
{
public:
    EmployeeInfo info;
    Employee *prev;
    Employee *next;

    Employee(const EmployeeInfo &einfo)
        : info(einfo), prev(nullptr), next(nullptr) {}
};

class EmployeeList
{
private:
    Employee *head;

    Employee *findEmployee(const string &id)
    {
        Employee *current = head;
        while (current)
        {
            if (current->info.id == id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

public:
    EmployeeList() : head(nullptr) {}
    ~EmployeeList()
    {
        while (head)
        {
            Employee *temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool addEmployee(const string &id, const string &name)
    {
        if (findEmployee(id))
            return false;

        EmployeeInfo empInfo(name, id);
        Employee *newEmployee = new Employee(empInfo);

        if (!head || head->info.id > id)
        {
            newEmployee->next = head;
            if (head)
                head->prev = newEmployee;
            head = newEmployee;
        }
        else
        {
            Employee *current = head;
            while (current->next && current->next->info.id < id)
                current = current->next;

            newEmployee->next = current->next;
            if (current->next)
                current->next->prev = newEmployee;
            current->next = newEmployee;
            newEmployee->prev = current;
        }
        return true;
    }

    bool addProject(const string &id, const string &projectName, const string &projectCode, int isCompleted)
    {
        Employee *employee = findEmployee(id);
        if (!employee)
            return false;

        Project *current = employee->info.projects;
        while (current)
        {
            if (current->code == projectCode)
                return false;
            current = current->next;
        }

        Project *newProject = new Project(projectName, projectCode, isCompleted);
        newProject->next = employee->info.projects;
        employee->info.projects = newProject;
        return true;
    }

    bool removeEmployee(const string &id)
    {
        Employee *employee = findEmployee(id);
        if (!employee)
            return false;

        if (employee->prev)
            employee->prev->next = employee->next;
        if (employee->next)
            employee->next->prev = employee->prev;
        if (employee == head)
            head = employee->next;

        Project *project = employee->info.projects;
        while (project)
        {
            Project *temp = project;
            project = project->next;
            delete temp;
        }

        delete employee;
        return true;
    }

    bool updateEmployee(const string &id, const string &newProjectName, bool isCompleted)
    {
        Employee *employee = findEmployee(id);
        if (!employee)
            return false;

        Project *newProject = new Project(newProjectName, "", isCompleted);
        newProject->next = employee->info.projects;
        employee->info.projects = newProject;
        return true;
    }

    void displayEmployee(const string &id)
    {
        Employee *employee = findEmployee(id);
        if (!employee)
        {
            cout << "Employee not found.\n"
                 << endl;
            return;
        }
        cout << "Employee ID: " << employee->info.id << ", Name: " << employee->info.name << endl;
        Project *project = employee->info.projects;
        while (project)
        {
            cout << "  Project: " << project->name << " (" << project->code
                 << "), Completed: " << (project->completed ? "Yes" : "No") << endl;
            project = project->next;
        }
        cout << endl;
    }

    void displayAllEmployees(int order)
    {

        if (!head)
        {
            cout << "No employees found.\n"
                 << endl;
            return;
        }

        if (order == 0)
        {
            Employee *current = head;
            while (current)
            {
                displayEmployee(current->info.id);
                current = current->next;
            }
        }
        else
        {
            Employee *current = head;
            while (current && current->next)
                current = current->next;
            while (current)
            {
                displayEmployee(current->info.id);
                current = current->prev;
            }
        }
    }
};
