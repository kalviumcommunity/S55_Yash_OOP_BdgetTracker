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

    string getSource() const {
        return source;
    }

    void setAmount(double amount) {
        this->amount = amount;
    }

    void setSource(string source) {
        this->source = source;
    }

    static int getTotalIncomes() {
        return totalIncomes;
    }
};

int Income::totalIncomes = 0;

// Derived class demonstrating single inheritance
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

    string getCategory() const {
        return category;
    }

    void setAmount(double amount) {
        this->amount = amount;
    }

    void setCategory(string category) {
        this->category = category;
    }

    static int getTotalExpenses() {
        return totalExpenses;
    }
};

int Expense::totalExpenses = 0;

// Derived class demonstrating single inheritance
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

    string getBusinessPurpose() const {
        return businessPurpose;
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
        cout << "Income added: " << income->getAmount() << " from " << income->getSource() << endl;
    }

    void addExpense(Expense* expense) {
        expenses.emplace_back(expense);
        cout << "Expense added: " << expense->getAmount() << " for " << expense->getCategory() << endl;
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
            if (incomeType == 1 || incomeType == 2) break; // Valid input
            cout << "Invalid input. Enter type of income (1 - Generic Income, 2 - Salary Income): ";
        }

        cout << "Enter income amount: ";
        cin >> amount;
        cout << "Enter income source: ";
        cin >> ws;
        getline(cin, source);

        if (incomeType == 2) {
            // Input specific for SalaryIncome
            cout << "Enter employer name: ";
            getline(cin, employer);
            tracker->addIncome(new SalaryIncome(amount, source, employer));
        } else {
            // Generic Income
            tracker->addIncome(new Income(amount, source));
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
            if (expenseType == 1 || expenseType == 2) break; // Valid input
            cout << "Invalid input. Enter type of expense (1 - Generic Expense, 2 - Business Expense): ";
        }

        cout << "Enter expense amount: ";
        cin >> amount;
        cout << "Enter expense category: ";
        cin >> ws;
        getline(cin, category);

        if (expenseType == 2) {
            // Input specific for BusinessExpense
            cout << "Enter business purpose: ";
            getline(cin, businessPurpose);
            tracker->addExpense(new BusinessExpense(amount, category, businessPurpose));
        } else {
            // Generic Expense
            tracker->addExpense(new Expense(amount, category));
        }
    }

    tracker->viewSummary();

    delete tracker;

    return 0;
}
