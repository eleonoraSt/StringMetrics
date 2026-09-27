cmake_minimum_required(VERSION 3.19)
project(StringMetrics LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.11 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_library(libStringMetrics
    STATIC
        include/editDistance.h
        include/editDistance_utils.h
        include/utfChars.h
)

qt_add_executable(StringMetrics
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(StringMetrics
    PRIVATE
        libStringMetrics
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

enable_testing()

find_package(Qt6 6.11 REQUIRED COMPONENTS Test)

qt_add_executable(testLevenstein
    tests/TestLevenstein.cpp
)

qt_add_executable(testDamerauLevenstein
    tests/TestDamerauLevenstein.cpp
)

qt_add_executable(testHamming
    tests/TestHamming.cpp
)

qt_add_executable(testLCS
    tests/TestLCS.cpp
)

target_link_libraries(testLevenstein
    PRIVATE
        libStringMetrics
        Qt6::Core
        Qt6::Test
)

target_link_libraries(testDamerauLevenstein
    PRIVATE
        libStringMetrics
        Qt6::Core
        Qt6::Test
)

target_link_libraries(testHamming
    PRIVATE
        libStringMetrics
        Qt6::Core
        Qt6::Test
)

target_link_libraries(testLCS
    PRIVATE
        libStringMetrics
        Qt6::Core
        Qt6::Test
)

add_test(NAME testLevenstein COMMAND testLevenstein)
add_test(NAME testDamerauLevenstein COMMAND testDamerauLevenstein)
add_test(NAME testHamming COMMAND testHamming)
add_test(NAME testLCS COMMAND testLCS)

install(TARGETS StringMetrics
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET StringMetrics
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
