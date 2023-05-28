#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

class Employee {
public:
    int id;
    string name;
    string surname;
    int yearOfBirth;
    double salary;
};

bool compareById(const Employee& emp1, const Employee& emp2) {
    return emp1.id < emp2.id;
}

bool compareByName(const Employee& emp1, const Employee& emp2) {
    if (emp1.surname == emp2.surname) {
        return emp1.name < emp2.name;
    }
    return emp1.surname < emp2.surname;
}

bool compareByYear(const Employee& emp1, const Employee& emp2) {
    return emp1.yearOfBirth < emp2.yearOfBirth;
}

bool compareBySalary(const Employee& emp1, const Employee& emp2) {
    return emp1.salary < emp2.salary;
}

void processQuery(const vector<Employee>& employees, const string& query) {
    string what;
    string order;
    int item;
    istringstream iss(query);
    iss >> what >> order >> item;

    vector<Employee> sortedEmployees = employees;

    if (what == "id") {
        sort(sortedEmployees.begin(), sortedEmployees.end(), compareById);
    } else if (what == "name") {
        sort(sortedEmployees.begin(), sortedEmployees.end(), compareByName);
    } else if (what == "year") {
        sort(sortedEmployees.begin(), sortedEmployees.end(), compareByYear);
    } else if (what == "salary") {
        sort(sortedEmployees.begin(), sortedEmployees.end(), compareBySalary);
    }

    if (order == "desc") {
        reverse(sortedEmployees.begin(), sortedEmployees.end());
    }

    cout << "query: " << query << "\n";

    int count = 0;
    for (const auto& employee : sortedEmployees) {
        if (count == item) {
            break;
        }
        cout << employee.id << " " << employee.name << " " << employee.surname << " " << employee.yearOfBirth << " " << employee.salary << "\n";
        count++;
    }
    cout << endl;
}

int main() {
    int N;
    cin >> N;

    vector<Employee> employees(N);
    for (int i = 0; i < N; ++i) {
        cin >> employees[i].id >> employees[i].name >> employees[i].surname >> employees[i].yearOfBirth >> employees[i].salary;
    }

    int M;
    cin >> M;
    cin.ignore(); // Ignore the newline character

    for (int i = 0; i < M; ++i) {
        string query;
        getline(cin, query);
        processQuery(employees, query);
    }

    return 0;
}
