//
// Created by Ulysse B on 16/06/2026.
//

#include "BlackScholes.h"
#include <cmath>
#include <numbers>

double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2.0));
}

double norm_pdf(double x) {
    return std::exp(-(x * x) * 0.5) / std::sqrt(2.0 * std::numbers::pi);
}

BSResult calculate_bs(double S, double K, double r, double sigma, double T) {
    double sigma_sqrt_T = sigma * std::sqrt(T);
    double d1 = (std::log(S / K) + (r + (sigma * sigma) / 2.0) * T) / sigma_sqrt_T;
    double d2 = d1 - sigma_sqrt_T;

    BSResult res;
    res.price = S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
    res.delta = norm_cdf(d1);
    res.gamma = norm_pdf(d1) / (S * sigma_sqrt_T);
    res.vega  = S * norm_pdf(d1) * std::sqrt(T);

    return res;
}




