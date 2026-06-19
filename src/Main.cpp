#include <iostream>
#include <chrono>
#include <iomanip>
#include "mc_engine.h"

int main() {
    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;
    int num_sim = 1000000;
    int num_day = 252;
    double barrier = 120.0;


    std::cout << "[1/3] Pricing Call Européen..." << std::flush;
    auto start_eur = std::chrono::high_resolution_clock::now();
    MCResult res_eur = monte_carlo_call(S, T, sigma, r, K, num_sim);
    auto end_eur = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_eur = end_eur - start_eur;
    std::cout << "      Prix: " << std::fixed << std::setprecision(5) << res_eur.price
              << " | Temps: " << time_eur.count() << " sec\n" << std::endl;


    std::cout << "[2/3] Pricing Call Asiatique (252 jours)..." << std::flush;
    auto start_asian = std::chrono::high_resolution_clock::now();
    MCResult res_asian = monte_carlo_asian(S, T, sigma, r, K, num_sim, num_day);
    auto end_asian = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_asian = end_asian - start_asian;
    std::cout << "      Prix: " << res_asian.price
              << " | Temps: " << time_asian.count() << " sec\n" << std::endl;


    std::cout << "[3/3] Pricing Barrière Up-and-Out (B=" << barrier << ")..." << std::flush;
    auto start_bar = std::chrono::high_resolution_clock::now();
    MCResult res_bar = monte_carlo_barrier(S, T, sigma, r, K, num_sim, num_day, barrier);
    auto end_bar = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_bar = end_bar - start_bar;
    std::cout << "       Prix: " << res_bar.price
              << " | Temps: " << time_bar.count() << " sec\n" << std::endl;

    return 0;
}