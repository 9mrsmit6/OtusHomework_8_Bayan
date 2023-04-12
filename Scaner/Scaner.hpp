#ifndef SCANER_HPP
#define SCANER_HPP

#include "../Options/Options.hpp"
#include "../Filter/Filter.hpp"
#include "../Data/Data.hpp"
#include <boost/regex.hpp>
#include <memory>


namespace FileSearch
{
    struct Scaner
    {
        Scaner(const Options::RawOptions& opt_):
            opt(opt_),
            filter(opt_)
        {   }

        std::unique_ptr<Data::FileInfoBiMap> createPaths()
        {

            auto map=std::make_unique<Data::FileInfoBiMap>();

            for(const auto& t:opt.includeDirs)
            {
                if(opt.isRecursive)
                {
                    analizeDir<std::filesystem::recursive_directory_iterator>(t, map);
                }
                else
                {
                    analizeDir<std::filesystem::directory_iterator>(t, map);
                }
            }

            Data::eraseUniq(*map);
            maxBlockCnt=map->left.rbegin()->first;
            return std::move(map);
        }

        std::size_t getMaxBlockCount(){return maxBlockCnt;}

    private:

        template <class Iterator>
        void analizeDir(const std::filesystem::path& path, std::unique_ptr<Data::FileInfoBiMap>& bmP)
        {
            auto blockSize=opt.blockSize;
            if(blockSize==0){   blockSize=1;   }

            try
            {
                Iterator it(path);
                Iterator end;

                for(auto i=it;i!=end;i++)
                {
                    if(
                            (i->is_regular_file()) &&
                            (i->file_size()>= opt.minFileSize)  &&
                            filter.regexFilter(i->path().filename()) &&
                            filter.dirFilter(i->path())
                      )
                    {
                       auto sz=std::filesystem::file_size(i->path());
                       auto blCnt=(sz/blockSize)+1;
                       bmP->insert({blCnt, {   i->path(),  sz }  });
                    }
                }
            }
            catch(...)
            {
                return;
            }
        }

        const Options::RawOptions& opt;
        std::size_t maxBlockCnt{0};
        Filter filter;

    };
}
#endif // SCANER_HPP
