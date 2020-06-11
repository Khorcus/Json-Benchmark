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

rapidjson::Document document_canada;

void test_rapidjson_serialization();

void test_rapidjson_deserialization();

void test_rapidjson_deserialization_canada();

void test_rapidjson_serialization_canada();

void test_jsoncpp();

void test_nlohmann_json();

static void BM_rapidjson(benchmark::State &state) {
    for (auto _ : state)
        test_rapidjson_serialization();
}

static void BM_jsoncpp(benchmark::State &state) {
    for (auto _ : state)
        test_jsoncpp();
}

static void BM_test_rapidjson_deserialization_canada(benchmark::State &state) {
    for (auto _ : state)
        test_rapidjson_deserialization_canada();
}

static void BM_test_rapidjson_serialization_canada(benchmark::State &state) {
    for (auto _ : state)
        test_rapidjson_serialization_canada();
}

static void test_rapidjson_serialization(benchmark::State &state) {
    if (document_canada.Null()) {
        return;
    }
    int size = state.range(0);
    for (auto _ : state) {
        ofstream ofs_canada("../test-data/canada-rapidjson-output.json");
        rapidjson::OStreamWrapper osw_canada(ofs_canada);
        rapidjson::Writer<rapidjson::OStreamWrapper> writer_canada(osw_canada);
        document_canada.Accept(writer_canada);
    }
}

int main(int argc, char *argv[]) {
    BENCHMARK(BM_test_rapidjson_deserialization_canada);
    BENCHMARK(BM_test_rapidjson_serialization_canada);
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) {
        return 1;
    }
    ::benchmark::RunSpecifiedBenchmarks();
}

void test_rapidjson_deserialization_canada() {
    ifstream ifs_canada("../test-data/canada.json");
    rapidjson::IStreamWrapper isw_canada(ifs_canada);
    document_canada.ParseStream(isw_canada);
}

void test_rapidjson_serialization_canada() {
    ofstream ofs_canada("../test-data/canada-rapidjson-output.json");
    rapidjson::OStreamWrapper osw_canada(ofs_canada);
    rapidjson::Writer<rapidjson::OStreamWrapper> writer_canada(osw_canada);
    document_canada.Accept(writer_canada);
}

void test_rapidjson_serialization() {
    using rapidjson::IStreamWrapper;
    using rapidjson::OStreamWrapper;
    using rapidjson::Document;
    using rapidjson::Writer;

    ifstream ifs_canada("../test-data/canada.json");
    IStreamWrapper isw_canada(ifs_canada);

    Document document_canada;
    document_canada.ParseStream(isw_canada);

    ofstream ofs_canada("../test-data/canada-rapidjson-output.json");
    OStreamWrapper osw_canada(ofs_canada);

    Writer<OStreamWrapper> writer_canada(osw_canada);
    document_canada.Accept(writer_canada);


//    ifstream ifs_large_file("../test-data/large-file.json");
//    IStreamWrapper isw_large_file(ifs_large_file);
//
//    Document document_large_file;
//    document_canada.ParseStream(isw_large_file);
//
//    ofstream ofs_large_file("../test-data/large-file-rapidjson-output.json");
//    OStreamWrapper osw_large_file(ofs_large_file);
//
//    Writer<OStreamWrapper> writer_large_file(osw_large_file);
//    document_canada.Accept(writer_large_file);


    ifstream ifs_citylots("../test-data/citylots.json");
    IStreamWrapper isw_citylots(ifs_citylots);

    Document document_citylots;
    document_citylots.ParseStream(isw_citylots);

    ofstream ofs_citylots("../test-data/citylots-rapidjson-output.json");
    OStreamWrapper osw_citylots(ofs_citylots);

    Writer<OStreamWrapper> writer_citylots(osw_citylots);
    document_citylots.Accept(writer_citylots);
}

void test_jsoncpp() {
    using Json::Value;

    ifstream ifs_canada("../test-data/canada.json");
    Json::Value value_canada;
    ifs_canada >> value_canada;

    ofstream ofs_canada("../test-data/canada-jsoncpp-output.json");
    ofs_canada << value_canada;


    ifstream ifs_citylots("../test-data/citylots.json");
    Json::Value value_citylots;
    ifs_citylots >> value_citylots;

    ofstream ofs_citylots("../test-data/citylots-jsoncpp-output.json");
    ofs_citylots << value_citylots;


//    ifstream ifs_large_file("../test-data/large-file.json");
//    Json::Value value_large_file;
//    ifs_canada >> value_large_file;
//
//    ofstream ofs_large_file("../test-data/large-file-jsoncpp-output.json");
//    ofs_large_file << value_large_file;
}

void test_nlohmann_json() {
    using nlohmann::json;

    ifstream ifs_canada("../test-data/canada.json");
    json json_canada;
    ifs_canada >> json_canada;

    ofstream ofs_canada("../test-data/canada-nlochmann-output.json");
    ofs_canada << json_canada;


    ifstream ifs_citylots("../test-data/citylots.json");
    json json_citylots;
    ifs_citylots >> json_citylots;

    ofstream ofs_citylots("../test-data/citylots-nlochmann-output.json");
    ofs_citylots << json_citylots;

//    ifstream ifs_large_file("../test-data/large-file.json");
//    json json_large_file;
//    ifs_canada >> json_large_file;
//
//    ofstream ofs_large_file("../test-data/large-file-nlochmann-output.json");
//    ofs_large_file << json_large_file;
}