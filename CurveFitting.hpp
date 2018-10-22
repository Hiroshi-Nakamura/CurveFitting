#ifndef CURVEFITTING_HPP_INCLUDED
#define CURVEFITTING_HPP_INCLUDED

#include "AutomaticDifferentiation.hpp"
#include "Minimization.hpp"
#include <vector>
#include <memory>

class CurveFitting {
    const std::vector<double> x;
    const std::vector<double> y;
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)=0; /// for solving the problem.
    virtual double model(const std::vector<double> param, const double x)=0; /// for checking the solution.
public:
    CurveFitting(const std::vector<double>& _x, const std::vector<double>& _y) : x(_x), y(_y) { assert(x.size()==y.size()); }

    virtual size_t num_param()=0;

    template<typename T>
    T residual(const std::vector<T> param){
        T rtn=AutomaticDifferentiation::zero<T>();
        for(size_t i=0; i<x.size(); i++){
            T redidual=model(param,x[i]) - y[i];
            rtn = rtn + redidual*redidual;
        }
        return rtn;
    }

    bool solve(Eigen::VectorXd& x_val)
    {
        return Minimization::minimization(
            [this](const std::vector<AutomaticDifferentiation::FuncPtr<double>> param){ return residual(param); },
            x_val);
    }
};

using FittingPtr=std::shared_ptr<CurveFitting>;

class LineFitting : public CurveFitting {
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)
    {
        return param[0]*x+param[1];
    }

    virtual double model(const std::vector<double> param, const double x)
    {
        return param[0]*x+param[1];
    }
public:
    LineFitting(const std::vector<double>& _x, const std::vector<double>& _y) : CurveFitting(_x,_y) {}
    virtual size_t num_param(){ return 2; };
};

class PolynomialFitting : public CurveFitting {
    size_t n;
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)
    {
        auto rtn=param[0];
        double mul_x=x;
        for(size_t i=1; i<=n; i++){
            rtn = rtn+param[i]*mul_x;
            mul_x *= x;
        }
        return rtn;
    }

    virtual double model(const std::vector<double> param, const double x)
    {
        auto rtn=param[0];
        double mul_x=x;
        for(size_t i=1; i<=n; i++){
            rtn = rtn+param[i]*mul_x;
            mul_x *= x;
        }
        return rtn;
    }
public:
    PolynomialFitting(const std::vector<double>& _x, const std::vector<double>& _y, const size_t _n) : CurveFitting(_x,_y), n(_n) {}
    virtual size_t num_param(){ return n+1; };
};

class CatenaryFitting : public CurveFitting {
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)
    {
        return param[0]*cosh(-(x-param[1])/param[0])+param[2];
    }

    virtual double model(const std::vector<double> param, const double x)
    {
        return param[0]*cosh(-(x-param[1])/param[0])+param[2];
    }
public:
    CatenaryFitting(const std::vector<double>& _x, const std::vector<double>& _y) : CurveFitting(_x,_y) {}
    virtual size_t num_param(){ return 3; };
};

class ExponentialFitting : public CurveFitting {
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)
    {
        return param[0]*exp(-(x-param[2])/param[1])+param[3];
    }

    virtual double model(const std::vector<double> param, const double x)
    {
        return param[0]*exp(-(x-param[2])/param[1])+param[3];
    }
public:
    ExponentialFitting(const std::vector<double>& _x, const std::vector<double>& _y) : CurveFitting(_x,_y) {}
    virtual size_t num_param(){ return 4; };
};

class InvCycloidFitting : public CurveFitting { /// Inv means exchanging x y value.
    virtual AutomaticDifferentiation::FuncPtr<double> model(const std::vector<AutomaticDifferentiation::FuncPtr<double>> param, const double x)
    {
        auto theta=acos(1.0-(x-param[2])/param[0]);
        return param[0]*(theta-sin(theta))+param[1];
    }

    virtual double model(const std::vector<double> param, const double x)
    {
        auto theta=acos(1.0-(x-param[2])/param[0]);
        return param[0]*(theta-sin(theta))+param[1];
    }
public:
    InvCycloidFitting(const std::vector<double>& _x, const std::vector<double>& _y) : CurveFitting(_x,_y) {}
    virtual size_t num_param(){ return 3; };
};

#endif // CURVEFITTING_HPP_INCLUDED
