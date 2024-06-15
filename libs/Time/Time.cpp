#include "Time.hpp"

#include <chrono>
#include <print>


auto MeasureTime(std::function<void()> const & function, std::string_view const message) -> void
{
    auto const start = std::chrono::high_resolution_clock::now();
    function();
    auto const stop = std::chrono::high_resolution_clock::now();
    auto const difference_ms = duration_cast<std::chrono::nanoseconds>(stop - start);
    auto const time_ms = difference_ms.count() / static_cast<long double>(1e6);
    std::println("{}: {:.3f} ms", message, time_ms);
}
