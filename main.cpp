#include "Options/Options.hpp"
#include "Scaner/Scaner.hpp"
#include <iostream>
#include "Processor/Processor.hpp"


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
    auto filesMap=scaner.createPaths();

    Process::Processor proc(rawOptions.blockSize, scaner.getMaxBlockCount());
    proc.searchDublicate(filesMap);

    Data::printFilesPaths(*filesMap);

    return 0;
}
