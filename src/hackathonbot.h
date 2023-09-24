//
// Created by Ethan on 9/13/2023.
//

#include <vector>
#include "action.h"

#ifndef LEARNSOMETHING_HACKATHONBOT_H
#define LEARNSOMETHING_HACKATHONBOT_H

//inherit from action for basic action handling
class HackathonBot : Action {
public:
    HackathonBot();
    void takeAction(float price);
    bool isHolding();
private:
    double actionPrice; //sell price you sold it at or buy price you bought it at
    int upWindows;
    int downWindows;
    std::vector<double> prev3Prices;
    void UpdateState(float price);
    // Method to buy a specific quantity at a specific price
    bool CheckSell(float price);
    bool CheckBuy(float price);

    bool sell(double price) {
        Action::sell(price);
        actionPrice = price;
    }

    bool buy(double price) {
        Action::buy(price);
        actionPrice = price;
    }
};

#endif //LEARNSOMETHING_HACKATHONBOT_H
