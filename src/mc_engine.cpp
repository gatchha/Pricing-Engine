
#include <cmath>

#include "mc_engine.h"

#include <random>

MCResult monte_carlo_call(double S, double T, double sigma, double r, double K, double num_sim) {
    double u = S*(std::exp((r-(sigma*sigma)/2)*T));
    double sqrtT = std::sqrt(T);
    double volTerme = sigma*sqrtT;
    double discountFactor = std::exp(-r*T);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 1.0);

    double payoffSum1 = 0.0;
    double payoffSquaredSum1 = 0.0;
    double payoffSum2 = 0.0;
    double payoffSquaredSum2 = 0.0;

    for (int i = 0; i < num_sim; i++) {
        double Z1 = dis(gen);
        double Z2 = -Z1;
        double St1 = u * std::exp(volTerme*Z1);
        double St2 = u * std::exp(volTerme*Z2);
        double payoff = std::max(St1-K, 0.0);
        double payoff2 = std::max(St2-K, 0.0);
        double payoffF = (payoff+payoff2)/2;
        payoffSum1 += payoffF;
        payoffSquaredSum1 += payoffF*payoffF;
        payoffSum2 += payoff;
        payoffSquaredSum2 += payoff*payoff;


    }

    double MeanPayoff1 = payoffSum1 / num_sim;
    double MeanPayoffsquared1 = payoffSquaredSum1 / num_sim;
    double variance1 = MeanPayoffsquared1 - (MeanPayoff1 * MeanPayoff1);
    double stdDev1 = std::sqrt(variance1);
    double stderror_anti = stdDev1 / std::sqrt(num_sim);

    double MeanPayoff2 = payoffSum2 / num_sim;
    double MeanPayoffsquared2 = payoffSquaredSum2 / num_sim;
    double variance2 = MeanPayoffsquared2 - (MeanPayoff2 * MeanPayoff2);
    double stdDev2 = std::sqrt(variance2);
    double stderror_vanilla = stdDev2 / std::sqrt(num_sim);

    MCResult f;
    f.price = MeanPayoff1 * discountFactor;
    f.stderror_antithetic = stderror_anti * discountFactor;
    f.stderror_vanilla = stderror_vanilla * discountFactor;

    return f;

}


