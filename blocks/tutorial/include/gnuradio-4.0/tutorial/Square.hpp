#pragma once

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>


namespace gr::tutorial {

template <typename T>
struct Square : Block<Square<T>> {

    using Description = Doc<"@brief Squares the input value">;

    PortIn<T> in{};
    PortOut<T> out{};

    Annotated<T, "offset", Doc<"additive offset">, Visible, Unit<"dB">>        offset = 0;

    T _offset_linear{T{0}};

    GR_MAKE_REFLECTABLE(Square, in, out, offset);

    template<gr::meta::t_or_simd<T> V>
    [[nodiscard]] constexpr V processOne(V input) const noexcept { return input*input + _offset_linear; }

    void settingsChanged(const gr::property_map& old_settings, const gr::property_map& new_settings) {
        if (new_settings.contains("offset") && old_settings.at("offset") != new_settings.at("offset")) {
            _offset_linear = pow(T{10},offset/T{10});
        }
    }


};

} // namespace gr::tutorial

GR_REGISTER_BLOCK(gr::tutorial::Square, [ float, short, std::complex<float> ])