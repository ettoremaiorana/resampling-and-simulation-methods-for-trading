//
// Created by ivan on 11/09/2019.
//

#include "gtest/gtest.h"
#include <vector>
#include <random>
#include "../src/bootstrap.h"
#include "../src/stats.h"
using namespace boost::accumulators;

TEST (BootstrapTest, NumbersMatch) {

    std::random_device rd;
    std::mt19937 e2(rd());
    std::normal_distribution<> dist(0, 1);

    std::vector<double> returns;
    for (int i = 1; i < 1000; i++) {
        returns.emplace_back(dist(e2));
    }

    std::vector<double> samples = calc_bootstrap(statistics::mean, returns, 10000);
    const double mean_of_mean = statistics::mean(returns);
    const double sd_of_mean = static_cast<double>(statistics::std(returns)) / sqrt(returns.size()-1);
    const double mean_of_samples = statistics::mean(samples);
    const double std_of_samples = statistics::std(samples);

    ASSERT_NEAR(mean_of_samples, mean_of_mean, 0.001);
    ASSERT_NEAR(std_of_samples, sd_of_mean, 0.001);

}

