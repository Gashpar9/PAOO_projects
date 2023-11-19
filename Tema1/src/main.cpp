#include <iostream>

#include "money_transfer_service.hpp"

using namespace money_transfer_service;

int main() {
    MoneyTransferService mts;

    // Create accounts
    User_Account ua1((char*)"Vlad", (char*)"qwerty");
    User_Account ua2((char*)"Dragos", (char*)"12345");

    Bank_Account* sa1 = new Savings_Account((char*)"Vlad Criste", (char*)"123ABC567890123");
    Bank_Account* sa2 = new Savings_Account((char*)"Dragos Criste", (char*)"123ABC567890124");
    Bank_Account* ba1 = new Business_Account((char*)"Jocuri Jocuri SRL", (char*)"346325FHFJG123");
    Bank_Account* ba2 = new Business_Account((char*)"Filme Filme SRL", (char*)"6238746IUOU6731");

    // Add accounts to users
    ua1.addAccount(sa1);
    ua1.addAccount(ba1);
    ua2.addAccount(sa2);
    ua2.addAccount(ba2);

    // Test account copy
    User_Account ua3(ua1);
    ua1.getAccounts()[0]->addBalance(100);
    std::cout << "ua1 sa1 balance: " << ua1.getAccounts()[0]->getBalance() << std::endl;
    std::cout << "ua3 sa1 balance: " << ua3.getAccounts()[0]->getBalance() << std::endl;

    ua2.getAccounts()[1]->addBalance(100);
    User_Account ua4 = ua2;
    std::cout << "ua2 ba2 balance: " << ua2.getAccounts()[1]->getBalance() << std::endl;
    std::cout << "ua4 ba2 balance: " << ua4.getAccounts()[1]->getBalance() << std::endl;

    // Test account move
    User_Account ua5 = std::move(ua1);

    // Test transfer
    mts.transfer(&ua2, ua2.getAccounts()[1], ua2.getAccounts()[0], 40, (char*)"12345");
    std::cout << "ua2 sa2 balance: " << ua2.getAccounts()[0]->getBalance() << std::endl;
    std::cout << "ua2 ba2 balance: " << ua2.getAccounts()[1]->getBalance() << std::endl;

    return 0;
}