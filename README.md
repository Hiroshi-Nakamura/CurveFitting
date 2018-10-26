# CurveFitting
Curve fitting by using of Minimization.
Base class is CurveFitting, but it is vitual class, which you cannot use itself. 
You can use some derived classes already prepared, Line, Polynomial, Catenary, Exponential, InvCycloid.
Or you can create a derive class from "CurveFitting" class.

The usage is shown in "CurveFittingMai.cpp".
First, call constructure, whose arguments are sample points cordinates, `std::vector<double> x` and `std::vector<double> y`. 
Next, prepare `std::vector<double>` as initial values of curve equation parameter, or `Eigen::VectorXd` is acceptable.
Last, call solve() function. Its argument will be updated to the solution.

