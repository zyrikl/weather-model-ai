#pragma once

#include "predictor.h"
#include <vector>

LinearRegression identify_parameters(std::vector<double> x_vals, std::vector<double> y_vals);