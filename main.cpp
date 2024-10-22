#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

    virtual string getDetails() const {
        return "Income from " + source + ": $" + to_string(amount);
    }

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

    virtual string getDetails() const {
        return "Expense for " + category + ": $" + to_string(amount);
    }

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

    void addIncome(double amount, string source) {
        addIncome(new Income(amount, source));
    }

    void addIncome(double amount, string source, string employer) {
        addIncome(new SalaryIncome(amount, source, employer));
    }

    void addExpense(Expense* expense) {
        expenses.emplace_back(expense);
        cout << "Expense added: " << expense->getDetails() << endl;
    }

    void addExpense(double amount, string category) {
        addExpense(new Expense(amount, category));
    }

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
        int incomeType;
        double amount;
        string source, employer;
        
        cout << "Enter type of income (1 - Generic Income, 2 - Salary Income): ";
        while (true) {
            cin >> incomeType;
            if (incomeType == 1 || incomeType == 2) break;
            cout << "Invalid input. Enter type of income (1 - Generic Income, 2 - Salary Income): ";
        }

        cout << "Enter income amount: ";
        cin >> amount;
        cout << "Enter income source: ";
        cin >> ws;
        getline(cin, source);

        if (incomeType == 2) {
            cout << "Enter employer name: ";
            getline(cin, employer);
            tracker->addIncome(amount, source, employer);
        } else {
            tracker->addIncome(amount, source);
        }
    }

    int expenseCount;
    cout << "How many expenses would you like to enter? ";
    cin >> expenseCount;

    for (int i = 0; i < expenseCount; i++) {
        int expenseType;
        double amount;
        string category, businessPurpose;

        cout << "Enter type of expense (1 - Generic Expense, 2 - Business Expense): ";
        while (true) {
            cin >> expenseType;
            if (expenseType == 1 || expenseType == 2) break;
            cout << "Invalid input. Enter type of expense (1 - Generic Expense, 2 - Business Expense): ";
        }

        cout << "Enter expense amount: ";
        cin >> amount;
        cout << "Enter expense category: ";
        cin >> ws;
        getline(cin, category);

        if (expenseType == 2) {
            cout << "Enter business purpose: ";
            getline(cin, businessPurpose);
            tracker->addExpense(amount, category, businessPurpose);
        } else {
            tracker->addExpense(amount, category);
        }
    }

    tracker->viewSummary();

    delete tracker;
    return 0;
}
