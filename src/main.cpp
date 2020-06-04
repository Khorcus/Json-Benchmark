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

void test_rapidjson();

void test_jsoncpp();

void nlohmann_json();

static void BM_rapidjson(benchmark::State& state) {
    for (auto _ : state)
        nlohmann_json();
}

BENCHMARK(BM_rapidjson);
BENCHMARK_MAIN();

//int main(int argc, char *argv[]) {
//    test_rapidjson();
//    test_jsoncpp();
//    nlohmann_json();
//}

void test_rapidjson() {
    using rapidjson::IStreamWrapper;
    using rapidjson::OStreamWrapper;
    using rapidjson::Document;
    using rapidjson::Writer;

    ifstream ifs_canada("../data/canada.json");
    IStreamWrapper isw_canada(ifs_canada);

    Document document_canada;
    document_canada.ParseStream(isw_canada);

    ofstream ofs_canada("../data/canada-rapidjson-output.json");
    OStreamWrapper osw_canada(ofs_canada);

    Writer<OStreamWrapper> writer_canada(osw_canada);
    document_canada.Accept(writer_canada);


//    ifstream ifs_large_file("../data/large-file.json");
//    IStreamWrapper isw_large_file(ifs_large_file);
//
//    Document document_large_file;
//    document_canada.ParseStream(isw_large_file);
//
//    ofstream ofs_large_file("../data/large-file-rapidjson-output.json");
//    OStreamWrapper osw_large_file(ofs_large_file);
//
//    Writer<OStreamWrapper> writer_large_file(osw_large_file);
//    document_canada.Accept(writer_large_file);


    ifstream ifs_citylots("../data/citylots.json");
    IStreamWrapper isw_citylots(ifs_citylots);

    Document document_citylots;
    document_citylots.ParseStream(isw_citylots);

    ofstream ofs_citylots("../data/citylots-rapidjson-output.json");
    OStreamWrapper osw_citylots(ofs_citylots);

    Writer<OStreamWrapper> writer_citylots(osw_citylots);
    document_citylots.Accept(writer_citylots);
}

void test_jsoncpp() {
    using Json::Value;

    ifstream ifs_canada("../data/canada.json");
    Json::Value value_canada;
    ifs_canada >> value_canada;

    ofstream ofs_canada("../data/canada-jsoncpp-output.json");
    ofs_canada << value_canada;


    ifstream ifs_citylots("../data/citylots.json");
    Json::Value value_citylots;
    ifs_citylots >> value_citylots;

    ofstream ofs_citylots("../data/citylots-jsoncpp-output.json");
    ofs_citylots << value_citylots;


//    ifstream ifs_large_file("../data/large-file.json");
//    Json::Value value_large_file;
//    ifs_canada >> value_large_file;
//
//    ofstream ofs_large_file("../data/large-file-jsoncpp-output.json");
//    ofs_large_file << value_large_file;
}

void nlohmann_json() {
    using nlohmann::json;

    ifstream ifs_canada("../data/canada.json");
    json json_canada;
    ifs_canada >> json_canada;

    ofstream ofs_canada("../data/canada-nlochmann-output.json");
    ofs_canada << json_canada;


    ifstream ifs_citylots("../data/citylots.json");
    json json_citylots;
    ifs_citylots >> json_citylots;

    ofstream ofs_citylots("../data/citylots-nlochmann-output.json");
    ofs_citylots << json_citylots;

//    ifstream ifs_large_file("../data/large-file.json");
//    json json_large_file;
//    ifs_canada >> json_large_file;
//
//    ofstream ofs_large_file("../data/large-file-nlochmann-output.json");
//    ofs_large_file << json_large_file;
}