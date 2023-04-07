#ifndef SCANER_HPP
#define SCANER_HPP

#include "../Options/Options.hpp"
#include "../Filter/Filter.hpp"
#include <boost/regex.hpp>
#include <memory>


namespace FileSearch
{
    struct Scaner
    {
        Scaner(const Options::RawOptions& opt_):
            opt(opt_),
            filter(opt_)
        {
            paths=std::make_unique<std::vector<std::filesystem::path>>();
        }

        void createPaths()
        {

            for(const auto& t:opt.includeDirs)
            {
                if(opt.isRecursive)
                {
                    analizeDir<std::filesystem::recursive_directory_iterator>(t);
                }
                else
                {
                    analizeDir<std::filesystem::directory_iterator>(t);
                }
            }


        }

    private:

        template <class Iterator>
        void analizeDir(const std::filesystem::path& path)
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
                        std::cout<<i->path()<<std::endl;
                        paths->push_back(i->path());
                    }
                }
            }
            catch(...)
            {
                return;
            }
        }

        const Options::RawOptions& opt;
        std::unique_ptr<std::vector<std::filesystem::path>> paths;

        Filter filter;

    };
}
#endif // SCANER_HPP
