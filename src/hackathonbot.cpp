//
// Created by Ethan on 9/13/2023.
//

#include "hackathonbot.h"

HackathonBot::HackathonBot() {
    actionPrice = 100;
    prev3Prices = {100, 100, 100}; //new price at back. Old prices in front ({three, two, one})
    upWindows = 0;   
    downWindows = 0;
    lastActed = 0;
    nonVolatileWindows = 0;
}

bool HackathonBot::isHolding() {
    return getHold();
}

void HackathonBot::UpdateState(float price) {
    if (price > prev3Prices.back()) {
        upWindows++;
        downWindows=0;
    } else if (price < prev3Prices.back()) {
        downWindows++;
        upWindows=0;
    } else {
        upWindows=0;
        downWindows=0;
    }
    lastActed += 1;

    if (price <= 1.05*prev3Prices[2] && price >= .95*prev3Prices[2]) {
        nonVolatileWindows++;
    } else {
        nonVolatileWindows = 0;
    }
}

bool HackathonBot::CheckSell(float price) {
    bool ret = ( price > (1.89)*actionPrice //89% increase
        || upWindows == 52
        || downWindows == 47
        || price < (.38)*actionPrice); //62% drop
    //wip
    //drops 15, rises 15, drops 25. Down overall 45
    bool complex1 = (lastActed == 3 
    && prev3Prices[1] <= .85*prev3Prices[0]
    && prev3Prices[2] >= 1.15*prev3Prices[1]
    && price <= .75*prev3Prices[2]
    && price <= .55*prev3Prices[0]);

    //raises 20, drops 15, raises 30. Overall down 45
    bool complex2 = (lastActed == 3 
    && prev3Prices[1] >= 1.2*prev3Prices[0]
    && prev3Prices[2] >= .85*prev3Prices[1]
    && price <= 1.3*prev3Prices[2]
    && price >= 1.5*prev3Prices[0]);

    bool notVolatile = (nonVolatileWindows >= 5 && lastActed >= 5);

    return ret || complex1 || complex2 || notVolatile;
}

bool HackathonBot::CheckBuy(float price) {
    bool ret = ( price < 52
    || (lastActed >= 5 && downWindows >= 5) );
    return ret;
}

void HackathonBot::takeAction(float price) {
    UpdateState(price);
    if (getHold()) {
        //check if you should sell
        if (CheckSell(price)) {
            sell(price);
            return;
        }
    } else {
        if (CheckBuy(price)) {
            buy(price);
            return;
        }
    }

    prev3Prices.erase(prev3Prices.begin()); //update after you're done using it
    prev3Prices.push_back(price);
}

