#include "Options/Options.hpp"
#include "Scaner/Scaner.hpp"
#include "Hash/Hash.hpp"
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

    std::unique_ptr<Process::Processor> proc;

    switch(rawOptions.hashNumber)
    {
        case Options::HashType::CRC16:
            proc=std::make_unique<Process::Processor>(rawOptions.blockSize, scaner.getMaxBlockCount(), hashBlock<boost::crc_16_type>);
            break;

        case Options::HashType::XMODEM:
            proc=std::make_unique<Process::Processor>(rawOptions.blockSize, scaner.getMaxBlockCount(), hashBlock<boost::crc_xmodem_type>);
            break;

        case Options::HashType::CRC32:
        default:
            proc=std::make_unique<Process::Processor>(rawOptions.blockSize, scaner.getMaxBlockCount(), hashBlock<boost::crc_32_type>);
            break;
    }

    proc->searchDublicate(filesMap);
    Data::printFilesPaths(*filesMap);

    return 0;
}
