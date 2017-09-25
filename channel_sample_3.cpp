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

auto sum = [](auto c, auto const& ints){
    return [ints, c]{
        auto s = 0;
        for(auto i : ints){
            s += i;
        }

        c(s);
    };
};

auto go = [](auto f){
    return async(default_executor, f);
};

int main() {
    std::vector s{7, 2, 8, -9, 4, 0};

    auto [send0, receive0] = channel<int>(default_executor);
    auto [send1, receive1] = channel<int>(default_executor);

    std::atomic_bool done{ false };

    auto f = go(sum(send0, s | slice(0, 3)));
    auto g = go(sum(send1, s | slice(3, 6)));
    auto joined = join(default_executor,
                      [&done](int x, int y){ 
                          cout << x << " " << y << " " << x + y << "\n";
                          done = true;
                      },
                       receive0,
                       receive1);
    receive0.set_ready();
    receive1.set_ready();

    while (!done) {}
}
