#include "bankaccount.hpp"
#include <iostream>
#include <memory>
#include <iomanip>

void printTransactionHistory(const std::vector<Transaction>& history) {
    std::cout << "Transaction History:\n";
    for (const auto& transaction : history) {
        std::cout << "Deposit: " << transaction.deposit
                  << ", Withdraw: " << transaction.withdraw
                  << ", Balance: " << transaction.balance << std::endl;
    }
}

void compareResults(const std::string& description, double expected, double actual) {
    std::cout << std::left << std::setw(30) << description
              << " | Expected: " << expected
              << " | Actual: " << actual
              << (expected == actual ? " | PASS" : " | FAIL") << std::endl;
}

int main() {
    // Test SavingsAccount
    std::cout << "::Test SavingsAccount::"<< std::endl;
    std::shared_ptr<SavingsAccount> savings = std::make_shared<SavingsAccount>(1000.0, 0.05);
    savings->deposit(200);
    double expectedSavingsBalance = 1000 + 200 + (200 * 0.05);
    compareResults("SavingsAccount balance after deposit", expectedSavingsBalance, savings->getBalance());
    printTransactionHistory(savings->getTransactionHistory());
    std::cout<<std::endl;

    // Test CheckingAccount
    std::cout << "::Test CheckingAccount::"<< std::endl;
    std::shared_ptr<CheckingAccount> checking = std::make_shared<CheckingAccount>(500.0, 1.5);
    checking->withdraw(100);
    double expectedCheckingBalance = 500 - (100 + 1.5);
    compareResults("CheckingAccount balance after withdraw", expectedCheckingBalance, checking->getBalance());
    printTransactionHistory(checking->getTransactionHistory());

    checking->withdraw(600);
    compareResults("CheckingAccount balance after failed withdraw", expectedCheckingBalance, checking->getBalance());
    printTransactionHistory(checking->getTransactionHistory());
    std::cout<<std::endl;

    // Test BusinessAccount
    std::cout << "::Test BusinessAccount::"<< std::endl;
    std::shared_ptr<BusinessAccount> business = std::make_shared<BusinessAccount>(2000.0, 5000.0);
    business->withdraw(4000);
    double expectedBusinessBalance = 2000 - 4000;
    compareResults("BusinessAccount balance after withdraw using credit line", expectedBusinessBalance, business->getBalance());
    printTransactionHistory(business->getTransactionHistory());

    business->withdraw(8000);
    compareResults("BusinessAccount balance after failed withdraw", expectedBusinessBalance, business->getBalance());
    printTransactionHistory(business->getTransactionHistory());
    std::cout<<std::endl;

    // Test overriding
    std::cout << "::Test overriding::"<< std::endl;
    std::shared_ptr<BankAccount> basicAccount = std::make_shared<BankAccount>(1000.0);
    std::cout << "BankAccount balance before deposit: " << basicAccount->getBalance() << std::endl;
    basicAccount->deposit(500.0);
    std::cout << "BankAccount balance after deposit: " << basicAccount->getBalance() << std::endl;

    std::shared_ptr<BankAccount> savingsAccount = std::make_shared<SavingsAccount>(1000.0, 0.05);
    std::cout << "SavingsAccount balance before deposit: " << savingsAccount->getBalance() << std::endl;
    savingsAccount->deposit(500.0);
    std::cout << "SavingsAccount balance after deposit: " << savingsAccount->getBalance() << std::endl;
    printTransactionHistory(savingsAccount->getTransactionHistory());
    std::cout<<std::endl;

    // Test AccountManager
    std::cout << "::Test AccountManager::"<< std::endl;
    AccountManager manager;
    manager.addAccount(savings);
    manager.addAccount(checking);
    manager.addAccount(business);

    // Test transferring funds between accounts
    manager.transferFunds(0, 1, 100);  // Transfer 100 from savings to checking
    expectedSavingsBalance -= 100;
    expectedCheckingBalance += 100;
    compareResults("SavingsAccount balance after transfer", expectedSavingsBalance, manager.getAccount(0)->getBalance());
    compareResults("CheckingAccount balance after transfer", expectedCheckingBalance, manager.getAccount(1)->getBalance());

    std::cout << "\nSavingsAccount Transaction History after transfer:\n";
    printTransactionHistory(manager.getAccount(0)->getTransactionHistory());

    std::cout << "\nCheckingAccount Transaction History after transfer:\n";
    printTransactionHistory(manager.getAccount(1)->getTransactionHistory());

   
    return 0;
}
