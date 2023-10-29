#include <iostream>
#include <cstring>

#include "money_transfer_service.hpp"
#include "sha256.hpp"

Account::Account(char* username, char* password) 
: balance(0)
{
    this->username = new char[strlen(username)];
    memcpy(this->username, username, strlen(username));

    std::string hashedPassword = sha256(password);
    this->password = new char[hashedPassword.length()];
    memcpy(this->password, hashedPassword.c_str(), hashedPassword.length());

    std::cout << "Account created for " << username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
}

Account::~Account() {
    std::cout << "Account destroyed for " << username << std::endl;
    
    delete this->username;
    delete this->password;
}

Account::Account(const Account& other) {
    this->username = new char[strlen(other.username)];
    memcpy(this->username, other.username, strlen(other.username));

    this->password = new char[strlen(other.password)];
    memcpy(this->password, other.password, strlen(other.password));

    this->balance = other.balance;

    std::cout << "Account copied for " << username << std::endl;
}

Account::Account(Account&& other) {
    this->username = other.username;
    this->password = other.password;
    this->balance = other.balance;

    other.username = NULL;
    other.password = NULL;

    std::cout << "Account moved for " << username << std::endl;
}

int Account::getBalance() {
    return this->balance;
}

int Account::addBalance(int amount) {
    this->balance += amount;
    return this->balance;
}

bool Account::verifyPassword(char* password) {
    std::string hashedPassword = sha256(password);
    return (strcmp(this->password, hashedPassword.c_str()) == 0);
}

MoneyTransferService::MoneyTransferService() {
    std::cout << "MoneyTransferService created" << std::endl;
}

bool MoneyTransferService::transfer(Account* from, Account* to, int amount, char* password) {
    if (!(from->verifyPassword(password))) {
        std::cout << "Password is incorrect" << std::endl;
        return false;
    }

    if (from->getBalance() < amount) {
        std::cout << "Insufficient funds" << std::endl;
        return false;
    }

    from->addBalance(-amount);
    to->addBalance(amount);

    std::cout << "Transfer complete" << std::endl;
    return true;
}


