#include <iostream>
#include <boost/assign/std/vector.hpp>
#include <functionException.h>

#include "functiondiscrete.h"
#include "functioncontinous.h"

using namespace boost::assign;

int main(int argc, char **argv) {
    try{
//         fl::FunctionDiscrete<double> f2dDis("some func") ; 
//         fl::FunctionContinous<double> f2Cont("sinus function");
//         f2Cont.addVariable('x');
//         f2Cont.setEquation("sin(x)");
//         std::cout << f2Cont.evaluate(0);
// 
 
//         f2dDis.addPoints(xs,ys);
//         std::cout << "\nDiscrete:"<< f2dDis.integrate(1,5,fl::eTrapezoidalRule);
//         std::string ax ; 
//         fl::FunctionMixed<double> f2Mixed( "mixed one!" ) ; 
//         std::vector<char> args ; 
//         args += 'x' ; 
//         f2Mixed.addFunction(fl::scInfinity_Minus,0,"2*x-1",args) ;
//         f2Mixed.addFunction(0,0,"2*x-1",args) ;
//         f2Mixed.addFunction(0,1,"1",args) ;
//         f2Mixed.addFunction(1,1,"2*x+1",args) ;
//         f2Mixed.addFunction(1,fl::scInfinity_Plus,"2*x+1",args) ;
// 
//         //f2Mixed.integrate(-3,4,fl::eRectangleRule);
//         
//         std::cout << "\nEval of Mixed function f(-1):" << f2Mixed.evaluate(-1);
//         std::cout << "\nEval of Mixed function f(0.4):" << f2Mixed.evaluate(0.4);
//         std::cout << "\nEval of Mixed function f(1):" << f2Mixed.evaluate(1);
//         std::cout << "\nEval of Mixed function f(4):" << f2Mixed.evaluate(4);
// 
//         std::cout << "\nIntegrate f(x) 0 - 2 :" << f2Mixed.integrate(0,2);
            std::vector<double> xs ; 
            std::vector<double> ys ;
            std::vector<double> zs ; 
            xs += 1,2,3,4,5,6 ; 
            ys += -40,77,1,1,2,2 ;
            zs += 0,0,0,0,0,0;
            
            fl::Function2D::FunctionDiscrete fl(xs,ys,"sin?"); 
            std::cout << fl.eval(3) << std::endl ; 
            
            
            std::cout << fl.max() << std::endl ; 
            std::cout << fl.min() << std::endl ; 

			fl::Function3D::FunctionDiscrete fd(xs,ys,zs,"Simple 3d discrete function");
            
            
            fl::Function2D::FunctionContinous fC ; 
            fC.setEquation("sin(x)");
            fC.addVariable("x");
            std::cout << fC.eval(0);
    }
    catch ( fl::FunctionException & e )
    {
        const char *ww = e.what() ; 
        std::cout << ww ;
    }
    return 0;
}
