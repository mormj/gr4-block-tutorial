#include <complex>
#include <cstdint>
#include <cstdlib>

#include <gnuradio-4.0/Graph.hpp>
#include <gnuradio-4.0/Scheduler.hpp>
#include <gnuradio-4.0/PluginLoader.hpp>
#include <gnuradio-4.0/tutorial/Square.hpp>
#include <gnuradio-4.0/zeromq/ZmqPushSink.hpp>
#include <gnuradio-4.0/zeromq/ZmqPullSource.hpp>

#include <gnuradio-4.0/BlockRegistry.hpp>

#include <print>

using namespace gr;
using namespace gr::tutorial;

int main() {

 
    using T = float;

    gr::Graph fg;
    auto&     source1 = fg.emplaceBlock<gr::zeromq::ZmqPullSource<T>>({
        {"endpoint", "tcp://localhost:5555"},
        {"timeout", 10},
        {"bind", false},
    });

    auto&     source2 = fg.emplaceBlock<gr::zeromq::ZmqPullSource<T>>({
        {"endpoint", "tcp://localhost:5556"},
        {"timeout", 10},
        {"bind", false},
    });

    auto&     source3 = fg.emplaceBlock<gr::zeromq::ZmqPullSource<T>>({
        {"endpoint", "tcp://localhost:5557"},
        {"timeout", 10},
        {"bind", false},
    });

    auto& sink = fg.emplaceBlock<gr::zeromq::ZmqPushSink<pmtv::pmt>>({
        {"endpoint", "tcp://localhost:5558"},
        {"timeout", 100},
        {"bind", true},
    });

    auto& packetizerBlock = fg.emplaceBlock<Packetizer<T>>({
        {"n_inputs", 3},
        {"packet_size", 1024}
    });


    const char* connection_error = "connection_error";

    // if (fg.connect<"out">(source).to<"in">(sink) != gr::ConnectionResult::SUCCESS) {
    //     throw gr::exception(connection_error);
    // }
    if (fg.connect(source1, "out"s, packetizerBlock, "in#0"s) != gr::ConnectionResult::SUCCESS) {
        throw gr::exception(connection_error);
    }
    if (fg.connect(source2, "out"s, packetizerBlock, "in#1"s) != gr::ConnectionResult::SUCCESS) {
        throw gr::exception(connection_error);
    }
    if (fg.connect(source3, "out"s, packetizerBlock, "in#2"s) != gr::ConnectionResult::SUCCESS) {
        throw gr::exception(connection_error);
    }    


    if (fg.connect(packetizerBlock, "out"s, sink, "in"s) != gr::ConnectionResult::SUCCESS) {
        throw gr::exception(connection_error);
    }


    gr::scheduler::Simple<gr::scheduler::ExecutionPolicy::singleThreaded> sched{std::move(fg)};
    const auto                                                            ret = sched.runAndWait();
    if (!ret.has_value()) {
        std::print("scheduler error: {}", ret.error());
        std::exit(1);
    }

    return 0;
}
