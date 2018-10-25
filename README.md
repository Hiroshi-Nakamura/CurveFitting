# CurveFitting
Curve fitting by using of Minimization.
Basic class is CurveFitting, but it is vitual class, you cannot use itself. 
You can use some derived classes already prepared, Line, Polynomial, Catenary, Exponential, InvCycloid.
Or you can create a derive class from "CurveFitting" class.

The usage is shown in "CurveFittingMai.cpp".
First, call constructure, whiose arguments are points cordinates, `std::vector<double> x` and `std::vector<double> y`. 
