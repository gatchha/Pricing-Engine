
#include <cmath>

#include "mc_engine.h"

#include <random>

MCResult monte_carlo_call(double S, double T, double sigma, double r, double K, double num_sim) {
    double u = S*(std::exp((r-(sigma*sigma)/2)*T));
    double racineT = std::sqrt(T);
    double vol_Terme = sigma*racineT;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> dis(0.0, 1.0);

    double gains = 0.0;

    for (int i = 0; i < num_sim; i++) {
        double Z = dis(gen);
        double St = u * std::exp(vol_Terme*Z);
        double payoff = std::max(St-K, 0.0);
        gains += payoff;

    }

    double MeanPayoff = gains / num_sim;
    MCResult f;
    f.St = MeanPayoff*std::exp(-r*T);
    return f;


}


