#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <memory>
#include "../Data/Data.hpp"
#include <optional>
#include <filesystem>
#include <fstream>
#include <vector>
#include <boost/bimap/support/lambda.hpp>

namespace Process
{
    struct Processor
    {
        void searchDublicate(std::unique_ptr<Data::FileInfoBiMap>& map)
        {
            for(std::size_t i{0};i!=maxBlockDeep;i++)
            {
                bool skipedAll{true};
                for(auto it=map->right.begin();it!=map->right.end();it++)
                {
                    auto fInfo=it->first;
                    if(fInfo.skip){continue;}
                    if(oversize(fInfo.size))
                    {
                        fInfo.skip=true;
                        map->right.modify_data(it,boost::bimaps::_data=fInfo);
                        continue;
                    }

                    auto newHash=getBlockHash(i, fInfo.path);
                    if(!newHash)
                    {
                        fInfo.skip=true;
                        map->right.modify_data(it,boost::bimaps::_data=fInfo);
                    }

                }
            }
        }

    private:
        std::optional<std::size_t> getBlockHash(std::size_t blockN, std::filesystem::path& path)
        {
            std::ifstream file(path, std::ios_base::binary);
            if(!file.is_open())
            {
                return std::nullopt;
            }

            std::size_t seek=blockN*blockSize;
            if(seek>=file.tellg())
            {
                return std::nullopt;
            }

            std::vector<char> block(blockSize,0);
            file.seekg(seek);
            file.read(block.data(), blockSize);
            auto readedBytes=file.gcount();
            if(readedBytes==0)
            {
                return std::nullopt;
            }

            file.close();

            return hashBlock(block);

        }


        std::size_t hashBlock( std::vector<char>& data)
        {
            return 123;
        }

        bool oversize(std::size_t fsize)
        {
            auto seek=currentBlockN*blockSize;
            return seek>=fsize;
        }


        const std::size_t blockSize{100};
        const std::size_t maxBlockDeep{100};
        std::size_t currentBlockN{0};
    };
}

#endif // PROCESSOR_HPP
