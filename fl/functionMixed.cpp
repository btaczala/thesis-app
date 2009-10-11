
#include "functionMixed.h"

fl::Function2D::FunctionMixed::FunctionMixed( const std::string & _functionName ) :
fl::Function2D::Function2DBase(_functionName)
{
    m_Type = eMixed;
}

void fl::Function2D::FunctionMixed::addFunction( fl::Function2D::Function2DBase * pFunction, double start, double stop )
{
    FunctionRange frFunction ; 
    frFunction.m_spFunction.reset(pFunction);
    frFunction.m_start = start ; 
    frFunction.m_stop = stop ; 
    m_Functions.push_back(frFunction);
}
double fl::Function2D::FunctionMixed::eval( double point,bool *pOk ) const{
    *pOk = false ;
    std::vector<FunctionRange>::iterator it = m_Functions.begin();
    std::vector<FunctionRange>::iterator itEnd = m_Functions.end();
    double val = -1  ;
    for ( it ; it != itEnd ; ++it ) {
        if ( point > it->m_start && point < it->m_stop ) { 
            val = it->m_spFunction->eval(point,pOk);
            break ; 
        }
        else if ( point == it->m_start && point == it->m_stop ) {
            val = it->m_spFunction->eval(point,pOk);
            break ; 
        }
    }
    return val ; 
}
double fl::Function2D::FunctionMixed::min( ) {
    return -1 ; 
}
double fl::Function2D::FunctionMixed::max( ) {
    return -1 ; 
}

fl::Function2D::Function2DBase* fl::Function2D::FunctionMixed::integrate(double start, double stop)
{
    return NULL ; 
}
