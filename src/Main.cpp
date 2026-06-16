#include "BlackScholes.h"
#include <iostream>

int main() {
    // Définit tes paramètres
    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;

    // Appel du moteur
    BSResult res = calculate_bs(S, K, r, sigma, T);

    std::cout << "Prix calculé : " << res.price << std::endl;
    std::cout << "Delta : " << res.delta << std::endl;

    return 0;
}