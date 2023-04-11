#ifndef DATA_HPP
#define DATA_HPP
#include <filesystem>
#include <tuple>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/support/lambda.hpp>

namespace Data
{
    struct FileInfo
    {
        std::filesystem::path path;
        std::size_t size;
        bool skip;
    };


using FileInfoBiMap=boost::bimap<
        boost::bimaps::multiset_of<std::size_t>,
        boost::bimaps::set_of<FileInfo>
        >;
}

#endif // DATA_HPP
