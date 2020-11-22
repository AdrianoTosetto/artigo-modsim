#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <functional>
#include <random>
#include <vector>

double uniformDistribution(double low, double high) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(low, high);

    return distr(gen);
}
// TODO: chance vec to const&
template<typename T>
std::vector<T> filter(std::vector<T> vec, std::function<bool(const T& e)> f) {
    std::vector<T> ret;
    std::copy_if(vec.begin(), vec.end(), std::back_inserter(ret), f);

    return ret;
}

#endif