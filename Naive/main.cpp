#include <Graph.hpp>
#include <Time.hpp>

#include <limits>
#include <format>

#if not defined(GRAPH_TYPE)
#define GRAPH_TYPE float
#endif

#if not defined(TEST_SIZE)
#define TEST_SIZE 1000
#endif


template<typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>;

auto main() -> int
{
    Graph<GRAPH_TYPE> graph{TEST_SIZE};

    MeasureTime([&] -> void
                {
                    auto const result = Shortcut(graph);
                }, std::format("Naive with size {}", TEST_SIZE));


    return 0;
}

template<typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>
{
    Graph<T> result{graph.size()};

    for (std::size_t i = 0; i < graph.size(); ++i)
    {
        for (std::size_t j = 0; j < graph.size(); ++j)
        {
            T minimum{0};

            if constexpr (std::numeric_limits<T>::has_infinity)
            {
                minimum = std::numeric_limits<T>::infinity();
            }
            else
            {
                minimum = std::numeric_limits<T>::max();
            }

            for (std::size_t k = 0; k < graph.size(); ++k)
            {
                minimum = std::min(minimum, graph[i, k] + graph[k, j]);
            }

            result[i, j] = minimum;
        }
    }

    return result;
}