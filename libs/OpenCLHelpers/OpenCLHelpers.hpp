#pragma once

#include <CL/opencl.hpp>


auto GetContext() -> cl::Context;

auto GetProgram(cl::Context const & context, std::string_view const filename) -> cl::Program;