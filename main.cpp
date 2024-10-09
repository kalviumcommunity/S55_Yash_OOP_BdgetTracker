#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Income {
private:
    double amount;
    string source;

public:
    Income() : amount(0), source("") {}

    Income(double amount, string source) {
        this->amount = amount;
        this->source = source;
    }

    double getAmount() const {
        return this->amount;
    }

    string getSource() const {
        return this->source;
    }
};

class Expense {
private:
    double amount;
    string category;

public:
    Expense() : amount(0), category("") {}

    Expense(double amount, string category) {
        this->amount = amount;
        this->category = category;
    }

    double getAmount() const {
        return this->amount;
    }

    string getCategory() const {
        return this->category;
    }
};

class BudgetTracker {
private:
    vector<Income> incomes;
    vector<Expense> expenses;

public:
    void addIncome(double amount, string source) {
        this->incomes.emplace_back(amount, source);
        cout << "Income added: " << amount << " from " << source << endl;
    }

    void addExpense(double amount, string category) {
        this->expenses.emplace_back(amount, category);
        cout << "Expense added: " << amount << " for " << category << endl;
    }

    void viewSummary() {
        double totalIncome = 0.0, totalExpenses = 0.0;

        for (const auto &income : incomes) {
            totalIncome += income.getAmount();
        }

        for (const auto &expense : expenses) {
            totalExpenses += expense.getAmount();
        }

        cout << "\n--- Financial Summary ---" << endl;
        cout << "Total Income: " << totalIncome << endl;
        cout << "Total Expenses: " << totalExpenses << endl;
        cout << "Remaining Balance: " << (totalIncome - totalExpenses) << endl;
    }
};

int main() {
    BudgetTracker tracker;

    int incomeCount;
    cout << "How many incomes would you like to enter? ";
    cin >> incomeCount;
    Income* incomes = new Income[incomeCount];

    for (int i = 0; i < incomeCount; i++) {
        double amount;
        string source;
        cout << "Enter income amount for income " << (i + 1) << ": ";
        cin >> amount;
        cout << "Enter income source for income " << (i + 1) << ": ";
        cin >> ws;
        getline(cin, source);
        incomes[i] = Income(amount, source);
        tracker.addIncome(incomes[i].getAmount(), incomes[i].getSource());
    }

    int expenseCount;
    cout << "How many expenses would you like to enter? ";
    cin >> expenseCount;
    Expense* expenses = new Expense[expenseCount];

    for (int i = 0; i < expenseCount; i++) {
        double amount;
        string category;
        cout << "Enter expense amount for expense " << (i + 1) << ": ";
        cin >> amount;
        cout << "Enter expense category for expense " << (i + 1) << ": ";
        cin >> ws;
        getline(cin, category);
        expenses[i] = Expense(amount, category);
        tracker.addExpense(expenses[i].getAmount(), expenses[i].getCategory());
    }

    tracker.viewSummary();

    delete[] incomes;
    delete[] expenses;

    return 0;
}
