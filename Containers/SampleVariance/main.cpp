#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using vector_d = std::vector<double>;

static double simpleVariance(const vector_d& vec)
{
    const decltype(vec.size()) n = vec.size();
    if (n < 2) return 0.0;

    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
    const double average = sum / n;

    double sqSum = 0.0;
    for (double x : vec)
    {
        sqSum += (x - average) * (x - average);
    }

    return sqSum / (n - 1);
}

// Standard deviation of the sample.
static double standardDevSample(const vector_d vec)
{
    return sqrt(simpleVariance(vec));
}

int main()
{
    vector_d vec = { 3, 5, 3, 7, 8, 1, 1, 1 };
    std::cout << simpleVariance(vec) << "\n";
    std::cout << standardDevSample(vec) << "\n";

    return 0;
}