#pragma once

#include <gnuradio-4.0/Block.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>
#include <ranges>

namespace gr::tutorial {

template <typename T>
struct Square : Block<Square<T>> {

    using Description = Doc<"@brief Squares the input value">;

    PortIn<T> in{};
    PortOut<T> out{};

    Annotated<T, "offset", Doc<"additive offset">, Visible, Unit<"dB">>        offset = 0;

    T _offset_linear{T{0}};

    GR_MAKE_REFLECTABLE(Square, in, out, offset);

    // template<gr::meta::t_or_simd<T> V>
    // [[nodiscard]] constexpr V processOne(V input) const noexcept { return input*input + _offset_linear; }

    // [[nodiscard]] constexpr T processOne(T input) const noexcept { return input*input + _offset_linear; }


    [[nodiscard]] constexpr work::Status processBulk(std::span<const T> input, std::span<T> output) const noexcept {       
        std::ranges::transform(input, output.begin(), [&](T a){ return a*a + _offset_linear; });

        return work::Status::OK;
    }

    void settingsChanged(const gr::property_map& old_settings, const gr::property_map& new_settings) {
        if (new_settings.contains("offset") && old_settings.at("offset") != new_settings.at("offset")) {
            _offset_linear = pow(T{10},offset/T{10});
        }
    }


};



template <typename T>
struct Packetizer : Block<Packetizer<T>, Resampling<1024U, 1UZ, false>> {

    using Description = Doc<"@brief Packetize the input streams and perform some function">;

    std::vector<PortIn<T>> in;
    PortOut<pmtv::pmt> out;

    size_t n_inputs;
    size_t packet_size;

    GR_MAKE_REFLECTABLE(Packetizer, in, out, n_inputs, packet_size);

    void settingsChanged(const property_map& old_settings, const property_map& new_settings) noexcept {
        if (new_settings.contains("n_inputs") && old_settings.at("n_inputs") != new_settings.at("n_inputs")) {
            in.resize(n_inputs);
        }

        if (new_settings.contains("packet_size")) {
            this->input_chunk_size = packet_size;
        }
    }

    template<gr::InputSpanLike TInSpan>
    [[nodiscard]] constexpr work::Status processBulk(const std::span<TInSpan>& input, std::span<pmtv::pmt> output) const noexcept {       

        const size_t N = this->input_chunk_size;  // input_chunk_size defines the input to output ratio, i.e. the decimation ratio
        size_t num_chunks = output.size();

        for (size_t idx = 0; idx < num_chunks; ++idx) {
            std::vector<T> out_chunk(N);
            std::copy(input[0].begin()+ idx * N, input[0].begin()+ (idx+1) * N, out_chunk.begin());
            for (std::size_t n = 1; n < input.size(); n++) {
                std::transform(out_chunk.begin(), out_chunk.end(), input[n].begin()+ idx * N, out_chunk.begin(), 
                    [](T a, T b){
                        return a + b;
                    }
                );
            }
            
            output[idx] = pmtv::pmt(std::move(out_chunk));
        }
        return work::Status::OK;
    }



};

} // namespace gr::tutorial

GR_REGISTER_BLOCK(gr::tutorial::Square, [ float, short, std::complex<float> ])
GR_REGISTER_BLOCK(gr::tutorial::Packetizer, [ float, short, std::complex<float> ])