#include <Graph.hpp>
#include <Time.hpp>

#include <limits>
#include <format>
#include <print>
#include <CL/opencl.hpp>

#include <OpenCLHelpers.hpp>


#define STORAGE    (TEST_SIZE * TEST_SIZE * sizeof(float))

auto main() -> int
{
    Graph<GRAPH_TYPE> graph{TEST_SIZE};
    graph.Randomize();

    Graph<GRAPH_TYPE> result{TEST_SIZE};

    auto const context = GetContext();
    auto const program = GetProgram(context, "../OpenCLSwapped/shortcut.cl");

    cl::Buffer bufferDst{context, CL_MEM_READ_WRITE, STORAGE};
    cl::Buffer bufferSrc{context, CL_MEM_WRITE_ONLY, STORAGE};

    cl::CommandQueue queue{context};

    MeasureTime(
        [&] -> void
        {
            cl::copy(queue, graph.data().cbegin(), graph.data().cend(), bufferSrc);
        }, "Time taken to load data"
    );

    cl::KernelFunctor<cl::Buffer, cl::Buffer, unsigned const> kernel{program, "shortcut"};
    cl::EnqueueArgs const args{queue, cl::NDRange{TEST_SIZE, TEST_SIZE}};

    MeasureTime(
        [&] -> void
        {
            kernel(args, bufferDst, bufferSrc, TEST_SIZE);
            queue.finish();
        }, std::format("OpenCL Swapped with size {}", TEST_SIZE)
    );

    MeasureTime(
        [&]
        {
            cl::copy(queue, bufferDst, result.data().begin(), result.data().end());
        }, "Time taken to unload data"
    );

    std::println("Checksum: {}", result.Checksum());

    return 0;
}
