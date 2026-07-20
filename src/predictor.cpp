#include "predictor.h"
#include <numeric>
#include <cmath>
#include <iostream>
#include <string>

double LinearRegression::predict(double x) {
    return a + b * x;
}

void LinearRegression::info() {
    std::cout << std::string("y^ = ") + std::to_string(a) + std::string(" + (") + std::to_string(b) + std::string(")x\nr = ") + std::to_string(r) + std::string(", R^2 = ") + std::to_string(r_sq * 100) + std::string("%.") << std::endl;
}

double get_sum(std::vector<double> x_vals) {
    return std::reduce(x_vals.begin(), x_vals.end());
}

double get_prod_sums(std::vector<double> x_vals, std::vector<double> y_vals) {
    std::vector<double> rval;

    for (int i = 0; i < x_vals.size(); i++) {
        rval.push_back(x_vals[i] * y_vals[i]);
    }

    return std::reduce(rval.begin(), rval.end());;
}

double get_square_sums(std::vector<double> x_vals) {
    std::vector<double> rval;

    for (int i = 0; i < x_vals.size(); i++) {
        rval.push_back(std::pow(x_vals[i], 2));
    }

    return std::reduce(rval.begin(), rval.end());
}

double get_mean(std::vector<double> a_vals) {
    return std::reduce(a_vals.begin(), a_vals.end()) / a_vals.size();
}

double get_stddev(std::vector<double> b_vals) {
    double mean = get_mean(b_vals);

    double sq_sum = 0.0;
    for (double x : b_vals) {
        sq_sum += std::pow((x - mean), 2);
    }

    return std::sqrt(sq_sum / (b_vals.size() - 1));
}

double get_prod_stddev(std::vector<double> x_vals, std::vector<double> y_vals) {
    double x_mean = get_mean(x_vals);
    double y_mean = get_mean(y_vals);

    double sq_sum = 0.0;
    for (int i = 0; i < x_vals.size(); i++) {
        sq_sum += (x_vals[i] - x_mean) * (y_vals[i] - y_mean);
    }

    return sq_sum;
}

double get_variation(std::vector<double> b_vals) {
    double mean = get_mean(b_vals);

    double sq_sum = 0.0;
    for (double x : b_vals) {
        sq_sum += (x - mean) * (x - mean);
    }

    return sq_sum / (b_vals.size() - 1);
}

double get_correlation(std::vector<double> x_vals, std::vector<double> y_vals) {
    return (
        (x_vals.size() * get_prod_sums(x_vals, y_vals))
      - (get_sum(x_vals) * get_sum(y_vals))
    ) / std::sqrt(
        (
            (x_vals.size() * get_square_sums(x_vals))
          - (std::pow(get_sum(x_vals), 2))
        ) * (
            (y_vals.size() * get_square_sums(y_vals))
          - (std::pow(get_sum(y_vals), 2))
        )
    );
}

LinearRegression calculate_lsrl(std::vector<double> x_vals, std::vector<double> y_vals) {
    LinearRegression rval;

    rval.r = get_correlation(x_vals, y_vals);
    rval.r_sq = std::pow(rval.r, 2);

    rval.b = rval.r * (get_stddev(y_vals) / get_stddev(x_vals));
    rval.a = get_mean(y_vals) - rval.b * get_mean(x_vals);

    return rval;
}

LinearRegression calculate_deming(std::vector<double> x_vals, std::vector<double> y_vals) {
    LinearRegression rval;
    rval.r = get_correlation(x_vals, y_vals);
    rval.r_sq = std::pow(rval.r, 2);
    double lambda = get_variation(y_vals) / get_variation(x_vals);

    double x_mean = get_mean(x_vals);
    double y_mean = get_mean(y_vals);

    double Sxx = 0.0, Syy = 0.0, Sxy = 0.0;
    for (int i = 0; i < x_vals.size(); ++i) {
        double dx = x_vals[i] - x_mean;
        double dy = y_vals[i] - y_mean;
        Sxx += dx * dx;
        Syy += dy * dy;
        Sxy += dx * dy;
    }

    double c = Syy - lambda * Sxx;
    double b1 = (c + std::sqrt(c * c + 4.0 * lambda * Sxy * Sxy)) / (2.0 * Sxy);
    double b0 = y_mean - b1 * x_mean;

    rval.a = b0;
    rval.b = b1;

    return rval;
}