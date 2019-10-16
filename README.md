

# Introduction

This project aims to give statistical significance to a list of daily results, possibly coming from a trading algorithm
run in backtest mode. </p>

At the moment, the project is only able to run a bootstrap analysis, which is nothing more than a resampling method, 
giving the range of statistical significance of the backtest results. Future development will include monte-carlo testing 
and bayesian analysis. </p>

The implementation reference has been Pyfolio and Empyrical, which are two projects owned by Quantopian and freely 
available on github. Full credits go to them, but the bugs in this project are all mine. </p>

 

## Getting Started

This project requires the package manager Conan in order to install its dependencies:

``` bash
pip install conan
conan profile new udacity
vim /root/.conan/profiles/udacity
```

then copy/paste the following content:

``` bashThe README also indicates the file and class structure, along with the expected behavior or output of the program.


[settings]
os=Linux
os_build=Linux
arch=x86_64
arch_build=x86_64
compiler=gcc
compiler.version=7
compiler.libcxx=libstdc++11
build_type=Release
[options]
[build_requires]
[env]
```

Clone this repository locally :

``` bash
git clone https://ivan_valeriani@bitbucket.org/ivan_valeriani/resampling-and-simulation-methods-for-trading.git
cd resampling-and-simulation-methods-for-trading
```

The list of dependencies can be found in conanfile.txt; to install them:

``` bash
conan install /home/workspace/resampling-and-simulation-methods-for-trading -if=/home/workspace/resampling-and-simulation-methods-for-trading/cmake-build-debug -pr=udacity
```

Build and execute

``` bash
cd cmake-build-debug
cmake ../
make
cp ../daily.csv ./bin/
cd bin && ./resampling
```

## How does it work

The program digests a header-less csv file  whose rows are of the format <date>,<double> indicating the earning 
percentage on that specific trading day. The sample file included in the project is just a normally randomized list of 
numbers with zero real significance. It includes 1000 days, without considering weekends and holidays. </p>
The program expects two other inputs: the number of bootstrap samples to generate (the bigger the number, the longer 
the program takes to terminate, the more statistical significance the numbers have) and the running mode (async or 
deferred). </p> 

## What the expected outcome of this project should be
Given a set of user's input, the program should print a table of statistics and their respective statistical confidence 
interval.  


## Testing
There is a small set of unit tests available, generating a ./test executable along with the main program.


