cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Json_Benchmark LANGUAGES CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(Rapidjson REQUIRED)
include_directories(${Rapidjson_INCLUDE_DIRS})

find_package(JsonCpp REQUIRED)
include_directories(${JsonCpp_INCLUDE_DIR})

find_package(nlohmann_json REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIR})

find_package(benchmark REQUIRED)
include_directories(${benchmark_INCLUDE_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${Rapidjson_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${JsonCpp_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${nlohmann_json_LIBRARY})
target_link_libraries(${PROJECT_NAME} benchmark::benchmark)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)