#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Income {
private:
    double amount;
    string source;
    static int totalIncomes;

public:
    Income() : amount(0), source("") {
        totalIncomes++;
    }

    Income(double amount, string source) : amount(amount), source(source) {
        totalIncomes++;
    }

    double getAmount() const {
        return this->amount;
    }

    string getSource() const {
        return this->source;
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

class Expense {
private:
    double amount;
    string category;
    static int totalExpenses;

public:
    Expense() : amount(0), category("") {
        totalExpenses++;
    }

    Expense(double amount, string category) : amount(amount), category(category) {
        totalExpenses++;
    }

    double getAmount() const {
        return this->amount;
    }

    string getCategory() const {
        return this->category;
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

class BudgetTracker {
private:
    vector<Income*> incomes;
    vector<Expense*> expenses;

public:
    void addIncome(double amount, string source) {
        Income* income = new Income(amount, source);
        incomes.emplace_back(income);
        cout << "Income added: " << amount << " from " << source << endl;
    }

    void addExpense(double amount, string category) {
        Expense* expense = new Expense(amount, category);
        expenses.emplace_back(expense);
        cout << "Expense added: " << amount << " for " << category << endl;
    }

    void viewSummary() {
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
    }
};

int main() {
    BudgetTracker* tracker = new BudgetTracker();

    int incomeCount;
    cout << "How many incomes would you like to enter? ";
    cin >> incomeCount;

    for (int i = 0; i < incomeCount; i++) {
        double amount;
        string source;
        cout << "Enter income amount for income " << (i + 1) << ": ";
        cin >> amount;
        cout << "Enter income source for income " << (i + 1) << ": ";
        cin >> ws;
        getline(cin, source);
        tracker->addIncome(amount, source);
    }

    int expenseCount;
    cout << "How many expenses would you like to enter? ";
    cin >> expenseCount;

    for (int i = 0; i < expenseCount; i++) {
        double amount;
        string category;
        cout << "Enter expense amount for expense " << (i + 1) << ": ";
        cin >> amount;
        cout << "Enter expense category for expense " << (i + 1) << ": ";
        cin >> ws;
        getline(cin, category);
        tracker->addExpense(amount, category);
    }

    tracker->viewSummary();

    delete tracker;

    return 0;
}
