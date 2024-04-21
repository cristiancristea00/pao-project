#include "Graph.hpp"

#include <random>
#include <iostream>


template
class Graph<GRAPH_TYPE>;

template
class Graph<Vector::type>;


template<typename T, typename VECTOR>
Graph<T, VECTOR>::Graph(std::size_t const size) noexcept : numVectors{(size + Vector::size::value - 1) / Vector::size::value}
{
    matrix.resize(size);

    if constexpr (std::is_scalar<T>::value)
    {
        for (auto & item: matrix)
        {
            item.resize(size);
        }
    }
    else
    {
        for (auto & item: matrix)
        {
            item.resize(numVectors);
        }
    }
}

template<typename T, typename VECTOR>
auto Graph<T, VECTOR>::Randomize() noexcept -> void
{
    std::mt19937 randomEngine{SEED};

    if constexpr (std::is_scalar<T>::value)
    {

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
    else // We have a vector
    {
        if constexpr (std::is_floating_point<VECTOR>::value)
        {
            std::uniform_real_distribution<VECTOR> randomDistribution{0, 1};

            for (auto & row: matrix)
            {
                for (auto & item: row)
                {
                    for (std::size_t idx = 0; idx < Vector::size::value; ++idx)
                    {
                        item[idx] = randomDistribution(randomEngine);
                    }
                }
            }
        }
        else
        {
            std::uniform_int_distribution<VECTOR> randomDistribution{0, std::numeric_limits<VECTOR>::max()};

            for (auto & row: matrix)
            {
                for (auto & item: row)
                {
                    for (std::size_t idx = 0; idx < Vector::size::value; ++idx)
                    {
                        item[idx] = randomDistribution(randomEngine);
                    }
                }
            }
        }
    }
}

template<typename T, typename VECTOR>
Graph<T, VECTOR>::Graph(std::initializer_list<std::initializer_list<T>> const & init) noexcept : numVectors{(init.size() + Vector::size::value - 1) / Vector::size::value}
{
    matrix.reserve(init.size());

    for (auto const & list: init)
    {
        matrix.emplace_back(list);
    }
}
