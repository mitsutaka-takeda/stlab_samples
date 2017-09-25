#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include <range/v3/view/slice.hpp>
#include <stlab/concurrency/channel.hpp>
#include <stlab/concurrency/default_executor.hpp>
#include <stlab/concurrency/future.hpp>

using namespace std;
using namespace stlab;
using namespace ranges::view;

auto sum = [](auto& send, auto const& ints){
    auto s = 0;
    for(auto i : ints){
        s += i;
    }
    send(s);
};

int main() {
    std::vector s{7, 2, 8, -9, 4, 0};

    auto [send0, receive0] = channel<int>(default_executor);
    auto [send1, receive1] = channel<int>(default_executor);

    auto f = async(default_executor, [s0 = send0, &s]{ sum(s0, s | slice(0ul, s.size()/2)); });
    auto g = async(default_executor, [s1 = send1, &s]{ sum(s1, s | slice(s.size()/2, s.size())); });

    std::atomic_bool done{ false };

    auto joined = join(default_executor,
                      [&done](int x, int y){ 
                          cout << x << " " << y << " " << x + y << "\n";
                          done = true;
                      },
                      receive0, receive1);
    receive0.set_ready();
    receive1.set_ready();

    while (!done) {}
}
