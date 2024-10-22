#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Abstract class Income
class Income {
protected:
    double amount;
    string source;
    static int totalIncomes;

public:
    Income() : amount(0), source("") {
        totalIncomes++;
        cout << "Default Constructor for Income called" << endl;
    }

    Income(double amount, string source) : amount(amount), source(source) {
        totalIncomes++;
        cout << "Parameterized Constructor for Income called" << endl;
    }

    virtual ~Income() {
        cout << "Destructor for Income called. Source: " << source << endl;
    }

    virtual double getAmount() const {
        return amount;
    }

    // Pure virtual function makes this an abstract class
    virtual string getDetails() const = 0;

    string getSource() const {
        return source;
    }

    static int getTotalIncomes() {
        return totalIncomes;
    }
};

int Income::totalIncomes = 0;

class SalaryIncome : public Income {
private:
    string employer;

public:
    SalaryIncome(double amount, string source, string employer) : Income(amount, source), employer(employer) {
        cout << "SalaryIncome Constructor called" << endl;
    }

    ~SalaryIncome() {
        cout << "Destructor for SalaryIncome called. Employer: " << employer << endl;
    }

    string getEmployer() const {
        return employer;
    }

    string getDetails() const override {
        return "Salary from " + employer + " via " + source + ": $" + to_string(amount);
    }
};

// Abstract class Expense
class Expense {
protected:
    double amount;
    string category;
    static int totalExpenses;

public:
    Expense() : amount(0), category("") {
        totalExpenses++;
        cout << "Default Constructor for Expense called" << endl;
    }

    Expense(double amount, string category) : amount(amount), category(category) {
        totalExpenses++;
        cout << "Parameterized Constructor for Expense called" << endl;
    }

    virtual ~Expense() {
        cout << "Destructor for Expense called. Category: " << category << endl;
    }

    virtual double getAmount() const {
        return amount;
    }

    // Pure virtual function makes this an abstract class
    virtual string getDetails() const = 0;

    static int getTotalExpenses() {
        return totalExpenses;
    }
};

int Expense::totalExpenses = 0;

class BusinessExpense : public Expense {
private:
    string businessPurpose;

public:
    BusinessExpense(double amount, string category, string businessPurpose) : Expense(amount, category), businessPurpose(businessPurpose) {
        cout << "BusinessExpense Constructor called" << endl;
    }

    ~BusinessExpense() {
        cout << "Destructor for BusinessExpense called. Business Purpose: " << businessPurpose << endl;
    }

    string getDetails() const override {
        return "Business Expense for " + businessPurpose + " in category " + category + ": $" + to_string(amount);
    }
};

class BudgetTracker {
private:
    vector<Income*> incomes;
    vector<Expense*> expenses;

public:
    BudgetTracker() {
        cout << "BudgetTracker created" << endl;
    }

    void addIncome(Income* income) {
        incomes.emplace_back(income);
        cout << "Income added: " << income->getDetails() << endl;
    }

    // Removed the direct instantiation of Income
    void addIncome(double amount, string source, string employer) {
        addIncome(new SalaryIncome(amount, source, employer));
    }

    void addExpense(Expense* expense) {
        expenses.emplace_back(expense);
        cout << "Expense added: " << expense->getDetails() << endl;
    }

    // Removed the direct instantiation of Expense
    void addExpense(double amount, string category, string businessPurpose) {
        addExpense(new BusinessExpense(amount, category, businessPurpose));
    }

    void viewSummary() const {
        double totalIncome = 0.0, totalExpenses = 0.0;

        for (const auto& income : incomes) {
            totalIncome += income->getAmount();
        }

        for (const auto& expense : expenses) {
            totalExpenses += expense->getAmount();
        }

        cout << "\n--- Financial Summary ---" << endl;
        cout << "Total Income: " << totalIncome << endl;
        cout << "Total Expenses: " << totalExpenses << endl;
        cout << "Remaining Balance: " << (totalIncome - totalExpenses) << endl;
        cout << "Total Incomes Recorded: " << Income::getTotalIncomes() << endl;
        cout << "Total Expenses Recorded: " << Expense::getTotalExpenses() << endl;
    }

    ~BudgetTracker() {
        for (auto income : incomes) {
            delete income;
        }
        for (auto expense : expenses) {
            delete expense;
        }
        cout << "BudgetTracker destroyed" << endl;
    }
};

int main() {
    BudgetTracker* tracker = new BudgetTracker();

    int incomeCount;
    cout << "How many incomes would you like to enter? ";
    cin >> incomeCount;

    for (int i = 0; i < incomeCount; i++) {
        double amount;
        string source, employer;

        cout << "Enter income amount: ";
        cin >> amount;
        cout << "Enter income source: ";
        cin >> ws;
        getline(cin, source);

        cout << "Enter employer name: ";
        getline(cin, employer);
        tracker->addIncome(amount, source, employer);
    }

    int expenseCount;
    cout << "How many expenses would you like to enter? ";
    cin >> expenseCount;

    for (int i = 0; i < expenseCount; i++) {
        double amount;
        string category, businessPurpose;

        cout << "Enter expense amount: ";
        cin >> amount;
        cout << "Enter expense category: ";
        cin >> ws;
        getline(cin, category);

        cout << "Enter business purpose: ";
        getline(cin, businessPurpose);
        tracker->addExpense(amount, category, businessPurpose);
    }

    tracker->viewSummary();

    delete tracker;
    return 0;
}
