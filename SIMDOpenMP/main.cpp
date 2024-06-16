#include <Graph.hpp>
#include <Time.hpp>

#include <format>
#include <limits>
#include <print>
#include <thread>

#include <omp.h>


#define NUM_THREADS     ( std::thread::hardware_concurrency() )


template <typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>;

[[gnu::const]] auto GetInfinity() -> Vector::type;

[[gnu::pure]] auto HorizontalMin(Vector::type const & vector) -> Vector::base_type;

[[gnu::pure]] auto ElementWiseMin(Vector::type const & lhs, Vector::type const & rhs) -> Vector::type;


static constexpr auto MAX = max_value<Vector::base_type>::get();


auto main() -> int
{
    Graph<GRAPH_TYPE> graph{TEST_SIZE};
    graph.Randomize();

    omp_set_num_threads(NUM_THREADS);

    Graph<GRAPH_TYPE> result;

    MeasureTime(
        [&] -> void
        {
            result = Shortcut(graph);
        }, std::format("SIMD OpenMP ({} threads) with size {}", NUM_THREADS, TEST_SIZE)
    );

    std::println("Checksum: {}", result.Checksum());

    return 0;
}

template <typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>
{
    Graph<T> result{graph.size()};

    Graph<Vector::type> vectors{graph.size()};
    Graph<Vector::type> transposed{graph.size()};

    #pragma omp parallel for default(none) shared(graph, vectors, transposed, MAX)
    for (std::size_t row = 0; row < graph.size(); ++row)
    {
        for (std::size_t vec = 0; vec < graph.sizeVec(); ++vec)
        {
            for (std::size_t vecElem = 0; vecElem < Vector::size::value; ++vecElem)
            {
                auto const idx = vec * Vector::size::value + vecElem;

                vectors[row, vec][vecElem] = idx < graph.size() ? graph[row, idx] : MAX;
                transposed[row, vec][vecElem] = idx < graph.size() ? graph[idx, row] : MAX;
            }
        }
    }

    #pragma omp parallel for default(none) shared(graph, vectors, transposed, result, MAX)
    for (std::size_t row = 0; row < graph.size(); ++row)
    {
        for (std::size_t col = 0; col < graph.size(); ++col)
        {
            auto minimum = GetInfinity();

            for (std::size_t k = 0; k < graph.sizeVec(); ++k)
            {
                minimum = ElementWiseMin(minimum, vectors[row, k] + transposed[col, k]);
            }

            result[row, col] = HorizontalMin(minimum);
        }
    }

    return result;
}

[[gnu::const]] auto GetInfinity() -> Vector::type
{
    Vector::type result;

    for (std::size_t idx = 0; idx < Vector::size::value; ++idx)
    {
        result[idx] = MAX;
    }

    return result;
}

[[gnu::pure]] auto HorizontalMin(Vector::type const & vector) -> Vector::base_type
{
    Vector::base_type result{MAX};

    for (std::size_t idx = 0; idx < Vector::size::value; ++idx)
    {
        result = std::min(result, vector[idx]);
    }

    return result;
}

[[gnu::pure]] auto ElementWiseMin(Vector::type const & lhs, Vector::type const & rhs) -> Vector::type
{
    return lhs < rhs ? lhs : rhs;
}
