#include <Graph.hpp>
#include <Time.hpp>

#include <limits>
#include <format>
#include <print>


template <typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>;

auto main() -> int
{
    Graph<GRAPH_TYPE> graph{TEST_SIZE};
    graph.Randomize();

    Graph<GRAPH_TYPE> result;

    MeasureTime(
        [&] -> void
        {
            result = Shortcut(graph);
        }, std::format("Naive with size {}", TEST_SIZE)
    );

    std::println("Checksum: {}", result.Checksum());

    return 0;
}

template <typename T>
auto Shortcut(Graph<T> const & graph) -> Graph<T>
{
    Graph<T> result{graph.size()};

    for (std::size_t row = 0; row < graph.size(); ++row)
    {
        for (std::size_t col = 0; col < graph.size(); ++col)
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
                minimum = std::min(minimum, graph[row, k] + graph[k, col]);
            }

            result[row, col] = minimum;
        }
    }

    return result;
}
