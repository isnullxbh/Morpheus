add_library(Std)

set_target_properties(Std
    PROPERTIES
        OUTPUT_NAME "Std"
        PREFIX      "")

target_compile_features(Std
    PUBLIC
        cxx_std_20)

target_sources(Std
    PUBLIC
        FILE_SET std TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Def.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Memory.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Std.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Strings.cppm
                ${CMAKE_CURRENT_SOURCE_DIR}/Utility.cppm)

target_link_libraries(Std)
