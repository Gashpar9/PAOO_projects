#include <iostream>
#include <cstring>
#include <ctime>

#include "money_transfer_service.hpp"
#include "sha256.hpp"

using namespace money_transfer_service;

User_Account::User_Account(char* username, char* password) 
: accounts(std::vector<Bank_Account*>())
{
    this->username = new char[strlen(username)];
    memcpy(this->username, username, strlen(username));

    time_t time;
    time = std::time(NULL);
    std::string salt = std::to_string(time);
    this->salt = new char[strlen(salt.c_str())];
    memcpy(this->salt, salt.c_str(), strlen(salt.c_str()));
    
    std::string hashedPassword = sha256(std::string(password) + salt);
    this->password = new char[hashedPassword.length()];
    memcpy(this->password, hashedPassword.c_str(), hashedPassword.length());

    std::cout << "User_Account created for " << username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
}

User_Account::~User_Account() {
    std::cout << "User_Account destroyed for " << username << std::endl;
    
    delete this->username;
    delete this->password;
    delete this->salt;
    for (auto account_ptr : accounts) {
        delete account_ptr;
    }
}

User_Account::User_Account(const User_Account& other) {
    this->username = new char[strlen(other.username)];
    memcpy(this->username, other.username, strlen(other.username));

    this->password = new char[strlen(other.password)];
    memcpy(this->password, other.password, strlen(other.password));

    this->salt = new char[strlen(other.salt)];
    memcpy(this->salt, other.salt, strlen(other.salt));

    this->accounts = std::vector<Bank_Account*>();
    for(const auto& account_ptr : other.accounts) {
        this->accounts.push_back(account_ptr->clone());
    }

    std::cout << "User_Account copied for " << username << std::endl;
}

User_Account::User_Account(User_Account&& other) 
: accounts(std::move(other.accounts))
{
    this->username = other.username;
    this->password = other.password;
    this->salt = other.salt;

    other.username = NULL;
    other.password = NULL;
    other.salt = NULL;
    other.accounts.clear();

    std::cout << "User_Account moved for " << username << std::endl;
}

User_Account& User_Account::operator=(const User_Account& other) {
    this->username = new char[strlen(other.username)];
    memcpy(this->username, other.username, strlen(other.username));

    this->password = new char[strlen(other.password)];
    memcpy(this->password, other.password, strlen(other.password));

    this->salt = new char[strlen(other.salt)];
    memcpy(this->salt, other.salt, strlen(other.salt));

    this->accounts = std::vector<Bank_Account*>();
    for(const auto& account_ptr : other.accounts) {
        this->accounts.push_back(account_ptr->clone());
    }

    std::cout << "User_Account copied for " << username << std::endl;
    return *this;
}

User_Account& User_Account::operator=(User_Account&& other) {
    this->username = other.username;
    this->password = other.password;
    this->salt = other.salt;
    this->accounts = std::move(other.accounts);

    other.username = NULL;
    other.password = NULL;
    other.salt = NULL;
    other.accounts.clear();

    std::cout << "User_Account moved for " << username << std::endl;
    return *this;
}

bool User_Account::verifyPassword(char* password) {
    std::string hashedPassword = sha256(password + std::string(this->salt));
    return (strcmp(this->password, hashedPassword.c_str()) == 0);
}

void User_Account::addAccount(Bank_Account* account) {
    this->accounts.push_back(account);
}

std::vector<Bank_Account*> User_Account::getAccounts() {
    return this->accounts;
}

//

int Bank_Account::getBalance() {
    return this->balance;
}

//

Savings_Account::Savings_Account(char* fullname, char* cnp) {
    this->fullname = new char[strlen(fullname)];
    memcpy(this->fullname, fullname, strlen(fullname));

    this->cnp = new char[strlen(cnp)];
    memcpy(this->cnp, cnp, strlen(cnp));

    this->balance = 0; // intreaba de ce nu pot initializa inainte de implementare

    std::cout << "Savings_Account created for " << fullname << std::endl;
}

Savings_Account::~Savings_Account() {
    std::cout << "Savings_Account destroyed for " << fullname << std::endl;
    
    delete this->fullname;
    delete this->cnp;
}

Savings_Account::Savings_Account(const Savings_Account& other) {
    this->fullname = new char[strlen(other.fullname)];
    memcpy(this->fullname, other.fullname, strlen(other.fullname));

    this->cnp = new char[strlen(other.cnp)];
    memcpy(this->cnp, other.cnp, strlen(other.cnp));

    this->balance = other.balance;

    std::cout << "Savings_Account copied for " << fullname << std::endl;
}

Savings_Account::Savings_Account(Savings_Account&& other) {
    this->fullname = other.fullname;
    this->cnp = other.cnp;
    this->balance = other.balance;

    other.fullname = NULL;
    other.cnp = NULL;

    std::cout << "Savings_Account moved for " << fullname << std::endl;
}

Savings_Account* Savings_Account::clone() {
    return new Savings_Account(*this);
}

int Savings_Account::addBalance(int amount) {
    this->balance += amount;
    return this->balance;
}

//

Business_Account::Business_Account(char* company_name, char* cif) {
    this->company_name = new char[strlen(company_name)];
    memcpy(this->company_name, company_name, strlen(company_name));

    this->cif = new char[strlen(cif)];
    memcpy(this->cif, cif, strlen(cif));

    this->balance = 0;

    std::cout << "Business_Account created for " << company_name << std::endl;
}

Business_Account::~Business_Account() {
    std::cout << "Business_Account destroyed for " << company_name << std::endl;
    
    delete this->company_name;
    delete this->cif;
}

Business_Account::Business_Account(const Business_Account& other) {
    this->company_name = new char[strlen(other.company_name)];
    memcpy(this->company_name, other.company_name, strlen(other.company_name));

    this->cif = new char[strlen(other.cif)];
    memcpy(this->cif, other.cif, strlen(other.cif));

    this->balance = other.balance;

    std::cout << "Business_Account copied for " << company_name << std::endl;
}

Business_Account::Business_Account(Business_Account&& other) {
    this->company_name = other.company_name;
    this->cif = other.cif;
    this->balance = other.balance;

    other.company_name = NULL;
    other.cif = NULL;

    std::cout << "Business_Account moved for " << company_name << std::endl;
}

Business_Account* Business_Account::clone() {
    return new Business_Account(*this);
}

int Business_Account::addBalance(int amount) {
    this->balance += amount;
    return this->balance;
}

//

MoneyTransferService::MoneyTransferService() {
    std::cout << "MoneyTransferService created" << std::endl;
}

bool MoneyTransferService::transfer(User_Account* user, Bank_Account* from, Bank_Account* to, int amount, char* password) {
    if (!(user->verifyPassword(password))) {
        std::cout << "Password is incorrect" << std::endl;
        return false;
    }

    if (amount <= 0) {
        std::cout << "Amount must be positive" << std::endl;
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




/*
Account::Account(char* username, char* password) 
: balance(0)
{
    this->username = new char[strlen(username)];
    memcpy(this->username, username, strlen(username));

    time_t time;
    time = std::time(NULL);
    std::string salt = std::to_string(time);
    this->salt = new char[strlen(salt.c_str())];
    memcpy(this->salt, salt.c_str(), strlen(salt.c_str()));
    
    std::string hashedPassword = sha256(std::string(password) + salt);
    this->password = new char[hashedPassword.length()];
    memcpy(this->password, hashedPassword.c_str(), hashedPassword.length());

    std::cout << "Account created for " << username << std::endl;
    std::cout << "Password: " << this->password << std::endl;
}

Account::~Account() {
    std::cout << "Account destroyed for " << username << std::endl;
    
    delete this->username;
    delete this->password;
    delete this->salt;
}

Account::Account(const Account& other) {
    this->username = new char[strlen(other.username)];
    memcpy(this->username, other.username, strlen(other.username));

    this->password = new char[strlen(other.password)];
    memcpy(this->password, other.password, strlen(other.password));

    this->salt = new char[strlen(other.salt)];
    memcpy(this->salt, other.salt, strlen(other.salt));

    this->balance = other.balance;

    std::cout << "Account copied for " << username << std::endl;
}

Account::Account(Account&& other) {
    this->username = other.username;
    this->password = other.password;
    this->salt = other.salt;
    this->balance = other.balance;

    other.username = NULL;
    other.password = NULL;
    other.salt = NULL;

    std::cout << "Account moved for " << username << std::endl;
}

Account& Account::operator=(const Account& other) {
    this->username = new char[strlen(other.username)];
    memcpy(this->username, other.username, strlen(other.username));

    this->password = new char[strlen(other.password)];
    memcpy(this->password, other.password, strlen(other.password));

    this->salt = new char[strlen(other.salt)];
    memcpy(this->salt, other.salt, strlen(other.salt));

    this->balance = other.balance;

    std::cout << "Account copied for " << username << std::endl;
    return *this;
}

Account& Account::operator=(Account&& other) {
    this->username = other.username;
    this->password = other.password;
    this->salt = other.salt;
    this->balance = other.balance;

    other.username = NULL;
    other.password = NULL;
    other.salt = NULL;

    std::cout << "Account moved for " << username << std::endl;
    return *this;
}

int Account::getBalance() {
    return this->balance;
}

int Account::addBalance(int amount) {
    this->balance += amount;
    return this->balance;
}

bool Account::verifyPassword(char* password) {
    std::string hashedPassword = sha256(password + std::string(this->salt));
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

    if (amount <= 0) {
        std::cout << "Amount must be positive" << std::endl;
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
*/

