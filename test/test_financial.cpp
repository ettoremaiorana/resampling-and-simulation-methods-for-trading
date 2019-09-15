#include "gtest/gtest.h"
#include <vector>
#include <random>
#include "../src/financial.h"
#include "../src/stats.h"

TEST(FinancialTest, TestVaR) {
    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<> dist(0, 0.02);

    std::vector<double> returns;
    for (int i = 1; i < 100; i++) {
        returns.emplace_back(dist(e2));
    }

    double cutoffs[] = {0, 0.0499, 0.05, 0.2, 0.999, 1};
    for (double cutoff : cutoffs) {
        ASSERT_NEAR(
                value_at_risk(returns, cutoff),
                statistics::percentile(returns, cutoff * 100),
        0.001);
    }
}

TEST(FinancialTest, TestMD) {
    double array[] = {0.01, 0.1, -0.04, 0.02, 0.03, 0.02, 0.01, -0.1};
    std::vector<double> returns(array, array + sizeof(array) / sizeof(double));
    ASSERT_NEAR(
            max_drawdown(returns),
            -0.1,
            0.001);
}

TEST(FinancialTest, TestSharpeRatio) {
    double array[] = {0.01, 0.1, -0.04, 0.02, 0.03, 0.02, 0.01, -0.1};
    std::vector<double> returns(array, array + sizeof(array) / sizeof(double));
    ASSERT_NEAR(
            sharpe_ratio(returns, 0),
            1.7238,
            0.0001);
}

TEST(FinancialTest, TestAnnualVolatility) {
    double array[] = {0.01, 0.1, -0.04, 0.02, 0.03, 0.02, 0.01, -0.1};
    std::vector<double> returns(array, array + sizeof(array) / sizeof(double));
    ASSERT_NEAR(
            annual_volatility(returns),
            0.9136,
            0.0001);
}

TEST(FinancialTest, TestAnnualReturn) {
    double array[] = {0.01, 0.1, -0.04, 0.02, 0.03, 0.02, 0.01, -0.1};
    std::vector<double> returns(array, array + sizeof(array) / sizeof(double));
    ASSERT_NEAR(
            annual_return(returns),
            2.3303,
            0.0001);
}

