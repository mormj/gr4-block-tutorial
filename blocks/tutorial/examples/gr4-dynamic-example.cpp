
#include <gnuradio-4.0/Graph.hpp>
#include <gnuradio-4.0/Scheduler.hpp>
#include <gnuradio-4.0/PluginLoader.hpp>
#include <gnuradio-4.0/BlockRegistry.hpp>
#include <gnuradio-4.0/testing/NullSources.hpp>
#include <gnuradio-4.0/basic/CommonBlocks.hpp>

#include <print>
#include <filesystem>

using namespace gr;

struct TestContext {
    explicit TestContext(std::vector<std::filesystem::path> paths) : loader(gr::globalBlockRegistry(), std::move(paths)) {}

    gr::PluginLoader loader;
};

template<typename T>
requires (std::is_arithmetic_v<T>)
class BSquare : public gr::Block<BSquare<T>> {
public:
  PortIn<T> in;
  PortOut<T> out;

   [[nodiscard]] constexpr T processOne(T inValue) {
    return inValue * inValue;
  }
};

int main() {
    std::vector<std::filesystem::path> paths;
  gr::Graph graph{};
  TestContext context(std::vector<std::filesystem::path>{ "/code/build/plugins" });

  for (const auto& plugin [[maybe_unused]] : context.loader.failedPlugins()) {
    //   std::cout << plugin->metadata.plugin_name << std::endl;
      std::cout << plugin.first << std::endl;
  }

//   gr::registerBlock<BSquare, float>(pluginContext.registry); // register a source defined block into the blocklib

//   auto &source = graph.emplaceBlock("BSquare", "double", {}, pluginContext.loader); // load builtin block
//   auto &block = graph.emplaceBlock("BlockFromSo", "double", {}, pluginContext.loader); // load from .so file

//   graph.connect(source, 0, block, 0);
//   gr::scheduler::Simple<> scheduler{std::move(graph)};
//   scheduler.runAndWait();

//   std::print("Dynamic Flowgraph processed samples!\n");
}