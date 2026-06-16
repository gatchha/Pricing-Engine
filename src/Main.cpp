#include "BlackScholes.h"
#include <iostream>

int main() {

    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;


    BSResult res = calculate_bs(S, K, r, sigma, T);


    return 0;
}