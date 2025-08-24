#include <boost/ut.hpp>

#include <gnuradio-4.0/tutorial/Square.hpp>
#include <gnuradio-4.0/testing/TagMonitors.hpp>


#include <numeric>
#include <vector>

using namespace gr::tutorial;
using namespace boost::ut;

template <typename T>
bool almost_equal(const std::vector<T>& a,
                  const std::vector<T>& b,
                  T tol = static_cast<T>(1e-5)) {
    if (a.size() != b.size())
        return false;
    for (std::size_t i = 0; i < a.size(); ++i) {
        if (std::fabs(a[i] - b[i]) > tol)
            return false;
    }
    return true;
}

const suite SquareTests = [] {
    "Simple Test"_test = [] {
        auto blk = Square<float>(gr::property_map{
            {"offset", "3.0"},
        });

        float value = 483732.9227;
        float expected = value * value + pow(10.0,3.0/10.0);
        // expect(eq(blk.processOne(value), expected)); 

        std::vector<float> in_vals(1024);
        std::iota(in_vals.begin(), in_vals.end(), value);
        std::vector<float> expected_bulk(in_vals.size());
        std::vector<float> out_vals(in_vals.size());
        std::transform(in_vals.begin(), in_vals.end(), expected_bulk.begin(), [](float v){return v*v + pow(10.0,3.0/10.0);});

        blk.processBulk(in_vals, out_vals);
        expect(almost_equal(expected_bulk, out_vals)); 
    };

};

int main() { return boost::ut::cfg<boost::ut::override>.run(); }