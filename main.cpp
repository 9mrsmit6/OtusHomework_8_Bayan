#include "Options/Options.hpp"
#include "Scaner/Scaner.hpp"
#include <iostream>
#include <boost/program_options.hpp>

#include <boost/regex.hpp>

using namespace  std;


namespace po = boost::program_options;





int main(int argc, const char *argv[])
{
    auto[rawOptions, flag]=Options::getRawOptions(argc,argv);

    if(!flag)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }


    FileSearch::Scaner scaner(rawOptions);

    scaner.createPaths();

    return 0;
}
