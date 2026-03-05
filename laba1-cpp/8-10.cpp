#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

int data[1000000] = {};
int c[1000000] = {};
int targets[1000] = {};

std::default_random_engine rng((unsigned)time(0));

void rand_data_unsorted(int N) {
    std::uniform_int_distribution<int> dstr(0, N - 1);
    for (int i = 0; i < N; ++i) {
        data[i] = dstr(rng);
    }
}

bool lin_search(int begin, int end, int target) {
    for (int i = begin; i <= end; ++i) {
        if (data[i] == target) return true;
    }
    return false;
}

void strat_A(int begin, int end, int target) {
    for (int i = begin; i <= end; ++i) {
        if (data[i] == target) {
            std::swap(data[begin], data[i]);
            break;
        }
    }
}

void strat_B(int begin, int end, int target) {
    for (int i = begin; i <= end; ++i) {
        if (data[i] == target) {
            if (i > begin) std::swap(data[i], data[i - 1]);
            break;
        }
    }
}

void strat_C(int begin, int end, int target) {
    for (int i = begin; i <= end; ++i) {
        if (data[i] == target) {
            c[i]++;
            if (i > begin and c[i] > c[i - 1]) {
                std::swap(data[i], data[i - 1]);
                std::swap(c[i], c[i - 1]);
            }
            break;
        }
    }
}

float count_time(int N) {
    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        lin_search(0, N - 1, targets[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    return (time_span.count() / 1000.0f) / 1000.0f;
}

void run(void (strategy)(int, int, int), bool is_smooth) {
    std::cout << (is_smooth ? "SMOOTH" : "NOT_SMOOTH") << std::endl;
    for (int N = 100; N <= 1000000; N *= 10) {
        std::fill(c, c + N, 0);
        rand_data_unsorted(N);

        std::uniform_int_distribution<int> d_smooth(0, N - 1);
        std::uniform_int_distribution<int> d_not_smooth(N / 2, N / 2 + 3);

        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 4; ++j) {
                int t = is_smooth ? d_smooth(rng) : d_not_smooth(rng);
                strategy(0, N - 1, t);
            }
        }

        for (int k = 0; k < 1000; ++k) {
            targets[k] = is_smooth ? d_smooth(rng) : d_not_smooth(rng);
        }

        std::cout << N << " " << count_time(N) << std::endl;
    }
}

int main() {
    std::cout << "STRATEGY_A" << std::endl;
    run(strat_A, true);
    run(strat_A, false);

    std::cout << "STRATEGY_B" << std::endl;
    run(strat_B, true);
    run(strat_B, false);

    std::cout << "STRATEGY_C" << std::endl;
    run(strat_C, true);
    run(strat_C, false);

    return 0;
}
