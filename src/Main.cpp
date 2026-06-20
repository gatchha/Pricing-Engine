#include <iostream>
#include <chrono>
#include <iomanip>

#include "ImpliedVol.h"
#include "mc_engine.h"
#include "BlackScholes.h"

int main() {
    double S = 100.0, K = 100.0, r = 0.05, sigma = 0.2, T = 1.0;
    int num_sim = 1000000;
    int num_day = 252;
    double barrier = 120.0;


    std::cout << "Pricing European Call ..." << std::flush;
    auto start_eur = std::chrono::high_resolution_clock::now();
    MCResult res_eur = monte_carlo_call(S, T, sigma, r, K, num_sim);
    auto end_eur = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_eur = end_eur - start_eur;
    std::cout<<"\r\033[2K";
    std::cout << "      EU call Price: " << std::fixed << std::setprecision(5) << res_eur.price
              << " | Time: " << time_eur.count() << " sec\n" << std::endl;


    std::cout << " Pricing Asian Call (252 days)..." << std::flush;
    auto start_asian = std::chrono::high_resolution_clock::now();
    MCResult res_asian = monte_carlo_asian(S, T, sigma, r, K, num_sim, num_day);
    auto end_asian = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_asian = end_asian - start_asian;
    std::cout<<"\r\033[2K";
    std::cout << "      Asian call Price: " << res_asian.price
              << " | Time: " << time_asian.count() << " sec\n" << std::endl;


    std::cout << "Pricing Barrière Up-and-Out (B=" << barrier << ")..." << std::flush;
    auto start_bar = std::chrono::high_resolution_clock::now();
    MCResult res_bar = monte_carlo_barrier(S, T, sigma, r, K, num_sim, num_day, barrier);
    auto end_bar = std::chrono::high_resolution_clock::now();
    std::cout<<"\r\033[2K";
    std::chrono::duration<double> time_bar = end_bar - start_bar;
    std::cout << "       Price: " << res_bar.price
              << " | Time: " << time_bar.count() << " sec\n" << std::endl;

    std::cout<<"Standard error : "<<res_asian.stderror_vanilla<<std::endl;
    std::cout<<"Control variate standard error : "<<res_asian.stderror_cv<<std::endl;


    std::cout<<"BS price :" << calculate_bs( S,  K,  r, sigma,  T).price<<std::endl;

    std::cout<<"Implied volatility via bisection..."<<std::flush;
    auto start = std::chrono::high_resolution_clock::now();
    double vol =implied_vol_bisection(S,K,T,calculate_bs( S,  K,r, sigma,  T).price,r);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_end = end - start;
    std::cout<<"\r\033[2K";
    std::cout<<"Implied vol for precedent BS price (with bisection): \n"<< vol;
    std::cout<<"time :"<< time_end.count() << " sec\n";

    std::cout<<"Implied volatility via Newton-Raphson..."<<std::flush;
    auto debut = std::chrono::high_resolution_clock::now();
    double vol2 = implied_vol_newton(S,K,T,calculate_bs( S,  K,r, sigma,  T).price,r);
    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_fin = fin - debut;
    std::cout<<"\r\033[2K";
    std::cout<<"Implied volatility with Newton-Raphson :\n"<< vol2<<"\n";
    std::cout<<"time"<< time_fin.count() << " sec\n";


    return 0;
}