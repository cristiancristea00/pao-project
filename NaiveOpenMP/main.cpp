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
        }, std::format("Naive OpenMP ({} threads) with size {}", NUM_THREADS, TEST_SIZE)
    );

    std::println("Checksum: {}", result.Checksum());

    return 0;
}

template <typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>
{
    Graph<T> result{graph.size()};

    #pragma omp parallel for default(none) shared(graph, result)
    for (std::size_t row = 0; row < graph.size(); ++row)
    {
        for (std::size_t col = 0; col < graph.size(); ++col)
        {
            T minimum{max_value<T>::get()};

            for (std::size_t k = 0; k < graph.size(); ++k)
            {
                minimum = std::min(minimum, graph[row, k] + graph[k, col]);
            }

            result[row, col] = minimum;
        }
    }

    return result;
}
