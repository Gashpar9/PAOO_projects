#pragma once

class Account {
    private:
        char* username;
        char* password;
        int balance;

    public:
        Account(char* username, char* password);
        ~Account();
        Account(const Account& other);
        Account(Account&& other);

        bool verifyPassword(char* password);
        int getBalance();
        int addBalance(int amount);
};

class MoneyTransferService {

    public:
        MoneyTransferService();

        bool transfer(Account* from, Account* to, int amount, char* password);
};