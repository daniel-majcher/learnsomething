#include "pricingutil.h"

PricingUtil::PricingUtil()
{
    val = 0;
}

float PricingUtil::calcVal(float prevPrice, float interest, float oleoConstant)
{
    val = (prevPrice * (0.9 + interest)) * oleoConstant;
    return val;
}

float PricingUtil::getVal()
{
    return val;
}