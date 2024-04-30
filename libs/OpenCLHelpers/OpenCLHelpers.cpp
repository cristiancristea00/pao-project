#include "OpenCLHelpers.hpp"

#include <fstream>
#include <ranges>
#include <print>


auto GetContext() -> cl::Context
{
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);

    if (platforms.empty())
    {
        std::println(stderr, "No OpenCL platforms found. Check your OpenCL installation.");
        return EXIT_FAILURE;
    }

    std::println("Found {} OpenCL platform(s):", platforms.size());
    for (auto const & [index, platform] : std::views::enumerate(platforms))
    {
        std::println("Platform {}: {}", index, platform.getInfo<CL_PLATFORM_NAME>());
    }

    cl::Platform const platform = platforms.front();

    std::println("\nUsing platform: {}", platform.getInfo<CL_PLATFORM_NAME>());

    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

    if (devices.empty())
    {
        std::println(stderr, "No OpenCL devices found. Check your OpenCL installation.");
        return EXIT_FAILURE;
    }

    std::println("\nFound {} OpenCL device(s):", devices.size());
    for (auto const & [index, device] : std::views::enumerate(devices))
    {
        std::println("Device {}: {}", index, device.getInfo<CL_DEVICE_NAME>());
    }

    cl::Device const device = devices.front();
    std::println("\nUsing device: {}", device.getInfo<CL_DEVICE_NAME>());

    return cl::Context{device};
}

auto GetProgram(cl::Context const & context, std::string_view const filename) -> cl::Program
{
    std::ifstream file{filename.data()};

    using FileIterator = std::istreambuf_iterator<char>;
    std::string source{FileIterator{file}, FileIterator{}};

    cl::Program program{context, source};

    try
    {
        program.build();
    }
    catch (cl::Error const & error)
    {
        if (error.err() == CL_BUILD_PROGRAM_FAILURE)
        {
            std::println(stderr, "Build log:");
            std::println(stderr, "{}", program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(context.getInfo<CL_CONTEXT_DEVICES>().front()));
        }

        throw;
    }

    return program;
}
