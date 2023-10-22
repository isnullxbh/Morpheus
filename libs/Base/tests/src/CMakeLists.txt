find_package(GTest CONFIG REQUIRED)

add_executable(Morpheus.Base.Tests)

target_include_directories(Morpheus.Base.Tests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(Morpheus.Base.Tests
    PRIVATE
        main.cpp
        Morpheus/Exception.Test.cpp)

target_link_libraries(Morpheus.Base.Tests
    PRIVATE
        GTest::gtest
        Morpheus::Base)
