// Copyright 2019 Sabitov Egor <q.st.stream@gmail.com>

#include <header.hpp>
#include <iostream>
#include <chrono>
#include <vector>


#define DUP_10(x)  x x x x x x x x x x
#define DUP_100(x) DUP_10(x) DUP_10(x) DUP_10(x) DUP_10(x) DUP_10(x) DUP_10(x)\
DUP_10(x) DUP_10(x) DUP_10(x) DUP_10(x)
#define DUP_1000(x) DUP_100(x) DUP_100(x) DUP_100(x) DUP_100(x) DUP_100(x)\
DUP_100(x) DUP_100(x) DUP_100(x) DUP_100(x) DUP_100(x)
#define DUP_10000(x) DUP_1000(x) DUP_1000(x) DUP_1000(x) DUP_1000(x)\
DUP_1000(x) DUP_1000(x) DUP_1000(x) DUP_1000(x) DUP_1000(x) DUP_1000(x)
#define DUP_100000(x) DUP_10000(x) DUP_10000(x) DUP_10000(x) DUP_10000(x)\
DUP_10000(x) DUP_10000(x) DUP_10000(x) DUP_10000(x) DUP_10000(x) DUP_10000(x)
#define Step 64

//Cash #1 = 128 Kb
//Cash #2 = 512 Kb
//Cash #3 = 4 Mb
//64kb<128<256<512<1024<2048<4096<6144kb
// 8 experiments

int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    //Прямой обход
    size_t chet1 = 0;
    std::cout << "investigation" << std::endl;
    std::cout << "    travel_order: Forward" << std::endl;
    std::cout << "    experiments:" << std::endl;
    for (size_t size = 65536; size <= 4096 * 2 * 1024; size *= 2) {
        char *array = new char[size]();
        size_t j = 0;
        for (; j < size / 64; j++) {
            array[j * 64] = (size + 1) * Step;
        }
        j -= Step;
        array[j] = 0;
        size_t n = 0;
        size_t t = 0;
        start = std::chrono::system_clock::now();
        while (n < 1000) {
            DUP_100000(t = array[t];)
            n++;
        }
        end = std::chrono::system_clock::now();
        auto time = end - start;
        delete[] array;
        chet1++;
        std::cout << "    - experiment:" << std::endl;
        std::cout << "          number:" << chet1 << std::endl;
        std::cout << "          buffer_size:" << size / 1024;
        std::cout << "Kb" << std::endl;
        std::cout << "          duration:" << time.count() / 10000.;
        std::cout << "ns" << std::endl;
    }
    std::cout << std::endl << std::endl;
    // Обратный обход
    size_t chet2 = 0;
    std::cout << "investigation" << std::endl;
    std::cout << "    travel_order: Reverse" << std::endl;
    std::cout << "    experiments:" << std::endl;
    for (size_t size = 65536; size <= 4096 * 2 * 1024; size *= 2) {
        char *array = new char[size]();
        int j = size - 1;
        for (; j >= 0; j -= Step) {
            array[j] = j - Step;
        }
        j += Step;
        array[j] = size - 1;
        size_t n = 0;
        size_t t = 0;
        start = std::chrono::system_clock::now();
        while (n < 1000) {
            DUP_100000(t = array[t];)
            n++;
        }
        end = std::chrono::system_clock::now();
        auto time = end - start;
        delete[] array;
        chet2++;
        std::cout << "    - experiment:" << std::endl;
        std::cout << "          number:" << chet2 << std::endl;
        std::cout << "          buffer_size:" << size / 1024;
        std::cout<< "Kb"<< std::endl;
        std::cout << "          duration:" << time.count() / 10000.;
        std::cout << "ns" << std::endl;
    }
    std::cout << std::endl << std::endl;
    //Рандомный обход
    size_t chet3 = 0;
    std::cout << "investigation" << std::endl;
    std::cout << "    travel_order: Random" << std::endl;
    std::cout << "    experiments:" << std::endl;
    for (size_t size = 65536 / 4; size <= 4096 * 2 * 1024 / 4; size *= 2) {
        int size_s = size / Step;
        int *array = new int[size]();
        std::vector<int> buf(size_s);
        for (int i = 0; i < size / Step; i++)
            buf[i] = i * Step;
        int k = 0;
        while (size_s > 0) {
            srand(time(NULL));
            unsigned int t = clock();
            int num = (rand_r(&t) % size_s);
            array[k] = buf[num];
            size_s--;
            for (size_t m = num; m < static_cast<size_t>(size_s); m++)
                buf[m] = buf[m + 1];
            buf.resize(size_s);
            k += Step;
        }
        size_t n = 0;
        size_t t = 0;
        start = std::chrono::system_clock::now();
        while (n < 1000) {
            DUP_100000(t = array[t];)
            n++;
        }
        end = std::chrono::system_clock::now();
        auto time = end - start;
        delete[] array;
        chet3++;
        std::cout << "    - experiment:" << std::endl;
        std::cout << "          number:" << chet3 << std::endl;
        std::cout << "          buffer_size:" << size * 4 / 1024;
        std::cout<< "Kb" << std::endl;
        std::cout << "          duration:" << time.count() / 10000.;
        std::cout<< "ns" << std::endl;
    }
    return 0;
}
