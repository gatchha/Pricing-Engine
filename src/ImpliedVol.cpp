//
// Created by Ulysse B on 20/06/2026.
//

#include "ImpliedVol.h"
#include "BlackScholes.h"
#include <cmath>

double implied_vol_bisection(double S, double K, double T, double market_price, double r) {

    double epsilon = 0.00000001;
    double lower_bound = 0.001;
    double upper_bound = 5;
    double sigma_mid = (lower_bound + upper_bound)/2;
    BSResult f_sigma = calculate_bs(S,K,r,sigma_mid,T);
    while (std::abs(market_price - f_sigma.price) > epsilon) {
        if (f_sigma.price > market_price) {
            upper_bound = sigma_mid;
            sigma_mid = (lower_bound + upper_bound)/2;
        }
        else {
            lower_bound = sigma_mid;
            sigma_mid = (lower_bound + upper_bound)/2;
        }
        f_sigma = calculate_bs(S,K,r,sigma_mid,T);

    }
    return sigma_mid;
}

double implied_vol_newton(double S, double K, double T, double market_price, double r) {
    double sigma = 0.2;
    double epsilon = 0.00000001;
    BSResult bsp = calculate_bs(S,K,r,sigma,T);
    while (std::abs(market_price-bsp.price)>epsilon) {
        sigma = sigma - (bsp.price-market_price)/bsp.vega;
        bsp = calculate_bs(S,K,r,sigma,T);

    }
    return sigma;
}
