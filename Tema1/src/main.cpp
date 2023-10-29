#include <iostream>

#include "money_transfer_service.hpp"

int main() {
    MoneyTransferService mts;

    Account a1((char*)"Vlad", (char*)"qwerty");
    Account a2((char*)"Dragos", (char*)"12345");

    // Functionality test
    a1.addBalance(100);

    mts.transfer(&a1, &a2, 50, (char*)"qwerty");
    std::cout << "a1 balance: " << a1.getBalance() << std::endl;
    std::cout << "a2 balance: " << a2.getBalance() << std::endl;


    // Constructor test
    Account a3(a1);
    std::cout << "a3 balance: " << a3.getBalance() << std::endl;

    Account a4(std::move(a1));
    std::cout << "a4 balance: " << a4.getBalance() << std::endl;

    return 0;
}