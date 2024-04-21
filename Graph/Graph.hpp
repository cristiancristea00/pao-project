#pragma once

#include <cstdint>
#include <vector>


template<typename T>
class Graph
{
public:
    explicit Graph(std::size_t const size) noexcept;
    Graph(std::initializer_list<std::initializer_list<T>> const & init) noexcept;

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t { return matrix.size(); }

    auto operator[](std::size_t const row, std::size_t const col) const noexcept -> T const &;
    auto operator[](std::size_t const row, std::size_t const col) noexcept -> T &;
private:
    std::vector<std::vector<T>> matrix;

    static constexpr std::size_t SEED{0xDEADBEEF42};
};

