//
// Created by ivan on 11/09/2019.
//

#include "bootstrap.h"
#include <random>

static std::random_device rd;
static std::mt19937 e2(rd());


std::vector<double> calc_bootstrap(double (*stat)(const std::vector<double>& input) , const std::vector<double>& returns, int n_samples) {
    std::uniform_int_distribution<> dist(0, returns.size() - 1);

    std::vector<double> out;
    out.reserve(n_samples);
    for (int i = 0; i < n_samples; i++) {
        std::vector<double> returns_i;
        returns_i.reserve(returns.size());
        for (int j = 0; j < returns.size(); j++) {
            int idx = dist(e2);
            returns_i.emplace_back(returns[idx]);
        }
        out.emplace_back(stat(returns_i));
    }
    return out;
}

std::vector<double> calc_bootstrap(double (*stat)(const std::vector<double>& input, double percentage) , const std::vector<double>& returns, double percentage, int n_samples) {
    std::uniform_int_distribution<> dist(0, returns.size() - 1);

    std::vector<double> out;
    out.reserve(n_samples);
    for (int i = 0; i < n_samples; i++) {
        std::vector<double> returns_i;
        returns_i.reserve(returns.size());
        for (int j = 0; j < returns.size(); j++) {
            int idx = dist(e2);
            returns_i.emplace_back(returns[idx]);
        }
        out.emplace_back(stat(returns_i, percentage));
    }
    return out;
}
