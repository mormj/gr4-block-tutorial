#pragma once

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>


namespace gr::tutorial {

struct Square : Block<Square> {

    using Description = Doc<"@brief Squares the input value">;

    PortIn<float> in;
    PortOut<float> out;

    GR_MAKE_REFLECTABLE(Square, in, out);

    [[nodiscard]] constexpr float processOne(float input) const noexcept { return input*input; }
};

} // namespace gr::tutorial

GR_REGISTER_BLOCK(gr::tutorial::Square, [ float, short, std::complex<float> ])