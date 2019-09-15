//
// Created by ivan on 11/09/2019.
//

#include <vector>

std::vector<double> calc_bootstrap(double (*stat)(const std::vector<double>&) , const std::vector<double>& returns, int n_samples);
std::vector<double> calc_bootstrap(double (*stat)(const std::vector<double>& input, double percentage) , const std::vector<double>& returns, double percentage, int n_samples);
