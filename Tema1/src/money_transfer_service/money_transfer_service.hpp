#pragma once

#include <vector>

namespace money_transfer_service {

    class Bank_Account {
        protected:
            int balance;
        public:
            virtual ~Bank_Account() {}
            
            virtual Bank_Account* clone() = 0;

            virtual int getBalance();
            virtual int addBalance(int amount) = 0;
    };

    class Savings_Account : public Bank_Account {
        private:
            char* fullname;
            char* cnp;
        public:
            Savings_Account(char* fullname, char* cnp);
            ~Savings_Account();
            Savings_Account(const Savings_Account& other);
            Savings_Account(Savings_Account&& other);

            virtual Savings_Account* clone() override;

            virtual int addBalance(int amount) override;
    };

    class Business_Account : public Bank_Account {
        private:
            char* company_name;
            char* cif;
        public:
            Business_Account(char* company_name, char* cif);
            ~Business_Account();
            Business_Account(const Business_Account& other);
            Business_Account(Business_Account&& other);

            virtual Business_Account* clone() override;

            virtual int addBalance(int amount) override;
    };

    class User_Account {
        private:
            char* username;
            char* password;
            char* salt;
            std::vector<Bank_Account*> accounts;
        public:
            User_Account(char* username, char* password);
            ~User_Account();
            User_Account(const User_Account& other);
            User_Account(User_Account&& other);

            User_Account& operator=(const User_Account& other);
            User_Account& operator=(User_Account&& other);

            bool verifyPassword(char* password);
            void addAccount(Bank_Account* account);
            std::vector<Bank_Account*> getAccounts();
    };

    class MoneyTransferService {

        public:
            MoneyTransferService();

            bool transfer(User_Account* user, Bank_Account* from, Bank_Account* to, int amount, char* password);
    };
}