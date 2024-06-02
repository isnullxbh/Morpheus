find_package(Clang CONFIG REQUIRED)

add_library(Morpheus.Metadata)

set_target_properties(Morpheus.Metadata
    PROPERTIES
        OUTPUT_NAME "Morpheus.Metadata"
        PREFIX      "")

target_compile_features(Morpheus.Metadata
    PUBLIC
        cxx_std_20)

execute_process(
    COMMAND bash -c "${CMAKE_CXX_COMPILER} -x c++ -Wp,-v /dev/null 2>&1 > /dev/null | grep '^ /' | grep 'c++'"
    OUTPUT_VARIABLE MORPHEUS_SYS_HEADERS_RAW
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
string(REGEX REPLACE "[ \n\t]+" ";" MORPHEUS_SYS_HEADERS ${MORPHEUS_SYS_HEADERS_RAW})
message(STATUS "XXX=${MORPHEUS_SYS_HEADERS}")
#target_compile_definitions(Morpheus.Metadata
#    PUBLIC
#        MORPHEUS_SYS_HEADERS=${MORPHEUS_SYS_HEADERS})

target_include_directories(Morpheus.Metadata
    PRIVATE
        ${CLANG_INCLUDE_DIRS})

target_sources(Morpheus.Metadata
    PUBLIC
        FILE_SET morpheus_metadata TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Entities/Class.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Entities/DataMember.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Matchers/HasEntityAttribute.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/EntityRegistry.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Extractor.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Metadata.cppm)

target_link_libraries(Morpheus.Metadata
    Std
    clangTooling
    clangFrontend
    clangASTMatchers)

add_library(Morpheus::Metadata ALIAS Morpheus.Metadata)

