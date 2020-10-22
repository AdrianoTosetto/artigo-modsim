#include "random.h"

double_t randomProbability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> distr(0, 1);

    return distr(gen);
}