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

            return std::move(map);


        }

    private:

        template <class Iterator>
        void analizeDir(const std::filesystem::path& path, std::unique_ptr<Data::FileInfoBiMap>& bmP)
        {
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
                        bmP->insert({0, {   i->path(),  std::filesystem::file_size(i->path()),  false   }  });
                    }
                }
            }
            catch(...)
            {
                return;
            }
        }

        const Options::RawOptions& opt;
        Filter filter;

    };
}
#endif // SCANER_HPP
