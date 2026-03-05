#include <iostream>
#include <chrono>
#include <random>


int data[1000000] = {};


//заполнение (time(0) - время с 00:00 01.01.1970, используется как сид (биг брейн тайм))
void rand_data_unsorted(int N) {
    std::default_random_engine rng((int)time(0));
    std::uniform_int_distribution<unsigned>dstr(0, N - 1);
    for (int i = 0; i < N; ++i) {
        data[i] = dstr(rng);
    }
}
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

//поиски
bool lin_search(int start, int end, int target){ 
    int N = end - start + 1;
    for (int i = 0; i < N; ++i) {
        if (data[i] == target) {
            return true;
        }
    }
    return false;
}
bool bin_search(int start, int end, int target){ 
    int N = end - start + 1;
    while (end >= start) {
        N = end - start + 1;
        int mid = start + N/2;
        if (data[mid] == target) {
            return true;
        }
        else if (data[mid] > target){
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }
    return false;
}



//подсчет времени выполнения функции repeat раз
float count_time(bool(search)(int start, int end, int target), int N, int target) {
    long long repeat = 100;
    auto begin = std::chrono::steady_clock::now();
    for (int j = 0; j < repeat; ++j) {
        search(0, N - 1, target);
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    return ((time_span.count() + 0.0)/repeat);
}



//поиск по N = 10^... для target = -1 - не в массиве: смысла генерить 50 раз нету
void worst_case(void(rand_data)(int N), bool(*search)(int start, int end, int target)){
    std::cout << "WORST CASE SCENARIO\n";

    for (int N = 100; N <= 1000000; N*=10) {
        rand_data(N);
        std::cout << N << ' ' << count_time(search, N, -1) << '\n';
    }
    std::cout << '\n';
}

//поиск для случ target из массива
void avg_case(void(rand_data)(int N), bool(*search)(int start, int end, int target)){
    std::cout << "AVG CASE SCENARIO\n";

    srand((int)time(0));
    int iter = 100;

    for (int N = 100; N <= 1000000; N*=10) { //  берем все нужные длины N
        float s = 0;
        for (int u = 0; u < iter; ++u) { //      и прогоняем их по iter раз для разных r = target
            int r = rand() % N; //чтоб уместить в [0, N-1]
            rand_data(N);
            s += count_time(search, N, r);
        }
        std::cout << N << ' ' << s/(iter + 0.0) << '\n';
    }
    std::cout << '\n';
}
        



int main() {
    worst_case(rand_data_unsorted, lin_search); // худший лин
    avg_case(rand_data_unsorted, lin_search); // средний лин
    worst_case(rand_data_sorted, bin_search); // худший бин
    avg_case(rand_data_sorted, bin_search); // средний бин

    return 0;
}
