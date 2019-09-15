//
// Created by ivan on 13/09/2019.
//
#include <vector>

double annual_return(const std::vector<double>& daily_returns);
double annual_volatility(const std::vector<double>& daily_returns);
double sharpe_ratio(const std::vector<double>& daily_returns, double risk_free);
double max_drawdown(const std::vector<double>& daily_returns);
double value_at_risk(const std::vector<double>& daily_returns, double cutoff_percentage);
