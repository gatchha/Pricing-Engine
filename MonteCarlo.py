import math
import random
import time

def monte_carlo_call_python(S, T, sigma, r, K, num_sim):
    u = S * math.exp((r - (sigma ** 2) / 2) * T)
    vol_terme = sigma * math.sqrt(T)
    discount_factor = math.exp(-r * T)

    payoff_sum = 0.0

    for _ in range(num_sim):
        u1 = random.random()
        u2 = random.random()
        Z1 = math.sqrt(-2.0 * math.log(u1)) * math.cos(2.0 * math.pi * u2)

        St = u * math.exp(vol_terme * Z1)
        payoff = max(St - K, 0.0)
        payoff_sum += payoff

    price = (payoff_sum / num_sim) * discount_factor
    return price

if __name__ == "__main__":
    S, K, r, sigma, T = 100.0, 100.0, 0.05, 0.2, 1.0
    num_sim = 1000000

    print("Lancement du benchmark Python (1 million de simulations)...")
    start_time = time.time()

    prix = monte_carlo_call_python(S, T, sigma, r, K, num_sim)

    end_time = time.time()
    execution_time = end_time - start_time

    print(f"Prix calculé par Python : {prix:.5f}")
    print(f"Temps d'exécution Python : {execution_time:.4f} secondes")

    def monte_carlo_asian_python(S, T, sigma, r, K, num_sim, num_day):
        dt = T / num_day
        drift = math.exp((r - (sigma ** 2) / 2.0) * dt)
        vol_terme = sigma * math.sqrt(dt)
        discount_factor = math.exp(-r * T)

        payoff_sum = 0.0

        for _ in range(num_sim):
            current_S = S
            st_sum = 0.0

            for _ in range(num_day):
                u1 = random.random()
                u2 = random.random()
                Z1 = math.sqrt(-2.0 * math.log(u1)) * math.cos(2.0 * math.pi * u2)

                current_S = current_S * drift * math.exp(vol_terme * Z1)
                st_sum += current_S

            payoff = max((st_sum / num_day) - K, 0.0)
            payoff_sum += payoff

            return (payoff_sum / num_sim) * discount_factor

if __name__ == "__main__":
    S, K, r, sigma, T = 100.0, 100.0, 0.05, 0.2, 1.0
    num_sim = 1000000
    num_day = 252


    print("\n[1/2] Python - Call Européen...")
    start = time.time()
    prix_eur = monte_carlo_call_python(S, T, sigma, r, K, num_sim)
    print(f"Prix: {prix_eur:.5f} | Temps: {time.time() - start:.2f} sec")


    print("\n[2/2] Python - Call Asiatique")
    start = time.time()
    prix_asian = monte_carlo_asian_python(S, T, sigma, r, K, num_sim, num_day)
    print(f"Prix: {prix_asian:.5f} | Temps: {time.time() - start:.2f} sec")