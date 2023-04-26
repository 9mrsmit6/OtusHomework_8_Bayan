cmake_minimum_required(VERSION 3.5)

project(bayan LANGUAGES CXX)

#MyBoostPath


option(CUSTOM_B_P "CustomBoostPath" OFF)

if(CUSTOM_B_P)
    set( BOOST_ROOT CACHE PATH "BoostPath")
endif()




find_package(Boost COMPONENTS program_options regex container REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bayan
    main.cpp
    Options/Options.hpp
    Scaner/Scaner.hpp
    Filter/Filter.hpp
    Data/Data.hpp
    Processing/Handler.hpp
    Hash/Hash.hpp
)

target_link_libraries(bayan   ${Boost_LIBRARIES}    )

install(TARGETS bayan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME   "${CMAKE_PROJECT_NAME}")
set(CPACK_PACKAGE_CONTACT 9mrsmit6@gmail.com)
include(CPack)
