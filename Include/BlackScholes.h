//
// Created by Ulysse B on 16/06/2026.
//
#ifndef PRICING_ENGINE_BLACKSCHOLES_H
#define PRICING_ENGINE_BLACKSCHOLES_H

struct BSResult {
    double price, delta, gamma, vega, theta, rho;
};



double norm_cdf(double x);
double norm_pdf(double x);
BSResult calculate_bs(double S, double K, double r, double sigma, double T);

#endif //PRICING_ENGINE_BLACKSCHOLES_H