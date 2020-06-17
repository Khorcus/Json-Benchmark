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

std::string filename_end = ".json";
std::vector<rapidjson::Document> rapidjson_docs(10);
std::vector<Json::Value> jsoncpp_values(10);
std::vector<nlohmann::json> nlohmann_jsons(10);


std::string i_to_test_filename(int i) {
    std::string test_filename_start = "../test-data/";
    return test_filename_start + std::to_string((i + 1) * 10) + filename_end;
}

std::string i_to_output_filename(int i) {
    std::string output_filename_start = "../output-data/";
    return output_filename_start + std::to_string((i + 1) * 10) + filename_end;
}


static void test_rapidjson_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ifstream ifs(i_to_test_filename(i));
        state.ResumeTiming();

        rapidjson::IStreamWrapper isw(ifs);
        rapidjson_docs[i].ParseStream(isw);

        state.PauseTiming();
        ifs.close();
        state.ResumeTiming();
    }
}

static void test_rapidjson_serialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ofstream ofs(i_to_output_filename(i));
        state.ResumeTiming();

        rapidjson::OStreamWrapper osw(ofs);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer_canada(osw);
        rapidjson_docs[i].Accept(writer_canada);

        state.PauseTiming();
        std::flush(ofs);
        ofs.close();
        state.ResumeTiming();
    }
}

static void test_jsoncpp_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ifstream ifs(i_to_test_filename(i));
        state.ResumeTiming();

        ifs >> jsoncpp_values[i];

        state.PauseTiming();
        ifs.close();
        state.ResumeTiming();
    }
}

static void test_jsoncpp_serialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ofstream ofs(i_to_output_filename(i));
        state.ResumeTiming();

        ofs << jsoncpp_values[i];

        state.PauseTiming();
        std::flush(ofs);
        ofs.close();
        state.ResumeTiming();
    }
}

static void test_nlohmann_json_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ifstream ifs(i_to_test_filename(i));
        state.ResumeTiming();

        ifs >> nlohmann_jsons[i];

        state.PauseTiming();
        ifs.close();
        state.ResumeTiming();
    }
}

static void test_nlohmann_json_serialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        state.PauseTiming();
        ofstream ofs(i_to_output_filename(i));
        state.ResumeTiming();

        ofs << nlohmann_jsons[i];

        state.PauseTiming();
        std::flush(ofs);
        ofs.close();
        state.ResumeTiming();
    }
}


BENCHMARK(test_rapidjson_deserialization)->DenseRange(0, 1, 1);

BENCHMARK(test_rapidjson_serialization)->DenseRange(0, 1, 1);

BENCHMARK(test_jsoncpp_deserialization)->DenseRange(0, 1, 1);

BENCHMARK(test_jsoncpp_serialization)->DenseRange(0, 1, 1);

BENCHMARK(test_nlohmann_json_deserialization)->DenseRange(0, 1, 1);

BENCHMARK(test_nlohmann_json_serialization)->DenseRange(0, 1, 1);


BENCHMARK_MAIN();