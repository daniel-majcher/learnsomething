//
// Created by Ethan on 9/13/2023.
//

#include "action.h"


Action::Action(bool initHold = true) : holding(initHold) {
    initialBalance = 0; //not sure what purpose of initialBalance is
    balance = 0;
}

bool Action::buy(double price) {
    if (!holding && balance>=price) {
        balance -= price;
        return true;
    } else {
        return false;
    }
}

bool Action::sell(double price) {
    if (holding) {
        balance += price;
        return true;
    } else {
        return false;
    }
}

bool Action::getHold() {
    return holding;
}

double Action::getBalance() {
    return balance;
}
