#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

std::vector<std::pair<int, int>> genOffsets(int radius) {
    std::vector<std::pair<int, int>> offsets;
    for (auto r = -radius; r <= radius; r++)
        offsets.push_back(std::make_pair(-radius, r));

    for (auto r = -(radius-1); r <= (radius-1); r++)
        offsets.push_back(std::make_pair(r, radius));

    for (auto r = radius; r >= -radius; r--)
        offsets.push_back(std::make_pair(radius, r));

    for (auto r = (radius-1); r >= -(radius-1); r--)
        offsets.push_back(std::make_pair(r, -radius));

    return offsets;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}


inline std::string genFileName(uint32_t timestamp) {
    std::string sbreakpoint = std::to_string(timestamp);
    sbreakpoint = 
        std::string(6 - sbreakpoint.length(), '0') + sbreakpoint;

    return "snapshot" + sbreakpoint;
}

template<typename ... Args>
std::string stringFormat( const std::string& format, Args ... args )
{
    size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1;
    if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[ size ] ); 
    snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 );
}

#endif