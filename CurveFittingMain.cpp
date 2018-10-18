#include "CurveFitting.hpp"
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char** argv)
{
    try{
        if(argc!=2){ throw std::string("too few args."); }
        std::string filename(argv[1]);
        std::ifstream ifs(filename);
        if(!ifs.is_open()){ throw std::string("cannot open file")+filename; }

        std::vector<double> x;
        std::vector<double> y;
        std::string line;

        for(int i=0; std::getline(ifs,line); i++){
            std::vector<std::string> elements;
            boost::split(elements, line, boost::is_any_of(","));
            if(elements.size()==1){
                x.push_back(i);
                y.push_back(std::stod(elements[0]));
            }else if(elements.size()==2){
                x.push_back(std::stod(elements[0]));
                y.push_back(std::stod(elements[1]));
            }else{
                throw std::string("bad file format.");
            }
        }

        {
            std::cout << "---Line Fitting---" << std::endl;
            LineFitting line_fit(x,y);

            Eigen::VectorXd x_val(2);
            x_val.setOnes();
            line_fit.solve(x_val);
            std::cout << x_val << std::endl;

            std::vector<double> vec_x(x_val.data(),x_val.data()+2);
            std::cout << "residual(vec_x)=" << line_fit.residual(vec_x) << std::endl;
        }
        {
            std::cout << "---Catenary Fitting---" << std::endl;
            CatenaryFitting catenary_fit(x,y);

            Eigen::VectorXd x_val(3);
            x_val << 8.0, 19.0, 40.0;
            catenary_fit.solve(x_val);
            std::cout << x_val << std::endl;

            std::vector<double> vec_x(x_val.data(),x_val.data()+3);
            std::cout << "residual(vec_x)=" << catenary_fit.residual(vec_x) << std::endl;
        }
        {
            std::cout << "---Exponential Fitting---" << std::endl;
            ExponentialFitting exponential_fit(x,y);

            Eigen::VectorXd x_val(4);
            x_val << 10.0, 2.0, 0.0, 0.0;
            exponential_fit.solve(x_val);
            std::cout << x_val << std::endl;

            std::vector<double> vec_x(x_val.data(),x_val.data()+3);
            std::cout << "residual(vec_x)=" << exponential_fit.residual(vec_x) << std::endl;
        }
    }catch(std::string message){
        std::cout << message << std::endl;
        std::cout << "Usage: CurveFitting data_file.csv" << std::endl;
    }

}
