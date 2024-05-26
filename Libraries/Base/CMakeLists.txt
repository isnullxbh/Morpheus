add_library(Morpheus.Base)

set_target_properties(Morpheus.Base
    PROPERTIES
        OUTPUT_NAME "Morpheus.Base"
        PREFIX      "")

target_compile_features(Morpheus.Base
    PUBLIC
        cxx_std_20)

target_sources(Morpheus.Base
    PUBLIC
        FILE_SET morpheus_base TYPE CXX_MODULES
            FILES
                ${CMAKE_CURRENT_SOURCE_DIR}/Uri.cppm)

target_link_libraries(Morpheus.Base
    Std)

add_library(Morpheus::Base ALIAS Morpheus.Base)
