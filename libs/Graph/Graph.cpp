#include "Graph.hpp"

#include <iostream>
#include <random>


template
class Graph<GRAPH_TYPE>;

template
class Graph<Vector::type>;


template <typename T, typename VECTOR>
Graph<T, VECTOR>::Graph(std::size_t const size) noexcept : numElements{size}, numVectors{(size + Vector::size::value - 1) / Vector::size::value}
{
    matrix.resize(numElements * numElements);
}


template <typename T, typename VECTOR>
Graph<T, VECTOR>::Graph(std::initializer_list<std::initializer_list<T>> const & init) noexcept : numVectors{(init.size() + Vector::size::value - 1) / Vector::size::value}
{
    matrix.reserve(init.size());

    for (auto const & list : init)
    {
        matrix.insert(matrix.end(), list.begin(), list.end());
    }
}

template <typename T, typename VECTOR>
auto Graph<T, VECTOR>::Randomize() noexcept -> void
{
    std::mt19937 randomEngine{SEED};

    if constexpr (std::is_scalar<T>::value)
    {
        std::uniform_real_distribution<T> randomDistribution{0, 1};

        for (auto & elem : matrix)
        {
            elem = randomDistribution(randomEngine);
        }
    }
    else // We have a vector
    {
        std::uniform_real_distribution<VECTOR> randomDistribution{0, 1};

        for (auto & elem : matrix)
        {
            for (std::size_t idx = 0; idx < Vector::size::value; ++idx)
            {
                elem[idx] = randomDistribution(randomEngine);
            }
        }
    }
}

template <typename T, typename VECTOR>
auto Graph<T, VECTOR>::Checksum() const noexcept -> T
{
    return std::accumulate(matrix.begin(), matrix.end(), T{0});
}
