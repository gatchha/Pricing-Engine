# Pricing Engine

Moteur de calcul financier basé sur le modèle de Black-Scholes.

## Description
Ce projet implémente l'évaluation analytique d'options de type Call et le calcul des Greeks (Delta, Gamma, Vega) en C++.

## Structure du projet
- `src/` : Implémentation du moteur de calcul (`BlackScholes.cpp`, `Main.cpp`).
- `Include/` : Définitions et interfaces (`BlackScholes.h`).
- `CMakeLists.txt` : Configuration du système de build.

## Compilation et exécution
Le projet utilise CMake.
1. Charger le projet dans votre IDE (CLion recommandé).
2. Configurer le build via `CMakeLists.txt`.
3. Compiler et exécuter.

## Fonctionnalités
- Calcul du prix d'une option Call.
- Calcul des Greeks :
    - Delta ($\Delta$)
    - Gamma ($\Gamma$)
    - Vega ($\nu$)

## Dépendances
- C++20