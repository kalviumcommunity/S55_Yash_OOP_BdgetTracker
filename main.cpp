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
    Income(double amount, string source) : amount(amount), source(source) {
        totalIncomes++;
    }

    virtual ~Income() {
        totalIncomes--;
    }

    virtual double getAmount() const {
        return amount;
    }

    virtual string getDetails() const = 0;

    static int getTotalIncomes() {
        return totalIncomes;
    }
};

int Income::totalIncomes = 0;

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

// Abstract class Expense
class Expense {
protected:
    double amount;
    string category;
    static int totalExpenses;

public:
    Expense(double amount, string category) : amount(amount), category(category) {
        totalExpenses++;
    }

    virtual ~Expense() {
        totalExpenses--;
    }

    virtual double getAmount() const {
        return amount;
    }

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
    BusinessExpense(double amount, string category, string businessPurpose)
        : Expense(amount, category), businessPurpose(businessPurpose) {}

    string getDetails() const override {
        return "Business Expense for " + businessPurpose + " in category " + category + ": $" + to_string(amount);
    }
};

// Manages a collection of Income objects
class IncomeManager {
private:
    vector<Income*> incomes;

public:
    ~IncomeManager() {
        for (auto income : incomes) {
            delete income;
        }
    }

    void addIncome(Income* income) {
        incomes.push_back(income);
    }

    double getTotalIncome() const {
        double total = 0.0;
        for (const auto& income : incomes) {
            total += income->getAmount();
        }
        return total;
    }
};

// Manages a collection of Expense objects
class ExpenseManager {
private:
    vector<Expense*> expenses;

public:
    ~ExpenseManager() {
        for (auto expense : expenses) {
            delete expense;
        }
    }

    void addExpense(Expense* expense) {
        expenses.push_back(expense);
    }

    double getTotalExpenses() const {
        double total = 0.0;
        for (const auto& expense : expenses) {
            total += expense->getAmount();
        }
        return total;
    }
};

// Manages the overall budget using IncomeManager and ExpenseManager
class BudgetTracker {
private:
    IncomeManager incomeManager;
    ExpenseManager expenseManager;

public:
    void addIncome(double amount, string source, string employer) {
        incomeManager.addIncome(new SalaryIncome(amount, source, employer));
    }

    void addExpense(double amount, string category, string businessPurpose) {
        expenseManager.addExpense(new BusinessExpense(amount, category, businessPurpose));
    }

    void viewSummary() const {
        double totalIncome = incomeManager.getTotalIncome();
        double totalExpenses = expenseManager.getTotalExpenses();

        cout << "\n--- Financial Summary ---" << endl;
        cout << "Total Income: $" << totalIncome << endl;
        cout << "Total Expenses: $" << totalExpenses << endl;
        cout << "Remaining Balance: $" << (totalIncome - totalExpenses) << endl;
        cout << "Total Incomes Recorded: " << Income::getTotalIncomes() << endl;
        cout << "Total Expenses Recorded: " << Expense::getTotalExpenses() << endl;
    }
};

// Main function for user interaction
int main() {
    BudgetTracker tracker;

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
        tracker.addIncome(amount, source, employer);
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
        tracker.addExpense(amount, category, businessPurpose);
    }

    tracker.viewSummary();

    return 0;
}
