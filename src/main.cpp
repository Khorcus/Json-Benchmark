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

void rapidjson_deserialize(benchmark::State &state, int i, bool pause) {
    if (pause) {
        state.PauseTiming();
    }
    ifstream ifs(i_to_test_filename(i));
    rapidjson::IStreamWrapper isw(ifs);
    if (!rapidjson_docs[i].IsNull()) {
        rapidjson_docs[i] = rapidjson::Document();
    }
    if (pause) {
        state.ResumeTiming();
    }

    rapidjson_docs[i].ParseStream(isw);

    if (pause) {
        state.PauseTiming();
    }
    ifs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

void rapidjson_serialize(benchmark::State &state, int i, int pause) {
    if (pause) {
        state.PauseTiming();
    }
    ofstream ofs(i_to_output_filename(i));
    rapidjson::OStreamWrapper osw(ofs);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer(osw);
    if (pause) {
        state.ResumeTiming();
    }

    rapidjson_docs[i].Accept(writer);

    if (pause) {
        state.PauseTiming();
    }
    std::flush(ofs);
    ofs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

static void test_rapidjson_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        rapidjson_deserialize(state, i, true);
    }
}

static void test_rapidjson_serialization(benchmark::State &state) {
    int i = state.range(0);

    if (rapidjson_docs[i].IsNull()) {
        rapidjson_deserialize(state, i, false);
    }

    for (auto _ : state) {
        rapidjson_serialize(state, i, true);
    }
}

void jsoncpp_deserialize(benchmark::State &state, int i, bool pause) {
    if (pause) {
        state.PauseTiming();
    }
    ifstream ifs(i_to_test_filename(i));
    if (!jsoncpp_values[i].isNull()) {
        jsoncpp_values[i] = Json::Value();
    }
    if (pause) {
        state.ResumeTiming();
    }

    ifs >> jsoncpp_values[i];

    if (pause) {
        state.PauseTiming();
    }
    ifs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

void jsoncpp_serialize(benchmark::State &state, int i, bool pause) {
    if (pause) {
        state.PauseTiming();
    }
    ofstream ofs(i_to_output_filename(i));
    if (pause) {
        state.ResumeTiming();
    }

    ofs << jsoncpp_values[i];

    if (pause) {
        state.PauseTiming();
    }
    std::flush(ofs);
    ofs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

static void test_jsoncpp_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        jsoncpp_deserialize(state, i, true);
    }
}

static void test_jsoncpp_serialization(benchmark::State &state) {
    int i = state.range(0);

    if (jsoncpp_values[i].isNull()) {
        jsoncpp_deserialize(state, i, false);
    }

    for (auto _ : state) {
        jsoncpp_serialize(state, i, true);
    }
}

void nlohmann_json_deserialize(benchmark::State &state, int i, bool pause) {
    if (pause) {
        state.PauseTiming();
    }
    ifstream ifs(i_to_test_filename(i));
    if (!nlohmann_jsons[i].is_null()) {
        nlohmann_jsons[i] = nlohmann::json();
    }
    if (pause) {
        state.ResumeTiming();
    }

    ifs >> nlohmann_jsons[i];

    if (pause) {
        state.PauseTiming();
    }
    ifs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

void nlohmann_json_serialize(benchmark::State &state, int i, bool pause) {
    if (pause) {
        state.PauseTiming();
    }
    ofstream ofs(i_to_output_filename(i));
    if (pause) {
        state.ResumeTiming();
    }

    ofs << nlohmann_jsons[i];

    if (pause) {
        state.PauseTiming();
    }
    std::flush(ofs);
    ofs.close();
    if (pause) {
        state.ResumeTiming();
    }
}

static void test_nlohmann_json_deserialization(benchmark::State &state) {
    int i = state.range(0);
    for (auto _ : state) {
        nlohmann_json_deserialize(state, i, true);
    }
}

static void test_nlohmann_json_serialization(benchmark::State &state) {
    int i = state.range(0);

    if (nlohmann_jsons[i].is_null()) {
        nlohmann_json_deserialize(state, i, false);
    }

    for (auto _ : state) {
        nlohmann_json_serialize(state, i, true);
    }
}


BENCHMARK(test_rapidjson_deserialization)->DenseRange(0, 9, 1);

BENCHMARK(test_rapidjson_serialization)->DenseRange(0, 9, 1);

BENCHMARK(test_jsoncpp_deserialization)->DenseRange(0, 9, 1);

BENCHMARK(test_jsoncpp_serialization)->DenseRange(0, 9, 1);

BENCHMARK(test_nlohmann_json_deserialization)->DenseRange(0, 9, 1);

BENCHMARK(test_nlohmann_json_serialization)->DenseRange(0, 9, 1);


BENCHMARK_MAIN();