#include <iostream>
#include <vector>
#include <memory>

using namespace std;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Employee {
protected:
    string name;
    int yearsOfExperience;
    double salesRevenue;

public:
    Employee(const string& name, int yearsOfExperience, double salesRevenue)
        : name(name), yearsOfExperience(yearsOfExperience), salesRevenue(salesRevenue) {}

    virtual double calculateSalary() const = 0;
    virtual string getDepartmentName() const = 0;

    virtual void printInfo() const {
        cout << "Name: " << name << "\n";
        cout << "Department: " << getDepartmentName() << "\n";
        cout << "Years of Experience: " << yearsOfExperience << "\n";
        cout << "Sales Revenue: " << salesRevenue << "\n";
        cout << "Calculated Salary: " << calculateSalary() << "\n";
        cout << "---------------------------\n";
    }

    virtual ~Employee() = default;
};

double getExperienceBonus(int yearsOfExperience) {
    if (yearsOfExperience < 1) return 0.0;
    if (yearsOfExperience <= 3) return 0.05;
    if (yearsOfExperience <= 5) return 0.07;
    if (yearsOfExperience <= 7) return 0.10;
    if (yearsOfExperience <= 10) return 0.12;
    return 0.15;
}


class Management : public Employee {
public:
    Management(const string& name, int yearsOfExperience, double salesRevenue)
        : Employee(name, yearsOfExperience, salesRevenue) {}

    double calculateSalary() const override {
        double SF = 15000;
        double VM = getExperienceBonus(yearsOfExperience);
        double RV = 0.30 * salesRevenue;
        return SF + SF * VM + RV;
    }

    string getDepartmentName() const override {
        return "Management";
    }
};


class Legal : public Employee {
public:
    Legal(const string& name, int yearsOfExperience, double salesRevenue)
        : Employee(name, yearsOfExperience, salesRevenue) {}

    double calculateSalary() const override {
        double SF = 10000;
        double VM = getExperienceBonus(yearsOfExperience);
        double RV = 0.05 * salesRevenue;
        return SF + SF * VM + RV;
    }

    string getDepartmentName() const override {
        return "Legal";
    }
};


class Sales : public Employee {
public:
    Sales(const string& name, int yearsOfExperience, double salesRevenue)
        : Employee(name, yearsOfExperience, salesRevenue) {}

    double calculateSalary() const override {
        double SF = 7000;
        double VM = getExperienceBonus(yearsOfExperience);
        double RV = 0.15 * salesRevenue;
        return SF + SF * VM + RV;
    }

    string getDepartmentName() const override {
        return "Sales";
    }
};

class Audit : public Employee {
public:
    Audit(const string& name, int yearsOfExperience, double salesRevenue)
        : Employee(name, yearsOfExperience, salesRevenue) {}

    double calculateSalary() const override {
        double SF = 12000;
        double VM = getExperienceBonus(yearsOfExperience);
        double RV = 0.10 * salesRevenue;
        return SF + SF * VM + RV;
    }

    string getDepartmentName() const override {
        return "Audit";
    }
};

class IT : public Employee {
public:
    IT(const string& name, int yearsOfExperience, double salesRevenue)
        : Employee(name, yearsOfExperience, salesRevenue) {}

    double calculateSalary() const override {
        double SF = 14000;
        double VM = getExperienceBonus(yearsOfExperience);
        double RV = 0.25 * salesRevenue;
        return SF + SF * VM + RV;
    }

    string getDepartmentName() const override {
        return "IT";
    }
};

int main() {
    vector<unique_ptr<Employee>> employees;

    employees.push_back(make_unique<Management>("Alice", 10, 50000));
    employees.push_back(make_unique<Legal>("Bob", 2, 20000));
    employees.push_back(make_unique<Sales>("Charlie", 6, 30000));
    employees.push_back(make_unique<Audit>("Dave", 8, 40000));
    employees.push_back(make_unique<IT>("Eve", 4, 10000));

    for (const auto& employee : employees) {
        employee->printInfo();
    }

    return 0;
}
