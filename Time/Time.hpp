#pragma once

#include <functional>
#include <string_view>


auto MeasureTime(std::function<void(void)> const & function, std::string_view const message) -> void;
