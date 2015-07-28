#include <iostream>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char** argv) {
    vector<int> v1;

    const size_t N = 100000000;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (size_t i = 0; i < N; i++)
        v2.push_back(i);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    return 0;
}
