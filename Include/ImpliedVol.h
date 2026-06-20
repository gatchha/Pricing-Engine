//
// Created by Ulysse B on 20/06/2026.
//

#ifndef PRICING_ENGINE_VOL_H
#define PRICING_ENGINE_VOL_H

double implied_vol_bisection(double S, double K, double T, double market_price, double r);
double implied_vol_newton(double S, double K, double T, double market_price, double r);





#endif //PRICING_ENGINE_VOL_H