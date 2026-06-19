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
    double sqrt_T = std::sqrt(T);
    double sigma_sqrt_T = sigma * sqrt_T;
    double discountFactor= std::exp(-r * T);

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / sigma_sqrt_T;
    double d2 = d1 - sigma_sqrt_T;

    double pdf_d1 = norm_pdf(d1);
    double cdf_d2 = norm_cdf(d2);

    BSResult res;
    res.price = S * norm_cdf(d1) - K * discountFactor * cdf_d2;
    res.delta = norm_cdf(d1);
    res.gamma = pdf_d1 / (S * sigma_sqrt_T);
    res.vega  = S * pdf_d1 * sqrt_T;
    res.theta = -(S * pdf_d1 * sigma) / (2.0 * sqrt_T) - r * K * discountFactor* cdf_d2;
    res.rho   = K * T * discountFactor * cdf_d2;

    return res;
}