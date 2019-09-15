#include <vector>
#include <iostream>
#include <future>
#include <mutex>
#include "bootstrap.h"
#include "DailyReturnsCsvReader.h"
#include "financial.h"
#include "stats.h"

using namespace statistics;

std::string header() {
    return "Statistic\tmean\t\t5%\t\t95%";
}

std::vector<std::future<std::string>> dispatch_tasks(const std::vector<double>& daily_returns, int n_samples, std::launch run_mode) {
    std::vector<std::future<std::string>> futures;

    futures.emplace_back(
            std::async(run_mode, [&daily_returns, n_samples](){
                std::vector<double> ann_ret_bootstrap = calc_bootstrap(annual_return, daily_returns, n_samples);
                std::ostringstream oss;
                oss << "Annual return" << "\t" << mean(ann_ret_bootstrap) << "\t" << percentile(ann_ret_bootstrap, 5) << "\t" << percentile(ann_ret_bootstrap, 95);
                return oss.str();
            }));

    futures.emplace_back(
            std::async(run_mode, [&daily_returns, n_samples](){
                std::vector<double> ann_vol_bootstrap = calc_bootstrap(annual_volatility, daily_returns, n_samples);
                std::ostringstream oss;
                oss << "Annual volat " << "\t" << mean(ann_vol_bootstrap) << "\t" << percentile(ann_vol_bootstrap, 5) << "\t" << percentile(ann_vol_bootstrap, 95);
                return oss.str();
            }));

    futures.emplace_back(
            std::async(run_mode, [&daily_returns, n_samples](){
                std::vector<double> sharpe_ratio_bootstrap = calc_bootstrap(sharpe_ratio, daily_returns, 0.0, n_samples);
                std::ostringstream oss;
                oss << "Sharpe ratio " << "\t" << mean(sharpe_ratio_bootstrap) << "\t" << percentile(sharpe_ratio_bootstrap, 5) << "\t" << percentile(sharpe_ratio_bootstrap, 95);
                return oss.str();
            }));

    futures.emplace_back(
            std::async(run_mode, [&daily_returns, n_samples](){
                std::vector<double> max_dd_bootstrap = calc_bootstrap(max_drawdown, daily_returns, n_samples);
                std::ostringstream oss;
                oss << "Max Drawdown " << "\t" << mean(max_dd_bootstrap) << "\t" << percentile(max_dd_bootstrap, 5) << "\t" << percentile(max_dd_bootstrap, 95);
                return oss.str();

            }));

    futures.emplace_back(
            std::async(run_mode, [&daily_returns, n_samples](){
                std::vector<double> var_bootstrap = calc_bootstrap(value_at_risk, daily_returns, 0.05, n_samples);
                std::ostringstream oss;
                oss << "Value-at-risk" << "\t" << mean(var_bootstrap) << "\t" << percentile(var_bootstrap, 5) << "\t" << percentile(var_bootstrap, 95);
                return oss.str();

            }));

    return futures;
}

static std::mutex m;
void print_safely(const std::string &s) {
    std::lock_guard<std::mutex> lock(m);
    std::cout << s << std::endl;
}

void collect_results(std::vector<std::string> &results, std::future<std::string> &f) {
    std::lock_guard<std::mutex> lock(m);
    std::string s = f.get();
    results.emplace_back(s);
}

int main(int argc, char** argv)
{

    std::string file_path;
    std::launch mode;
    int n_samples;
    std::string run_mode;
    std::string debug_mode = "debug";
    if (argc > 1 && debug_mode.compare(argv[1]) == 0 ) {
        file_path = "daily.csv";
        n_samples = 10000;
        run_mode = argv[2];
        if (run_mode == "d" || run_mode == "async") {
            mode = std::launch::async;
        }
        else if(run_mode == "deferred") {
            mode = std::launch::deferred;
        }
    }
    else {
        std::cout << "Welcome to resampling and simulation methods in finance." << std::endl;
        std::cout << "As it currently stands, only bootstrap has been implemented but new methods, such as monte-carlo, will be added soon." << std::endl;
        std::cout << "/-------------------------------------------------------------------------------------------------------------------/ " << std::endl;

        std::cout << "Please enter the full path of the file containg your daily results: [write 'd' for default, which is {$curr_directory}/daily.csv]]";
        std::cin >> file_path;
        if (file_path.empty() || file_path == "d") {
            file_path = "daily.csv";
        }

        std::cout << "Now enter the number of bootstrap samples you want to run: [suggested value is 10000]" << std::endl;
        std::cin >> n_samples;

        std::cout << "Lastly, enter the running mode, which can be async or deferred: [write 'd' for default, which is async]" << std::endl;
        std::cin >> run_mode;
        if (run_mode == "d" || run_mode == "async") {
            mode = std::launch::async;
        }
        else if(run_mode == "deferred") {
            mode = std::launch::deferred;
        }
        else {
            throw "Invalid run mode option";
        }
    }

    DailyReturnsCsvReader csv_reader(file_path);
    std::vector<double> daily_returns = csv_reader.read();

    std::vector<std::future<std::string>> rows = dispatch_tasks(daily_returns, n_samples, mode);

    std::cout << header() << std::endl;
    for(std::future<std::string>& f : rows) {
        std::cout << f.get() << std::endl;
    }

    return 0;
}