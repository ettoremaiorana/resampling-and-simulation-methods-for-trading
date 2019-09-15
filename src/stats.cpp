//
// Created by ivan on 14/09/2019.
//
#include <vector>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include "stats.h"

namespace statistics {
    double mean(const std::vector<double>& input)
    {
        boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
        for (double value : input) {
            acc(value);
        }
        return boost::accumulators::mean(acc);
    }

    double variance(const std::vector<double>& input)
    {
        boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::variance>> acc;
        for (double value : input) {
            acc(value);
        }
        return boost::accumulators::variance(acc);
    }

    double std(const std::vector<double>& input)
    {
        if (input.size() < 2) {
            return std::numeric_limits<double>::quiet_NaN();
        }
        double sum = 0;
        double m = mean(input);
        for (int i = 0; i < input.size(); i++)
            sum = sum + pow((input[i] - m),2);

        return sqrt(sum / (input.size() - 1));
    }

    double percentile(std::vector<double> input, double percent)
    {
        auto nth = input.begin() + (percent * input.size()) / 100;
        std::nth_element(input.begin(), nth, input.end());
        return *nth;
    }
}


