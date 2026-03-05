#include <iostream>
#include <chrono>
#include <random>

int data[1000000] = {};

void rand_data_sorted(int N) {
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, 10);
    
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            data[i] = dstr(rng);
        }
        else{
            data[i] = data[i - 1] + dstr(rng);
        }
    }
}
void rand_data_unsorted(int N) {
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, N - 1);
    
    for (int i = 0; i < N; ++i) {
        data[i] = dstr(rng);
    }
}


bool n_squared(int begin, int end, int target){
    for (int i = 0; i < end+1; ++i) {
        for (int j = 0; j < end+1; ++j) {
            if (data[i] + data[j] == target){
                return true;
            }
        }
    }
    return false;
}

//сравниваем сумму первого и последнего элементов с нужной, если искомая больше, двигаем
//второй (увеличиваем сумму), иначе последний (уменьшаем ее)
bool two_pointers_alg(int begin, int end, int target){
    int sum;
    while (begin != end){
        sum = data[begin] + data[end];
        if (sum < target){
            begin += 1;
        }
        else if (sum > target){
            end -= 1;
        }
        else{
            return true;
        }
    }
    return false;
}



float count_time(bool(search)(int begin, int end, int target), int N, int target) {
    long long repeat = 100000;
    auto begin = std::chrono::steady_clock::now();
    for (int j = 0; j < repeat; ++j) {
        search(0, N - 1, target);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return ((time_span.count() + 0.0)/repeat);
}


void worst_case(void(rand_data)(int N), bool(search)(int begin, int end, int target)){
    std::cout << "WCS\n";
    for (int N = 5; N <= 100; N+=5) {
        rand_data(N);
        std::cout << N << ' ' << count_time(search, N, -1) << '\n';
    }
    std::cout << '\n';
}

void avg_case(void(rand_data)(int N), bool(search)(int begin, int end, int target)){
    std::cout << "ACS\n";

    srand((int)time(0));
    int iter = 10;

    for (int N = 5; N <= 100; N+=5) {
        float s = 0;
        for (int j = 0; j < iter; ++j) {
            int r = rand() % N;
            rand_data(N);
            s += count_time(search, N, r);
        }
        std::cout << N << ' ' << s/(iter + 0.0) << '\n';
    }
    std::cout << '\n';
}

int main(){
    worst_case(rand_data_unsorted, n_squared);
    avg_case(rand_data_unsorted, n_squared);
    worst_case(rand_data_sorted, two_pointers_alg);
    avg_case(rand_data_sorted, two_pointers_alg);
    
    
    
    return 0;
}
