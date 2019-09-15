//
// Created by ivan on 12/09/2019.
//
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

namespace statistics {
    double mean(const std::vector<double>& input);
    double variance(const std::vector<double>& input);
    double std(const std::vector<double>& input);
    double percentile(std::vector<double> input, double percent);
}


