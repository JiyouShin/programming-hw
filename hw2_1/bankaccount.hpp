#ifndef BANKACCOUNT_HPP
#define BANKACCOUNT_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <fstream>

struct Transaction {
    double deposit;
    double withdraw;
    double balance;
};

class BankAccount {
protected:
    double balance;
    std::vector<Transaction> transactionHistory;

public:
    /*============================= Q 1.1 =============================*/
    // TODO
    BankAccount(double initialBalance):
    balance(initialBalance), transactionHistory(std::vector<Transaction>()) {};

    /*============================= Q 1.2 =============================*/
    // TODO
    virtual void deposit(double amount) {
        Transaction transaction;
        transaction.withdraw = 0;

        if (amount <= 0) {
            transaction.deposit = 0;
            transaction.balance = 0;
        } else {
            balance += amount;
            transaction.deposit = amount;
            transaction.balance = balance;
        }
        transactionHistory.push_back(transaction);
    }

    /*============================= Q 1.3 =============================*/
    // TODO
    virtual void withdraw(double amount) {
        Transaction transaction;
        transaction.deposit = 0;

        if (balance < amount || amount <= 0) {
            transaction.withdraw = 0;
            transaction.balance = balance;
        } else {
            balance -= amount;
            transaction.withdraw = amount;
            transaction.balance =  balance;
        }
        transactionHistory.push_back(transaction);
    }


    /*============================= Q 1.4 =============================*/
    // TODO
    double getBalance() const {
        return balance;
    }


    /*============================= Q 1.5 =============================*/
    // TODO
    const std::vector<Transaction>& getTransactionHistory() const {
        return transactionHistory;
    }

    // Do not modify this section.
    virtual ~BankAccount() {}
};


class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    /*============================= Q 2.1 =============================*/
    // TODO
    SavingsAccount(double initialBalance, double rate):
    BankAccount(initialBalance), interestRate(rate) {};

    /*============================= Q 2.2 =============================*/
    // TODO
    void deposit(double amount) override {
        Transaction transaction;
        transaction.withdraw = 0;

        if (amount <= 0) {
            transaction.balance = balance;
            transaction.deposit = 0;
        } else {
            double interest = amount * interestRate;
            balance += (amount + interest);
            transaction.balance = balance;
            transaction.deposit = amount + interest;
        }
        transactionHistory.push_back(transaction);
    }

    /*============================= Q 2.3 =============================*/
    // TODO
    ~SavingsAccount() {
        std::cout << "SavingsAccount closed" << std::endl;
    };
};


class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    /*============================= Q 3.1 =============================*/
    // TODO
    CheckingAccount(double initialBalance, double fee) :
    BankAccount(initialBalance), transactionFee(fee) {}

    /*============================= Q 3.2 =============================*/ 
    // TODO
    void withdraw(double amount) override {
        Transaction transaction;
        transaction.deposit = 0;

        if (balance < amount + transactionFee || amount <= 0) {
            transaction.withdraw = 0;
            transaction.balance = balance;
        } else {
            balance -= (amount + transactionFee);
            transaction.withdraw = amount + transactionFee;
            transaction.balance = balance;
        }
        transactionHistory.push_back(transaction);
    }

    /*============================= Q 3.3 =============================*/
    // TODO
    ~CheckingAccount() {
        std::cout << "CheckingAccount closed" << std::endl;
    }
};


class BusinessAccount : public BankAccount {
private:
    double creditLine;

public:
    /*============================= Q 4.1 =============================*/
    // TODO
    BusinessAccount(double initialBalance, double credit):
    BankAccount(initialBalance), creditLine(credit) {}

    /*============================= Q 4.2 =============================*/
    // TODO
    void withdraw(double amount) override {
        double limit = balance + creditLine;
        Transaction transaction;
        transaction.deposit = 0;
        
        if (limit < amount || amount <= 0) {
            transaction.balance = balance;
            transaction.withdraw = 0;
        } else {
            balance -= amount;
            transaction.balance = balance;
            transaction.withdraw = amount;
        }
        transactionHistory.push_back(transaction);
    }

    /*============================= Q 4.3 =============================*/
    // TODO
    ~BusinessAccount() {
        std::cout << "BusinessAccount closed" << std::endl;
    }

};

class AccountManager {
private:
    std::vector<std::shared_ptr<BankAccount> > accounts;

public:
    /*============================= Q 5.1 =============================*/
    // TODO
    void addAccount(const std::shared_ptr<BankAccount>& account) {
        accounts.push_back(account);
    }

    /*============================= Q 5.2 =============================*/
    // TODO
    void transferFunds(int fromIndex, int toIndex, double amount) {
        if (fromIndex < 0 || fromIndex >= accounts.size() || toIndex < 0 || fromIndex >= accounts.size()) {
            throw std::runtime_error("Invalid account index");
        }
        if (amount <= 0) {
            throw std::runtime_error("amount must be bigger than zero");
        }
        std::shared_ptr<BankAccount> fromAccount = accounts[fromIndex];
        std::shared_ptr<BankAccount> toAccount = accounts[toIndex];

        (*fromAccount).withdraw(amount);
        if ((*fromAccount).getBalance() > amount) {
            (*toAccount).deposit(amount);
        } 
    }

    /*============================= Q 5.3 =============================*/
    // TODO
    std::shared_ptr<BankAccount> getAccount(int index) {
        if (index < 0 || index >= accounts.size()) {
            throw std::runtime_error("Invalid Account index");
        } else {
            return accounts[index];
        }
    }
};

#endif  // BANKACCOUNT_HPP
