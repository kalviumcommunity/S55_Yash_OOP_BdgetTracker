#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Income {
private:
    double amount;
    string source;

public:
    Income(double amt, string src) : amount(amt), source(src) {}

    double getAmount() const {
        return amount;
    }

    string getSource() const {
        return source;
    }
};

class Expense {
private:
    double amount;
    string category;

public:
    Expense(double amt, string cat) : amount(amt), category(cat) {}

    double getAmount() const {
        return amount;
    }

    string getCategory() const {
        return category;
    }
};

class BudgetTracker {
private:
    vector<Income> incomes;
    vector<Expense> expenses;

public:
    void addIncome(double amount, string source) {
        incomes.emplace_back(amount, source);
        cout << "Income added: " << amount << " from " << source << endl;
    }

    void addExpense(double amount, string category) {
        expenses.emplace_back(amount, category);
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
    int choice;
    double amount;
    string sourceOrCategory;

    while (true) {
        cout << "\n--- Budget Tracker ---" << endl;
        cout << "1. Add Income" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. View Summary" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter income amount: ";
                cin >> amount;
                cout << "Enter income source: ";
                cin >> ws;
                getline(cin, sourceOrCategory);
                tracker.addIncome(amount, sourceOrCategory);
                break;
            case 2:
                cout << "Enter expense amount: ";
                cin >> amount;
                cout << "Enter expense category: ";
                cin >> ws;
                getline(cin, sourceOrCategory);
                tracker.addExpense(amount, sourceOrCategory);
                break;
            case 3:
                tracker.viewSummary();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
