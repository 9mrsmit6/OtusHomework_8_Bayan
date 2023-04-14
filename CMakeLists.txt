cmake_minimum_required(VERSION 3.5)

project(bayan LANGUAGES CXX)


set( BOOST_ROOT "/slowDataB/Boost/boost_1_81_0" )

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bayan
    main.cpp
    Options/Options.hpp
    Scaner/Scaner.hpp
    Filter/Filter.hpp
    Data/Data.hpp
    Processor/Processor.hpp
    Hash/Hash.hpp
)

target_link_libraries(bayan
        ${Boost_LIBRARIES}
        )

install(TARGETS bayan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
