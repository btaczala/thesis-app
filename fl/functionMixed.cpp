
#include "functionMixed.h"
#include "commons.h"
#include <algorithm>


fl::Function2D::FunctionMixed::FunctionMixed( const std::string & _functionName ) :
fl::Function2D::Function2DBase(_functionName)
{
    m_Type = eMixed;
}

void fl::Function2D::FunctionMixed::addFunction( fl::Function2D::FunctionContinous* pFunction, double start, fl::Function2D::FunctionMixed::Operator startOperator, double stop, fl::Function2D::FunctionMixed::Operator stopOperator )
{
    FunctionRange frFunction ; 
    frFunction.m_spFunction.reset(pFunction);
    frFunction.m_start = start ; 
    frFunction.m_stop = stop ; 
    frFunction.m_operatorStart= startOperator;
    frFunction.m_operatorStop = stopOperator;
    m_Functions.push_back(frFunction);
}
bool fl::Function2D::FunctionMixed::isHere (double point, const FunctionRange & funRange) const 
{
    if ( point == funRange.m_start && point == funRange.m_stop)
        return true ; 
    if ( point == funRange.m_start && funRange.m_operatorStart == eGreaterEqual){
        if ( point < funRange.m_stop )
            return true ; 
    }
    else if ( point > funRange.m_start ){
        if ( point < funRange.m_stop ){
            return true ; 
        }
        else if ( point == funRange.m_stop && funRange.m_operatorStop==eGreaterEqual ){
            return true ; 
        }
    }
    return false ; 
}
double fl::Function2D::FunctionMixed::eval( double point,bool *pOk ) const{
    *pOk = false ;
    std::vector<FunctionRange>::const_iterator it = m_Functions.begin();
    std::vector<FunctionRange>::const_iterator itEnd = m_Functions.end();
    double val = -1  ;
    bool bOk ; 
    for ( it ; it != itEnd ; ++it ) {
        if ( isHere(point,*it)){
            val = it->m_spFunction->eval(point,&bOk);
            *pOk = true ; 
            break ; 
        }
    }
    return val ; 
}
double fl::Function2D::FunctionMixed::min( ) const {
    //TODO: implement ?!
    return -1 ; 
}
double fl::Function2D::FunctionMixed::max( ) const {
    //TODO: implement ?!
    return -1 ; 
}

//double fl::Function2D::FunctionMixed::integrate(double start, double stop,double dStep)
//{
//    //TODO: implement ?!
//    return NULL ; 
//}


double fl::Function2D::FunctionMixed::xStartWhereIntegratingMakesSense() const 
{
    std::vector<double> results ; 
    double xStart ; 
    double val = 0 ; 
    static const int nIloscProbek = 10 ; 
    std::vector<FunctionRange>::const_iterator it = m_Functions.begin();
    std::vector<FunctionRange>::const_iterator itEnd = m_Functions.end();
    double xStop ; 
    double iter ; 
    double result ; 
    bool bOk ; 
    for ( it ; it != itEnd ; ++it ) {
        xStart = it->m_start ;
        xStop = it->m_stop; 
        if ( Thesis::Math::isInfinite( xStart ) ){
            xStart = -4000;
        }
        if ( Thesis::Math::isInfinite(xStop) ) {
            xStop = 4000 ; 
        }
        double xStep = (xStop - xStart) / (double)nIloscProbek;
        for ( int i = 0 ; i < nIloscProbek ; ++i ) {
            iter = ((double)i) + xStep ;
            val += it->m_spFunction->eval(iter,&bOk);
        }
        if ( val != 0 ) {
            result = it-> m_start ; 
            results.push_back(result);
        }
    }
    double r = *( std::min_element( results.begin(),results.end() ) );
    return r ;
}
double fl::Function2D::FunctionMixed::xStopWhereIntegratingMakesSense() const
{
    std::vector<double> results ; 
    double xStart ; 
    double val =0 ; 
    static const int nIloscProbek = 10 ; 
    std::vector<FunctionRange>::const_iterator it = m_Functions.begin();
    std::vector<FunctionRange>::const_iterator itEnd = m_Functions.end();
    double xStop ; 
    double iter ; 
    double result ; 
    bool bOk ; 
    for ( it ; it != itEnd ; ++it ) {
        xStart = it->m_start ;
        xStop = it->m_stop; 
        if ( Thesis::Math::isInfinite( xStart ) ){
            xStart = -4000;
        }
        if ( Thesis::Math::isInfinite(xStop) ) {
            xStop = 4000 ; 
        }
        double xStep = (xStop - xStart) / (double)nIloscProbek;
        for ( int i = 0 ; i < nIloscProbek ; ++i ) {
            iter = ((double)i) + xStep ;
            val += it->m_spFunction->eval(iter,&bOk);
        }
        if ( val != 0 ) {
            result = it-> m_stop ; 
            results.push_back(result);
        }
    }
    double r = *(std::max_element(results.begin(),results.end()));
    return result ;

}


