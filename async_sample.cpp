#include <iostream>
#include <thread>

#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>

using namespace std;
using namespace stlab;

struct unit{};
auto say = [](string s){
    for(auto i = 0; i < 5; ++i){
        cout << s << "\n";
        this_thread::sleep_for(100ms);
    }
    return unit{};
};

int main() {
    auto f = async(default_executor, [] { return say("world"); });
    auto g = async(default_executor, [] { return say("hello"); });
    
    std::atomic_bool done{false};

    auto result = when_all(default_executor, 
                           [&done](auto a, auto b){ 
                               done.store(true); }, f, g);

    while(!done){};
}
