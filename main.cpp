#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Transaction {
protected:
    double amount;
    string description;

public:
    Transaction(double amt, string desc) : amount(amt), description(desc) {}
    virtual ~Transaction() { cout << "Destructor for Transaction called: " << description << endl; }

    double getAmount() const { return amount; }
    string getDescription() const { return description; }

    virtual void display() const = 0;
};

class Income : public Transaction {
private:
    static int totalIncomes;

public:
    Income(double amount, string source) : Transaction(amount, source) {
        totalIncomes++;
        cout << "Income Created: " << description << endl;
    }

    ~Income() override {
        cout << "Income Destructor called. Source: " << description << endl;
    }

    void display() const override {
        cout << "Income from " << description << ": " << amount << endl;
    }

    static int getTotalIncomes() { return totalIncomes; }
};

int Income::totalIncomes = 0;

class Expense : public Transaction {
private:
    static int totalExpenses;

public:
    Expense(double amount, string category) : Transaction(amount, category) {
        totalExpenses++;
        cout << "Expense Created: " << description << endl;
    }

    ~Expense() override {
        cout << "Expense Destructor called. Category: " << description << endl;
    }

    void display() const override {
        cout << "Expense for " << description << ": " << amount << endl;
    }

    static int getTotalExpenses() { return totalExpenses; }
};

int Expense::totalExpenses = 0;

class BudgetTracker : public Income, public Expense {
private:
    vector<Income*> incomes;
    vector<Expense*> expenses;

public:
    BudgetTracker() : Income(0, ""), Expense(0, "") {
        cout << "BudgetTracker created" << endl;
    }

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

    void viewSummary() const {
        double totalIncome = 0.0, totalExpenses = 0.0;

        cout << "\n--- Financial Summary ---" << endl;
        for (const auto& income : incomes) {
            totalIncome += income->getAmount();
            income->display();
        }
        for (const auto& expense : expenses) {
            totalExpenses += expense->getAmount();
            expense->display();
        }

        cout << "Total Income: " << totalIncome << endl;
        cout << "Total Expenses: " << totalExpenses << endl;
        cout << "Remaining Balance: " << (totalIncome - totalExpenses) << endl;
        cout << "Total Incomes Recorded: " << Income::getTotalIncomes() << endl;
        cout << "Total Expenses Recorded: " << Expense::getTotalExpenses() << endl;
    }

    ~BudgetTracker() {
        for (auto income : incomes) delete income;
        for (auto expense : expenses) delete expense;
        cout << "BudgetTracker destroyed" << endl;
    }
};

int main() {
    BudgetTracker tracker;

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
        tracker.addIncome(amount, source);
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
        tracker.addExpense(amount, category);
    }

    tracker.viewSummary();

    return 0;
}
