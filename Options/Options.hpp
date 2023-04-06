#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <optional>
#include <tuple>

namespace Options
{
    struct RawOptions
    {
        std::vector<std::string>    includeDirs;
        std::vector<std::string>    excludeDirs;
        bool                        isRecursive{true};
        std::size_t                 minFileSize{1};//in bytes
        std::vector<std::string>    fileMask;
        std::size_t                 blockSize{1};
        int                         hashNumber{0};
    };

    std::tuple<RawOptions&, bool> getRawOptions(int argc, const char *argv[])
    {
        namespace po = boost::program_options;

        static RawOptions opt;

        try
        {
            po::options_description desc{"Options"};
            desc.add_options()
                    ("help,h", "Select optins")
                    ("include,I",   po::value< std::vector<std::string> >   (&opt.includeDirs),    "Include Directoris")
                    ("exclude,E",   po::value< std::vector<std::string> >   (&opt.excludeDirs),    "Exclude Directoris")
                    ("recursive,r", po::value< bool >                       (&opt.isRecursive),    "Recursive")
                    ("fsize,s",     po::value< std::size_t >                (&opt.minFileSize),    "min file size")
                    ("mask,m",      po::value< std::vector<std::string> >   (&opt.fileMask),       "mask")
                    ("bsize,bs",    po::value< std::size_t>                 (&opt.blockSize),      "blockSize")
                    ("hash,h",      po::value< int >                        (&opt.hashNumber),     "hash type []");

            po::variables_map vm;
            po::store(parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
        }
        catch(...)
        {
            return std::tuple<RawOptions&, bool>{opt,false};
        }

        return std::tuple<RawOptions&, bool>{opt,true};
    }


}
#endif // OPTIONS_HPP
