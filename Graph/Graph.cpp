#include "Graph.hpp"

#include <random>


#if not defined(GRAPH_TYPE)
#define GRAPH_TYPE float
#endif


template
class Graph<GRAPH_TYPE>;


template<typename T>
Graph<T>::Graph(std::size_t const size) noexcept
{
    matrix.resize(size);

    for (auto & item: matrix)
    {
        item.resize(size);
    }

    std::mt19937 randomEngine{SEED};
    if constexpr (std::is_floating_point<T>::value)
    {
        std::uniform_real_distribution<T> randomDistribution{0, 1};

        for (auto & row: matrix)
        {
            for (auto & item: row)
            {
                item = randomDistribution(randomEngine);
            }
        }
    }
    else
    {
        std::uniform_int_distribution<T> randomDistribution{0, std::numeric_limits<T>::max()};

        for (auto & row: matrix)
        {
            for (auto & item: row)
            {
                item = randomDistribution(randomEngine);
            }
        }
    }
}

template<typename T>
Graph<T>::Graph(std::initializer_list<std::initializer_list<T>> const & init) noexcept
{
    matrix.reserve(init.size());

    for (auto const & list: init)
    {
        matrix.emplace_back(list);
    }
}

template<typename T>
auto Graph<T>::operator[](std::size_t const row, std::size_t const col) const noexcept -> T const &
{
    return matrix[row][col];
}

template<typename T>
auto Graph<T>::operator[](std::size_t const row, std::size_t const col) noexcept -> T &
{
    return matrix[row][col];
}
