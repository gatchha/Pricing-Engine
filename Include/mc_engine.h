//
// Created by Ulysse B on 18/06/2026.
//

#ifndef PRICING_ENGINE_MC_ENGINE_H
#define PRICING_ENGINE_MC_ENGINE_H
#include "BlackScholes.h"
#include <cmath>
#include <numbers>

struct MCResult {
        double price;
        double stderror_vanilla;
        double stderror_antithetic;

};

MCResult monte_carlo_call(double S, double T, double sigma, double r, double K, double num_sim);
MCResult monte_carlo_asian (double S, double T, double sigma, double r, double K, int num_sim, int num_day);
MCResult monte_carlo_barrier(double S, double T, double sigma, double r, double K, int num_sim,int num_day, double barrier);

#endif //PRICING_ENGINE_MC_ENGINE_H