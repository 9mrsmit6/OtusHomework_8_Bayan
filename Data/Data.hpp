#ifndef DATA_HPP
#define DATA_HPP
#include <filesystem>
#include <tuple>
#include <iostream>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/support/lambda.hpp>

namespace Data
{
    using FileInfo=std::tuple<std::filesystem::path, std::size_t>;
//    struct FileInfo
//    {
//        std::filesystem::path path;
//        std::size_t size;
//        bool skip;
//    };


using FileInfoBiMap=boost::bimap<
        boost::bimaps::multiset_of<std::size_t>,
        boost::bimaps::set_of<FileInfo>
        >;





void eraseUniq(Data::FileInfoBiMap& map)
{
    std::vector<decltype(map.left.begin())> needErase;

    for(auto i=map.left.begin(); i!=map.left.end();i++)
    {
        if(map.left.count(i->first)<=1)
        {
            needErase.push_back(i);
        }
    }

    for(auto& i:needErase)
    {
       map.left.erase(i);
    }
}

void printMap(Data::FileInfoBiMap& map)
{
    for(auto& i:map)
    {
        auto [path, size]=i.right;
        std::cout<<i.left<<":"<<path<<std::endl;
    }
}

void printFilesPaths(Data::FileInfoBiMap& map)
{
    for(auto& i:map)
    {
        auto [path, size]=i.right;
        std::cout<<path<<std::endl;
    }
}

}
#endif // DATA_HPP
