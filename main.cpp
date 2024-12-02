#include <iostream>
#include <vector>
#include <string>
#include <memory> // For smart pointers

using namespace std;

// Abstract class Income (Base class, open for extension)
class Income {
protected:
    double amount;
    string source;

public:
    Income(double amount, string source) : amount(amount), source(source) {}

    virtual ~Income() = default;

    virtual double getAmount() const {
        return amount;
    }

    virtual string getDetails() const = 0; // Pure virtual function
};

// Derived class SalaryIncome (Extends Income)
class SalaryIncome : public Income {
private:
    string employer;

public:
    SalaryIncome(double amount, string source, string employer)
        : Income(amount, source), employer(employer) {}

    string getDetails() const override {
        return "Salary from " + employer + " via " + source + ": $" + to_string(amount);
    }
};

// Derived class InvestmentIncome (Extends Income)
class InvestmentIncome : public Income {
private:
    string investmentType;

public:
    InvestmentIncome(double amount, string source, string investmentType)
        : Income(amount, source), investmentType(investmentType) {}

    string getDetails() const override {
        return "Investment income from " + investmentType + " via " + source + ": $" + to_string(amount);
    }
};

// Abstract class Expense (Base class, open for extension)
class Expense {
protected:
    double amount;
    string category;

public:
    Expense(double amount, string category) : amount(amount), category(category) {}

    virtual ~Expense() = default;

    virtual double getAmount() const {
        return amount;
    }

    virtual string getDetails() const = 0; // Pure virtual function
};

// Derived class BusinessExpense (Extends Expense)
class BusinessExpense : public Expense {
private:
    string businessPurpose;

public:
    BusinessExpense(double amount, string category, string businessPurpose)
        : Expense(amount, category), businessPurpose(businessPurpose) {}

    string getDetails() const override {
        return "Business Expense for " + businessPurpose + " in category " + category + ": $" + to_string(amount);
    }
};

// Derived class PersonalExpense (Extends Expense)
class PersonalExpense : public Expense {
private:
    string description;

public:
    PersonalExpense(double amount, string category, string description)
        : Expense(amount, category), description(description) {}

    string getDetails() const override {
        return "Personal Expense for " + description + " in category " + category + ": $" + to_string(amount);
    }
};

// Manages a collection of Income objects
class IncomeManager {
private:
    vector<shared_ptr<Income>> incomes;

public:
    void addIncome(shared_ptr<Income> income) {
        incomes.push_back(income);
    }

    double getTotalIncome() const {
        double total = 0.0;
        for (const auto& income : incomes) {
            total += income->getAmount();
        }
        return total;
    }

    void showIncomeDetails() const {
        cout << "\n--- Income Details ---\n";
        for (const auto& income : incomes) {
            cout << income->getDetails() << endl;
        }
    }
};

// Manages a collection of Expense objects
class ExpenseManager {
private:
    vector<shared_ptr<Expense>> expenses;

public:
    void addExpense(shared_ptr<Expense> expense) {
        expenses.push_back(expense);
    }

    double getTotalExpenses() const {
        double total = 0.0;
        for (const auto& expense : expenses) {
            total += expense->getAmount();
        }
        return total;
    }

    void showExpenseDetails() const {
        cout << "\n--- Expense Details ---\n";
        for (const auto& expense : expenses) {
            cout << expense->getDetails() << endl;
        }
    }
};

// Manages the overall budget using IncomeManager and ExpenseManager
class BudgetTracker {
private:
    IncomeManager incomeManager;
    ExpenseManager expenseManager;

public:
    void addIncome() {
        int choice;
        double amount;
        string source, employer, investmentType;

        cout << "\nSelect Income Type:\n1. Salary Income\n2. Investment Income\nChoice: ";
        cin >> choice;

        cout << "Enter income amount: ";
        cin >> amount;
        cout << "Enter income source: ";
        cin.ignore();
        getline(cin, source);

        if (choice == 1) {
            cout << "Enter employer name: ";
            getline(cin, employer);
            incomeManager.addIncome(make_shared<SalaryIncome>(amount, source, employer));
        } else if (choice == 2) {
            cout << "Enter investment type: ";
            getline(cin, investmentType);
            incomeManager.addIncome(make_shared<InvestmentIncome>(amount, source, investmentType));
        } else {
            cout << "Invalid choice!\n";
        }
    }

    void addExpense() {
        int choice;
        double amount;
        string category, businessPurpose, description;

        cout << "\nSelect Expense Type:\n1. Business Expense\n2. Personal Expense\nChoice: ";
        cin >> choice;

        cout << "Enter expense amount: ";
        cin >> amount;
        cout << "Enter expense category: ";
        cin.ignore();
        getline(cin, category);

        if (choice == 1) {
            cout << "Enter business purpose: ";
            getline(cin, businessPurpose);
            expenseManager.addExpense(make_shared<BusinessExpense>(amount, category, businessPurpose));
        } else if (choice == 2) {
            cout << "Enter expense description: ";
            getline(cin, description);
            expenseManager.addExpense(make_shared<PersonalExpense>(amount, category, description));
        } else {
            cout << "Invalid choice!\n";
        }
    }

    void viewSummary() const {
        incomeManager.showIncomeDetails();
        expenseManager.showExpenseDetails();

        double totalIncome = incomeManager.getTotalIncome();
        double totalExpenses = expenseManager.getTotalExpenses();

        cout << "\n--- Financial Summary ---" << endl;
        cout << "Total Income: $" << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpenses << endl;
        cout << "Remaining Balance: $" << (totalIncome - totalExpenses) << endl;
    }
};

// Main function for user interaction
int main() {
    BudgetTracker tracker;
    int choice;

    do {
        cout << "\n--- Budget Tracker Menu ---\n";
        cout << "1. Add Income\n2. Add Expense\n3. View Summary\n4. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tracker.addIncome();
            break;
        case 2:
            tracker.addExpense();
            break;
        case 3:
            tracker.viewSummary();
            break;
        case 4:
            cout << "Exiting Budget Tracker.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
