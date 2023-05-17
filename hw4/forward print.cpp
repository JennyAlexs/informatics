#include <iostream>
#include <utility>

template<typename... Args>
void print(Args&&... args) {
    (std::cout << ... << std::forward<Args>(args)) << std::endl;
}

int main() {
    int n = 42;
    float k = 7.7;
    std::string t = "hi";
    
    print(n);               // int lvalue
    print(k);             // int rvalue
    print(t);               // std::string lvalue
    print(std::move(t));    // std::string rvalue
    
    return 0;
}
