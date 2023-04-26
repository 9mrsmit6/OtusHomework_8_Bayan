#include "Options/Options.hpp"
#include "Scaner/Scaner.hpp"
#include "Hash/Hash.hpp"
#include <iostream>
#include "Processing/Handler.hpp"


using namespace  std;

namespace po = boost::program_options;

auto createHandler(Options::RawOptions& opt, std::size_t blockCnt)
{

    switch(opt.hashNumber)
    {
        case Options::HashType::CRC16:       return Processing::Handler(opt.blockSize, blockCnt, hashBlock<boost::crc_16_type>);

        case Options::HashType::XMODEM:      return Processing::Handler(opt.blockSize, blockCnt, hashBlock<boost::crc_xmodem_type>);

        case Options::HashType::CRC32:
        default:
                                             return Processing::Handler(opt.blockSize, blockCnt, hashBlock<boost::crc_32_type>);
    }

//    std::array hashers =
//    {
//        hashBlock<boost::crc_16_type>, hashBlock<boost::crc_xmodem_type>, hashBlock<boost::crc_32_type>
//    };

// //   static_assert(size_t(Options::HashType::END_) == hashers.size(), "Fix hashers array");
//    return Processing::Handler(opt.blockSize, blockCnt, hashers.at( size_t(opt.hashNumber) ));

}



int main(int argc, const char *argv[])
{
    auto rawOptions=Options::getRawOptions(argc,argv);

    if(!rawOptions)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }

    FileSearch::Scaner scaner(rawOptions.value());
    auto filesMap=scaner.createPaths();

    auto proc=createHandler(rawOptions.value(), scaner.getMaxBlockCount());
    proc.searchDublicate(*filesMap);

    Data::printFilesPaths(*filesMap);

    return 0;
}
