#include "Options/Options.hpp"
#include <iostream>
#include <boost/program_options.hpp>

using namespace  std;


namespace po = boost::program_options;





int main(int argc, const char *argv[])
{
    auto[rawOptions, flag]=Options::getRawOptions(argc,argv);

    if(!flag)
    {
        std::cout<<"Options Parse Error";
        return -1;
    }

    for(auto& t:rawOptions.includeDirs)
    {

        std::cout<<"INC: "<<t<<endl;

    }


//        if (vm.count("help"))
//        {
//            std::cout << desc << '\n';
//        }

//        if(vm.count("include"))
//        {
//            auto& vect=vm["include"].as<vector<string>>();
//            for(auto& t:vect)
//            {
//                std::cout<<"INC: "<<t<<endl;
//            }
//        }

//        if(vm.count("exclude"))
//        {
//            auto& vect=vm["exclude"].as<vector<string>>();
//            for(auto& t:vect)
//            {
//                std::cout<<"EXC: "<<t<<endl;
//            }
//        }



    return 0;
}
