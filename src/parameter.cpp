#include "parameter.h"
#include "predictor.h"
#include "table.h"
#include <cmath>
#include <vector>

LinearRegression identify_parameters(std::vector<double> x_vals, std::vector<double> y_vals) {
	std::vector<std::vector<double>> parameter_table = create_table("./model/parameters.txt");
	double p_lsrl = parameter_table[0][0];
	double p_deming = parameter_table[0][1];

    LinearRegression rval;

    rval.a = calculate_lsrl(x_vals, y_vals).a * p_lsrl
            + calculate_deming(x_vals, y_vals).a * p_deming;
    rval.b = calculate_lsrl(x_vals, y_vals).b * p_lsrl
            + calculate_deming(x_vals, y_vals).b * p_deming;

    rval.r = get_correlation(x_vals, y_vals);
    rval.r_sq = std::pow(rval.r, 2);
    
    return rval;
}