#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <filesystem>

#include <tuple>

namespace Options
{
    enum class HashType
    {
        CRC32=0,
        CRC16,
        XMODEM
    };

    //Хранение сырых опций
    struct RawOptions
    {
        std::vector<std::filesystem::path>      includeDirs;
        std::vector<std::string>                excludeDirs;
        bool                                    isRecursive{true};
        std::size_t                             minFileSize{1};//in bytes
        std::vector<std::string>                fileMask{{"(\\w+).md"}};
        std::size_t                             blockSize{10};
        HashType                                hashNumber{HashType::CRC16};
    };

    int hashNumber{0};



    //Парсим опции
    std::tuple<RawOptions&, bool> getRawOptions(int argc, const char *argv[])
    {
        namespace po = boost::program_options;

        static RawOptions opt;

        try
        {
            po::options_description desc{"Options"};
            desc.add_options()
                    ("help,h", "Show help")
                    ("include,I",   po::value< std::vector<std::filesystem::path> >   (&opt.includeDirs),    "Include Directoris DEF: ./")
                    ("exclude,E",   po::value< std::vector<std::string> >   (&opt.excludeDirs),    "Exclude Directoris DEF: empty")
                    ("recursive,r", po::value< bool >                       (&opt.isRecursive),    "Recursive bool DEF: true")
                    ("fsize,s",     po::value< std::size_t >                (&opt.minFileSize),    "min file size (size_t) DEF: 1")
                    ("mask,m",      po::value< std::vector<std::string> >   (&opt.fileMask),       "mask DEF: (\\w+).md  (md files)")
                    ("bsize,b",    po::value< std::size_t>                 (&opt.blockSize),      "blockSize (size_t) DEF: 10")
                    ("hash,H",     po::value< int >                        (&hashNumber),         "hash type [0->CRC32; 1->CRC16; 2->XMODEM] DEF: CRC32");

            po::variables_map vm;
            po::store(parse_command_line(argc, argv, desc), vm);
            po::notify(vm);

            if(opt.includeDirs.empty())
            {
                opt.includeDirs.push_back(".");
            }


            if (vm.count("help")) {
                std::cout << desc << "\n";
            }

            switch(hashNumber)
            {
                case 0: opt.hashNumber=HashType::CRC32;     break;
                case 1: opt.hashNumber=HashType::CRC16;     break;
                case 2: opt.hashNumber=HashType::XMODEM;    break;
                default:opt.hashNumber=HashType::CRC32;     break;
            };
        }
        catch(...)
        {
            return std::tuple<RawOptions&, bool>{opt,false};
        }

        return std::tuple<RawOptions&, bool>{opt,true};
    }


}
#endif // OPTIONS_HPP
