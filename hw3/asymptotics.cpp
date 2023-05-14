#include <iostream>
#include <stdlib.h>
#include <set>
#include <chrono>
#include <vector>
#include <algorithm>

class LogDuration {
public:
    LogDuration(std::string id)
        : id_(std::move(id)) {
    }

    ~LogDuration() {
        const auto end_time = std::chrono::steady_clock::now();
        const auto dur = end_time - start_time_;
        std::cout << id_ << ": ";
        std::cout << "operation time"
                  << ": " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count()
                  << " ms" << std::endl;
    }

private:
    const std::string id_;
    const std::chrono::steady_clock::time_point start_time_ = std::chrono::steady_clock::now();
};


void set(int N){
    LogDuration ld("Set time");
    std::set <int> cont_1;
    int j;

    for (j=0; j<N; j++){
        int random = std::rand();
        cont_1.insert(random);
    };
};

void vector(int N){
    LogDuration ld("vector time");
    std::vector <int> cont_1(N);
    int i;
    for (i=0; i<N; i++){
        int random = std::rand();
        cont_1[i] = random;
    };
    std::sort(cont_1.begin(), cont_1.end());
};

void array(int N){
    LogDuration ld("array time");
    int cont_1[N];
    int i;
    for (i=0; i<N; i++){
        int random = std::rand();
        cont_1[i] = random;
    };
    std::sort(cont_1, cont_1 + N);
};



int main(){
    
    int N = 10000;
    std::cout << "Comparison for N =" << N << std::endl;
    set(N);
    array(N);
    vector(N);
    };
