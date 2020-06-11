find_path(JSONCPP_INCLUDE_DIR "json/json.h"
        PATH_SUFFIXES "jsoncpp"
        DOC "Specify the JsonCpp include directory here")

find_library(JSONCPP_LIBRARY
        NAMES jsoncpp
        PATHS
        DOC "Specify the JsonCpp library here")

set(JSONCPP_INCLUDE_DIRS ${JSONCPP_INCLUDE_DIR})
set(JSONCPP_LIBRARIES "${JSONCPP_LIBRARY}")
set(_JsonCpp_version_args)

if (EXISTS "${JSONCPP_INCLUDE_DIR}/json/version.h")
    file(STRINGS "${JSONCPP_INCLUDE_DIR}/json/version.h" _JsonCpp_version_contents REGEX "JSONCPP_VERSION_[A-Z]+")
    foreach (_JsonCpp_version_part MAJOR MINOR PATCH)
        string(REGEX REPLACE ".*# *define +JSONCPP_VERSION_${_JsonCpp_version_part} +([0-9]+).*" "\\1" JSONCPP_VERSION_${_JsonCpp_version_part} "${_JsonCpp_version_contents}")
    endforeach ()

    set(JSONCPP_VERSION_STRING "${JSONCPP_VERSION_MAJOR}.${JSONCPP_VERSION_MINOR}.${JSONCPP_VERSION_PATCH}")
    set(_JsonCpp_version_args VERSION_VAR JSONCPP_VERSION_STRING)
endif ()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(JSONCPP
        REQUIRED_VARS JSONCPP_LIBRARIES JSONCPP_INCLUDE_DIRS
        ${_JsonCpp_version_args})

if (JSONCPP_FOUND AND NOT TARGET jsoncpp::jsoncpp)

    add_library(jsoncpp::jsoncpp UNKNOWN IMPORTED)
    set_target_properties(jsoncpp::jsoncpp PROPERTIES
            IMPORTED_LOCATION “${JSONCPP_LIBRARY}”
            IMPORTED_LINK_INTERFACE_LANGUAGES “CXX”
            IMPORTED_INCLUDE_DIRECTORIES "${JSONCPP_INCLUDE_DIRS}")

endif ()



mark_as_advanced(JSONCPP_INCLUDE_DIR JSONCPP_LIBRARY)
