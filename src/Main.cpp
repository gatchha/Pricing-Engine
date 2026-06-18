#include "BlackScholes.h"
#include <iostream>
#include "mc_engine.h"


int main() {

    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;


    BSResult res = calculate_bs(S, K, r, sigma, T);
    std::cout << res.price << std::endl;

    MCResult res2 = monte_carlo_call(S,T,sigma,r,K,1000000);
    std::cout<< res2.St<<std::endl;

    return 0;
}
