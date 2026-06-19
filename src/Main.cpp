#include "BlackScholes.h"
#include <iostream>
#include "mc_engine.h"

int main() {
    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;
    int num_day = 252, num_sim = 1000000;


    BSResult res = calculate_bs(S, K, r, sigma, T);
    std::cout << "--- Pricing Engine ---" << std::endl;
    std::cout << "Black-Scholes Price : " << res.price << std::endl;


    MCResult res2 = monte_carlo_call(S, T, sigma, r, K, 1000000);
    std::cout << "Monte Carlo Price   : " << res2.price << std::endl;
    std::cout << "Std Error (Vanilla) : " << res2.stderror_vanilla << std::endl;
    std::cout << "Std Error (Antithetique)    : " << res2.stderror_antithetic << std::endl;


    double variance_vanilla = res2.stderror_vanilla * res2.stderror_vanilla;
    double variance_anti = res2.stderror_antithetic * res2.stderror_antithetic;
    double VRF = variance_vanilla / variance_anti;
    std::cout << "Variance Reduction Factor (VRF) : " << VRF << std::endl;


    double lowerBound = res2.price - (1.96 * res2.stderror_antithetic);
    double upperBound = res2.price + (1.96 * res2.stderror_antithetic);

    std::cout << "Confidence Interval 95% : [" << lowerBound << ", " << upperBound << "]" << std::endl;

    MCResult res_asian = monte_carlo_asian(S, T, sigma, r, K, num_sim, num_day);

    std::cout << "Monte Carlo Price (Asiatique) : " << res_asian.price << std::endl;
    std::cout << "Std Error (Vanilla)           : " << res_asian.stderror_vanilla << std::endl;

    double lower_asian = res_asian.price - (1.96 * res_asian.stderror_vanilla);
    double upper_asian = res_asian.price + (1.96 * res_asian.stderror_vanilla);

    std::cout << "Confidence Interval 95%       : [" << lower_asian << ", " << upper_asian << "]" << std::endl;
    return 0;
}