/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) <year>  <name of author>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.    

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "convolutionoperation.h"
#include "fl/function2dbase.h"
#include "fl/functiondiscrete.h"
#include <QDebug>
#include "commons.h"

ConvolutionOperation::ConvolutionOperation ( ) : IOperation ()
{
}
void ConvolutionOperation::addFunction ( fl::FunctionBase* pPtr )
{
    if ( m_functions.size() == 2 ) 
        return ; // cannot add more than 2 functions. 
    IOperation::addFunction ( pPtr );
}

fl::FunctionBase* ConvolutionOperation::calculate()
{
    cLOG();

    if ( ! areIntegratingToOne() )
    {

        LOG("Functions does not intergrate to 1 !!");
        return NULL ; 
    }
    int n = 100 ; 
    double startRange = 0 ; 
    double endRange = 5 ; 
    double epsilon = ( endRange - startRange ) / ((double)n) ; 
    int n_discrete = 100 ; 
    int a1 = 0 ;
    int b1 = 2 ;
    double delta = (b1 - a1) /(double)n_discrete ; 
    const fl::Function2D::Function2DBase * pFirst = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[0].get() ); 
    const fl::Function2D::Function2DBase * pSecond = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[1].get() ); 
    
    double f1XStart  = pFirst->xStartWhereIntegratingMakesSense() ; 
    double f2XStart  = pSecond->xStartWhereIntegratingMakesSense() ; 
    
    LOG( "starts" << f1XStart << " " << f2XStart );
    
    double f1XStop  = pFirst->xStopWhereIntegratingMakesSense() ; 
    double f2XStop  = pSecond->xStopWhereIntegratingMakesSense() ;
    LOG( "stops " << f1XStop  << " " << f2XStop );
    
    

    startRange = f1XStart + f2XStart ; 
    endRange = f1XStop+f2XStop ; 
    
    LOG( "Meaning full range [  "<< startRange << " , " << endRange<<" ]");

    std::vector<double> t ; // those are my x's
    double to_insert;
    for ( double j = 1 ; j < n_discrete+1 ; ++j ) {
        to_insert = j - 0.5f; 
        to_insert *=delta ; 
        to_insert+= a1 ; 
        t.push_back( to_insert ) ;
    }
    std::vector<double> xs ; 
    std::vector<double> ys ; 
    std::vector<double> ys2 ; 
    double partialResult=0;
    bool bOk ; 
    double x=0; 
    double y=0; 
    for ( double sIter = startRange ; sIter < endRange+0.5 ; sIter +=0.1){
        x = sIter ; 
        double pp2=0;
        double pp1=0;
        for ( int jIter = 0 ; jIter < n_discrete;++jIter ){
            //int realIter = t.size() - jIter ; 
            pp1 = pFirst->eval( t[jIter],&bOk );
            if ( bOk ) {
                switch ( m_typeOp ) {
                    case eAdd : 
                        pp2 = pSecond->eval(sIter - t[jIter],&bOk);
                        break ; 
                    case eMinus : 
                        pp2 = pSecond->eval(sIter + t[jIter],&bOk);
                        break ; 
                    case eTimes:
                        pp2 = pSecond->eval(sIter / t[jIter],&bOk);
                        break ; 
                    case eDiv:
                        pp2 = pSecond->eval(sIter * t[jIter],&bOk);
                        break ; 
                }
                //pp2 = pSecond->eval(sIter - t[jIter],&bOk);
                if ( bOk ) {
                    y += pp1 * pp2 ;
                }
            }
        }
        y*= (double)delta;
        xs.push_back(x);
        ys.push_back(y);
        x=0;
        y=0;
    }
	qDebug() << xs ; 
    qDebug() << ys ; 
    std::string funName = "Convolution : "  + pFirst->name() + pSecond->name() ;
    fl::Function2D::Function2DBase * pResult = new fl::Function2D::FunctionDiscrete(xs,ys,funName);
    return pResult;
}

bool ConvolutionOperation::areIntegratingToOne() const 
{
    cLOG();
    const fl::Function2D::Function2DBase * pFirst = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[0].get() ); 
    const fl::Function2D::Function2DBase * pSecond = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[1].get() );
    
    double f1XStart  = pFirst->xStartWhereIntegratingMakesSense() ; 
    double f2XStart  = pSecond->xStartWhereIntegratingMakesSense() ; 
    
    LOG("starts" << f1XStart << " " << f2XStart );
    
    double f1XStop  = pFirst->xStopWhereIntegratingMakesSense() ; 
    double f2XStop  = pSecond->xStopWhereIntegratingMakesSense() ;
    
    double firstIntergral = pFirst->integrate(f1XStart,f1XStop,0.01);
    double secondIntergral = pSecond->integrate(f2XStart,f2XStop,0.01);

    double delta = 0.01 ; 
    // if firstIntegral - delta < 1 < firstIntergral + delta 
    if ( firstIntergral + delta > 1 && firstIntergral - delta < 1 && secondIntergral + delta > 1 && secondIntergral - delta < 1 )
        return true ; 

    return false ; 
}


