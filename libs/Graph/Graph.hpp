#pragma once

#include <vector>


struct Vector
{
    using type = GRAPH_TYPE __attribute__((vector_size(32)));
    using base_type = GRAPH_TYPE;
    using size = std::integral_constant<std::size_t, sizeof(type) / sizeof(base_type)>;
};


template <typename T, typename VECTOR = Vector::base_type>
class Graph
{
public:
    Graph() noexcept = default;

    explicit Graph(std::size_t const size) noexcept;

    Graph(std::initializer_list<std::initializer_list<T>> const & init) noexcept;

    auto Randomize() noexcept -> void;

    auto Checksum() const noexcept -> T;

    [[nodiscard]] constexpr auto size() const noexcept -> std::size_t
    {
        return matrix.size();
    }

    [[nodiscard]] constexpr auto sizeVec() const noexcept -> std::size_t
    {
        return numVectors;
    }

    constexpr auto operator[](std::size_t const row, std::size_t const col) const noexcept -> T const &
    {
        return matrix[row][col];
    }

    constexpr auto operator[](std::size_t const row, std::size_t const col) noexcept -> T &
    {
        return matrix[row][col];
    }

private:
    std::vector<std::vector<T>> matrix;

    std::size_t numVectors{0};

    static constexpr std::size_t SEED{0xDEADBEEF42};
};
