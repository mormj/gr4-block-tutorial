#pragma once

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>


namespace gr::tutorial {

template <typename T>
struct Square : Block<Square<T>> {

    using Description = Doc<"@brief Squares the input value">;

    PortIn<T> in;
    PortOut<T> out;

    GR_MAKE_REFLECTABLE(Square, in, out);

    [[nodiscard]] constexpr T processOne(T input) const noexcept { return input*input; }
};

} // namespace gr::tutorial

GR_REGISTER_BLOCK(gr::tutorial::Square, [ float, short, std::complex<float> ])