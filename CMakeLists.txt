cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(Json_Benchmark LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Rapidjson REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(benchmark REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${RAPIDJSOM_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${JSONCPP_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE ${NLOHMANN_JSON_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)