#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>

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



class myclass{
    public:
        int s = 7;
        *a = new int[s];
        std::vector v;

        myclass() = default;
	~myclass() = default;
		
        myclass(myclass&& Object) noexcept {
            LogDuration ld("move");
            a = std::move(Object.a);
            s = std::move(Object.s);
            v = std::move(Object.v);
        };

        myclass& operator=(const myclass&& object){
            LogDuration ld("move operator:");
            a = std::move(Object.a);
            s = std::move(Object.s);
            v = std::move(Object.v);
            return *this;
        };

         myclass(const myclass &object){
            LogDuration ld("copy:");
            s = std::copy(object.s);
            a = std::copy(object.a);
            v = std::copy(object.v);
        };

        myclass operator=(const myclass& object){
            LogDuration ld("copy operator:");
            s = std::copy(object.s);
            a = std::copy(object.a);
            v = std::copy(object.v);
            return *this;
        };

};


int main(){
    myclass cl;
    std::vector<int> v = {13, 51, 126}
    cl.v = v;



    return 0;
};
