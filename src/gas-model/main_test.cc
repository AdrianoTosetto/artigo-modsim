#include <iostream>
#include <vector>
#include <type_traits>
#include "cellular_automata.h"

template<typename T>
constexpr bool check(...) {
    return false;
}

template<typename T>
constexpr bool check(typename T::test*) {
    return true;
}

template<typename T>
struct has_my_type {
    static constexpr bool value = check<T>(nullptr);
};

struct bolinha {
    typedef float myType;
    static void test();
};

class Cell {
 public:
    Cell* Clone() const {
        return nullptr;
    }
    static std::string getColorString() {
        return "000,000,000";
    }

    static std::string a() {
        return "000,000,000";
    }
};

int main(int argc, char const *argv[])
{
    CellularAutomaton<Cell> a(10,10);

    return 0;
}
