#ifndef DATA_HPP
#define DATA_HPP

#include <filesystem>
#include <tuple>
#include <iostream>

#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>


namespace Data
{
    //Info о файле. Путь и размер
    using FileInfo=std::tuple<std::filesystem::path, std::size_t>;

    //Определяю bimap
    using FileInfoBiMap=boost::bimap<
            boost::bimaps::multiset_of<std::size_t>,
            boost::bimaps::set_of<FileInfo>
            >;




    //Удаляю записи с уникальных хешем
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

    //Печаталка записей
    void printMap(Data::FileInfoBiMap& map)
    {
        for(auto& i:map)
        {
            auto [path, size]=i.right;
            std::cout<<i.left<<":"<<path<<std::endl;
        }
    }

    //Печаталка тольо путей
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
