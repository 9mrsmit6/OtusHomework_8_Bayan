#ifndef FILTER_HPP
#define FILTER_HPP
#include <boost/regex.hpp>
#include <filesystem>
#include "../Options/Options.hpp"

//Фильтр для отсеивания путей
struct Filter
{

    Filter(const Options::RawOptions& opt_):
        masks{createExprations(opt_.fileMask)},
        opt{opt_}
    {

    }

    //Фильтр по регуляркам
    bool regexFilter(const std::string& path)
    {
        if(masks.empty()){return true;}
        boost::smatch rez;

        for(auto& expr:masks)
        {
            try
            {
                if(boost::regex_match(path,  rez, expr))
                {
                    return true;
                }
            }
            catch(...)
            {
                continue;
            }
        }
        return false;
    }

    //Фильтр по исключенным папкам
    bool dirFilter(const std::string& path)
    {
        for(auto& s:opt.excludeDirs)
        {
            if(path.find(s)!=std::string::npos)
            {
                return false;
            }
        }
        return true;
    }

private:
    const std::vector<boost::regex> masks;
    const Options::RawOptions& opt;

    //Конструирую выражение regex по строке
    std::vector<boost::regex> createExprations(const std::vector<std::string>&  mask)
    {
        std::vector<boost::regex> ret;
        for(auto& s:mask)
        {
            try
            {
                ret.emplace_back(s);
            }
            catch(...)
            {
                continue;
            }
        }
        return ret;
    }
};



#endif // FILTER_HPP
