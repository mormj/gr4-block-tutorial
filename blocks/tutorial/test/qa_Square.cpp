#include <boost/ut.hpp>

#include <gnuradio-4.0/tutorial/Square.hpp>
using namespace gr::tutorial;
using namespace boost::ut;

const suite SquareTests = [] {
    "Simple Test"_test = [] {
        auto blk = Square<float>(gr::property_map{
            {"offset", "3.0"},
        });

        float value = 483732.9227;
        float expected = value * value + pow(10.0,3.0/10.0);
        expect(eq(blk.processOne(value), expected)); 
    };

};

int main() { return boost::ut::cfg<boost::ut::override>.run(); }