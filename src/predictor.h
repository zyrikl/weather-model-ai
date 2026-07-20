#pragma once
// not available for all compilers

#include <vector>

class LinearRegression {
    public:
        double a;
        double b;
        double r;
        double r_sq;

        double predict(double x);
        void info();
};

// Necessary data functions
double get_sum(std::vector<double> x_vals);
double get_prod_sums(std::vector<double> x_vals, std::vector<double> y_vals);
double get_square_sums(std::vector<double> x_vals);
double get_mean(std::vector<double> a_vals);
double get_stddev(std::vector<double> b_vals);
double get_variation(std::vector<double> c_vals);
double get_correlation(std::vector<double> x_vals, std::vector<double> y_vals);

// Linear regressions:
//  - Least squares regression
//  - Deming regression
LinearRegression calculate_lsrl(std::vector<double> x_vals, std::vector<double> y_vals);
LinearRegression calculate_deming(std::vector<double> x_vals, std::vector<double> y_vals);