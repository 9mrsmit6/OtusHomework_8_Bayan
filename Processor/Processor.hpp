#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <memory>
#include "../Data/Data.hpp"
#include <optional>
#include <filesystem>
#include <fstream>
#include <vector>
#include <boost/bimap/support/lambda.hpp>

#include <boost/crc.hpp>

namespace Process
{
    struct Processor
    {

        Processor(const std::size_t blockSize_, const std::size_t blockCnt_):
            blockSize(blockSize_),
            maxBlockCnt(blockCnt_){}

        void searchDublicate(std::unique_ptr<Data::FileInfoBiMap>& map)
        {
            for(std::size_t i{0};i!=maxBlockCnt;i++)
            {
                auto seek=i*blockSize;
                for(auto it=map->right.begin();it!=map->right.end();it++)
                {
                    auto& [path, sz]=it->first;
                    if(sz<=seek){continue;}

                    auto newHash=getBlockHash(seek, path);
                    if(!newHash)
                    {
                        auto hash=combineHash(it->second, newHash.value());
                        map->right.modify_data(it,boost::bimaps::_data=hash);
                    }

                }

                Data::eraseUniq(*map);
            }
        }

    private:
        std::optional<std::size_t> getBlockHash(std::size_t seek, const std::filesystem::path& path)
        {
            std::vector<char> block(blockSize,0);
            try
            {
                std::ifstream file(path, std::ios_base::binary);
                if(!file.is_open())
                {
                    return std::nullopt;
                }


                file.seekg(seek);
                file.read(block.data(), blockSize);
                auto readedBytes=file.gcount();
                if(readedBytes==0)
                {
                    return std::nullopt;
                }

                file.close();
            }
            catch(...)
            {
                return std::nullopt;
            }

            return hashBlock(block);

        }


        std::size_t hashBlock( std::vector<char>& data)
        {
            boost::crc_32_type result;
            result.process_bytes(data.data(), data.size());
            return result.checksum();

        }

        std::size_t combineHash(std::size_t oldHash, std::size_t newHash)
        {
            oldHash ^= newHash + 0x9e3779b9 + (oldHash << 6) + (oldHash >> 2);
            return oldHash;
        }

        const std::size_t blockSize;
        const std::size_t maxBlockCnt;

    };
}

#endif // PROCESSOR_HPP
