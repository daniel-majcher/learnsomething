//
// Created by Ethan on 9/13/2023.
//

#include "hackathonbot.h"

HackathonBot::HackathonBot() {
    actionPrice = 100;
    prev3Prices = {100, 100, 100}; //new price at back. Old prices in front ({three, two, one})
    upWindows = 0;   
    downWindows = 0;
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
    
}

bool HackathonBot::CheckSell(float price) {
    return ( price > (1.89)*actionPrice //89% increase
        || upWindows == 52
        || downWindows == 47
        || price < (.38)*actionPrice); //62% drop
    //wip
}

bool HackathonBot::CheckBuy(float price) {
    return true; //wip
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

