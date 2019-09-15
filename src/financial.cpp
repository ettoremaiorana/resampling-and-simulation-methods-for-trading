//
// Created by ivan on 13/09/2019.
//

#include "financial.h"
#include "stats.h"
#include <limits>

std::vector<double> adjust_returns(const std::vector<double>& daily_returns, double risk_free)
{
    if (risk_free == 0) {
        return daily_returns;
    }
    std::vector<double> returns_risk_adj;
    returns_risk_adj.reserve(daily_returns.size());
    std::for_each(daily_returns.begin(), daily_returns.end(), [&returns_risk_adj, risk_free](double val) {
        returns_risk_adj.emplace_back(val - risk_free);
    });
    return returns_risk_adj;
}

double annualization_factor()
{
    //TODO extend to weekly, monthly and yearly cases
    return 252;
}

std::vector<double> cum_returns(const std::vector<double>& daily_returns, double start)
{
    if (start == 0) {
        start = 100;
    }
    std::vector<double> output;
    output.reserve(daily_returns.size());
    std::for_each(daily_returns.begin(), daily_returns.end(), [&output](double val) {
        output.emplace_back(val + 1);
    }); //array + 1
    for (int i = 0; i < output.size(); i++) {
        output[i] = start * output[i];
        start = output[i];
    } //cumulative product
    return output;
}

double cum_returns_final(const std::vector<double>& daily_returns)
{
    if (daily_returns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double product = std::accumulate(daily_returns.begin(), daily_returns.end(), 1.0, [](double temp, double a) {
        return temp*(a+1);
    });
    return product;
}

std::vector<double> rolling_max(const std::vector<double>& input)
{
    std::vector<double> output;
    output.reserve(input.size());
    double curr_max = input[0];
    output.emplace_back(curr_max);
    for (int i = 1; i < input.size(); i++) {
        if(curr_max < input[i]) {
            curr_max = input[i];
        }
        output.emplace_back(curr_max);
    }
    return output;
}

double annual_return(const std::vector<double>& daily_returns)
{
    if (daily_returns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double ann_factor = annualization_factor();
    double num_years = static_cast<double>(daily_returns.size())/ann_factor;
    double ending_value = cum_returns_final(daily_returns);
    return pow(ending_value, 1.0/num_years) - 1;
}

double annual_volatility(const std::vector<double>& daily_returns)
{
    if (daily_returns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    double ann_factor = annualization_factor();
    double volatility = statistics::std(daily_returns);
    double ann_volatility = volatility * sqrt(ann_factor);
    return ann_volatility;
}

double sharpe_ratio(const std::vector<double>& daily_returns, double risk_free)
{
    double ann_factor = annualization_factor();
    std::vector<double> risk_adj_returns = adjust_returns(daily_returns, risk_free);
    double m = statistics::mean(risk_adj_returns);
    double s = statistics::std(risk_adj_returns);
    return (m / s) * sqrt(ann_factor);
}

double max_drawdown(const std::vector<double>& daily_returns)
{
    if (daily_returns.empty()) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    std::vector<double> cumulative = cum_returns(daily_returns, 100);
    std::vector<double> max_return = rolling_max(cumulative);
    std::vector<double> drawdown;
    drawdown.reserve(max_return.size());
    for (int i = 0; i < max_return.size(); i++) {
        drawdown.emplace_back((cumulative[i] - max_return[i]) / max_return[i]);
    }
    return *std::min_element(drawdown.begin(), drawdown.end());
}

double value_at_risk(const std::vector<double>& daily_returns, double cutoff_percentage)
{
    return statistics::percentile(daily_returns, 100 * cutoff_percentage);
}