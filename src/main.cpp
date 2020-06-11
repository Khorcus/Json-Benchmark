#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>
#include <json/json.h>
#include <nlohmann/json.hpp>
#include <benchmark/benchmark.h>
#include <fstream>


using std::ifstream;
using std::ofstream;

std::string test_filename_start = "../test-data/";
std::string output_filename_start = "../output-data/";
std::string filename_end = ".json";
std::vector<rapidjson::Document> rapidjson_docs(10);


std::string i_to_size_str(int i) {
    return std::to_string((i + 1) * 10);
}


static void test_rapidjson_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        ifstream ifs(test_filename_start + i_to_size_str(i) + filename_end);
        rapidjson::IStreamWrapper isw(ifs);
        rapidjson_docs[i].ParseStream(isw);
    }
}

static void test_rapidjson_serialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        ofstream ofs(output_filename_start + i_to_size_str(i) + filename_end);
        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer_canada(osw);
        rapidjson_docs[i].Accept(writer_canada);
    }
}


BENCHMARK(test_rapidjson_deserialization)->DenseRange(0, 9, 1);

BENCHMARK(test_rapidjson_serialization)->DenseRange(0, 9, 1);


BENCHMARK_MAIN();