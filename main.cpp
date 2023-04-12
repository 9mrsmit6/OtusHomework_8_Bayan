#include "Options/Options.hpp"
#include "Scaner/Scaner.hpp"
#include <iostream>
#include <boost/program_options.hpp>

#include <boost/regex.hpp>
#include "Processor/Processor.hpp"

//#include <boost/crc.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/bimap/support/lambda.hpp>



#include <vector>

#include <fstream>

using namespace  std;


namespace po = boost::program_options;

using Key=std::vector<int>;





int main(int argc, const char *argv[])
{
    auto[rawOptions, flag]=Options::getRawOptions(argc,argv);

    if(!flag)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }

    FileSearch::Scaner scaner(rawOptions);

    auto filesMap=scaner.createPaths();

    Process::Processor proc(rawOptions.blockSize, scaner.getMaxBlockCount());
    proc.searchDublicate(filesMap);

    Data::printFilesPaths(*filesMap);



    Data::FileInfoBiMap bimap;
    bimap.insert({1, {"1",1}});
    bimap.insert({1, {"2",1}});
    bimap.insert({1, {"3",1}});
    bimap.insert({2, {"4",1}});
    bimap.insert({3, {"5",1}});
    bimap.insert({3, {"6",1}});
    bimap.insert({4, {"7",1}});
    bimap.insert({5, {"8",1}});
    bimap.insert({5, {"9",1}});
    bimap.insert({5, {"00",1}});
    bimap.insert({6, {"11",1}});


    Data::printMap(bimap);
    cout<<"------------------------------------"<<endl;
    Data::eraseUniq(bimap);
    Data::printMap(bimap);




    //   auto it=filesMap->left.begin();

    //   for(;it!=filesMap->left.end();it++)
    //   {
    //       auto [path,v1,v2]=it->second;
    //        std::cout<<it->first<<":"<<path<<":"<<v1<<std::endl;
    //   }





    return 0;
}
