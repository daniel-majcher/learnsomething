#include <gtest/gtest.h>
#include <pricingutil.h>

TEST(sampleTest, sample) {
    EXPECT_EQ(4, 4);
}

TEST(TestPricingUtil, CalcGetVal)
{
    PricingUtil pu = PricingUtil();
    EXPECT_EQ(12, pu.calcVal(3, 1.1, 2));
    EXPECT_EQ(12, pu.getVal());

    EXPECT_EQ(9, pu.calcVal(10, 0, 1));
    EXPECT_EQ(9, pu.getVal());
}