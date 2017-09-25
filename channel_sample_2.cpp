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

auto sum = [](auto const& ints){
    auto s = 0;
    for(auto i : ints){
        s += i;
    }

    return s;
};

int main() {
    std::vector s{7, 2, 8, -9, 4, 0};
    using range_t = decltype(s | slice(0, 11));
    auto [send0, receive0] = channel<range_t>(default_executor);
    auto [send1, receive1] = channel<range_t>(default_executor);

    std::atomic_bool done{ false };

    auto f = async(default_executor, [s0 = send0, &s]{ s0(s | slice(0, 3)); });
    auto g = async(default_executor, [s1 = send1, &s]{ s1(s | slice(3, 6)); });
    auto joined = join(default_executor,
                      [&done](int x, int y){ 
                          cout << x << " " << y << " " << x + y << "\n";
                          done = true;
                      },
                       receive0 | sum,
                       receive1 | sum);
    receive0.set_ready();
    receive1.set_ready();

    while (!done) {}
}
