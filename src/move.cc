#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

std::vector<double> sample_dist(std::mt19937& engine, double mean) {

    constexpr std::size_t n_samples = 10;
    
    std::normal_distribution<double> dist(mean);

    std::vector<double> ret(n_samples);
    for (auto& x : ret) x = dist(engine);
    
    return ret;

}

int main() {

    std::random_device device;
    std::mt19937 engine(device());
    
    for (auto x : {0.0, 5.0, 10.0}) {
        // Here's the magic.  This code would compile with a pre-C++11 compiler
        // too, but the call to sample_dist would be copying the data instead
        // of moving them.
        for (auto y : sample_dist(engine, x))
            std::cout << y << " " << std::endl;
        std::cout << std::endl;
    }

}
