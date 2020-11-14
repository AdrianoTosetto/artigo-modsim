#ifndef UTILS_H
#define UTILS_H

#include <random>

double uniformDistribution(double low, double high) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(low, high);

    return distr(gen);
}

#endif