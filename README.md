# CurveFitting
Curve fitting by using of Minimization.
Base class is CurveFitting, but it is vitual class, which you cannot use itself. 
You can use some derived classes already prepared, Line, Polynomial, Catenary, Exponential and InvCycloid class.
Or you can create a derived class from "CurveFitting" class.

The usage is shown in "CurveFittingMai.cpp".
First, call constructure, whose arguments are sample points cordinates, `std::vector<double> x` and `std::vector<double> y`. 
Next, prepare `std::vector<double>` as initial values of curve equation parameter, or `Eigen::VectorXd` is acceptable.
Last, call `solve()` function. Its argument will be updated to the solution.

In the case of creating a new derived class, you should define its `model()` function.
Because template class cannot be vitrual class, you should define 2 types of `model()` function.
One is for `AutomaticDifferentiation::FuncPtr<double>`, the other is for `double`.
Their return will be the curve equation, to which you want to fit the sample data.
Additionally, you need to define `num_param()`, 
which is helpful to inform how many dimention the parameter vector needs.
