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
#include <algorithm>
#include <vector>
#include "settings.h"
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
        LOG("One or both functions does not intergrate to 1.");
        return NULL ; 
    }
    int n = 100 ; 
    double startRange = 0 ; 
    double endRange = 5 ; 
    double epsilon = ( endRange - startRange ) / ((double)n) ; 
    int n_discrete = 100 ; 
    
    const fl::Function2D::Function2DBase * pFirst = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[0].get() ); 
    const fl::Function2D::Function2DBase * pSecond = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[1].get() ); 
    
    double f1XStart  = pFirst->xStartWhereIntegratingMakesSense() ; 
    double f2XStart  = pSecond->xStartWhereIntegratingMakesSense() ; 
    
    LOG( "starts" << f1XStart << " " << f2XStart );
    
    double f1XStop  = pFirst->xStopWhereIntegratingMakesSense() ; 
    double f2XStop  = pSecond->xStopWhereIntegratingMakesSense() ;
    LOG( "stops " << f1XStop  << " " << f2XStop );
    
	double a1 = f1XStart;
	double b1 = f1XStop ; 
    double delta = ((b1) - (a1)) /(double)n_discrete ; 

	switch ( m_typeOp){
		case eAdd:
			{
				startRange = f1XStart + f2XStart ; 
				endRange = f1XStop+f2XStop ; 
				break;
			}
		case eMinus:
			{
				std::vector<double> findMinMax ; 
				startRange = f1XStart - f2XStop ; 
				endRange = f1XStop  - f2XStart; 
				break ; 
			}
		case eTimes:
			{
				std::vector<double> findMinMax ; 
				findMinMax.push_back(f1XStart*f2XStart);
				findMinMax.push_back(f1XStart*f2XStop);
				findMinMax.push_back(f2XStart*f1XStop);
				findMinMax.push_back(f2XStop*f1XStop);
				endRange = *(std::max_element(findMinMax.begin(),findMinMax.end()));
				startRange = *(std::min_element(findMinMax.begin(),findMinMax.end()));
				break;
			}
		case eDiv:
			{
				std::vector<double> findMinMax ; 
				findMinMax.push_back(f1XStart/f2XStart);
				findMinMax.push_back(f1XStart/f2XStop);
				findMinMax.push_back(f2XStart/f1XStop);
				findMinMax.push_back(f2XStop/f1XStop);
				endRange = *(std::max_element(findMinMax.begin(),findMinMax.end()));
				startRange = *(std::min_element(findMinMax.begin(),findMinMax.end()));
				break;
			}
	}
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
    for ( double sIter = startRange ; sIter < endRange; sIter += epsilon){
        x = sIter ; 
        double pp2=0;
        double pp1=0;
        for ( int jIter = 0 ; jIter < n_discrete;++jIter ){
            pp1 = pFirst->eval( t[jIter],&bOk );
            if ( bOk ) {
                switch ( m_typeOp ) {
                    case eAdd : 
                        pp2 = pSecond->eval(sIter - t[jIter],&bOk);
                        break ; 
                    case eMinus : 
                        pp2 = pSecond->eval(t[jIter] - sIter ,&bOk);
                        break ; 
                    case eTimes:
						if ( t[jIter] == 0  ){
							qDebug() << t[jIter] << "is null ! " ;
							continue ; 
						}
                        pp2 = pSecond->eval(sIter / t[jIter],&bOk);
                        break ; 
                    case eDiv:
						if ( sIter == 0 ){
							qDebug() << "sIter is null ! " ;
							continue ; 
						}
                        pp2 = pSecond->eval(t[jIter]/sIter,&bOk);
                        break ; 
                }
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

    LOG("stops" << f1XStop << " " << f2XStop );
    
    double dStep = Thesis::Settings::instance()->value(Thesis::SettingsNames::MathLib::scDefaultDiscreteStep).toDouble(); 
    
    double firstIntergral = pFirst->integrate(f1XStart,f1XStop,dStep);
    double secondIntergral = pSecond->integrate(f2XStart,f2XStop,dStep);
    
    LOG( pFirst->name().c_str() << " is integrating of range [" << f1XStart << " , " << f1XStop << "] to " << firstIntergral ) ; 
    LOG( pSecond->name().c_str() << " is integrating of range [" << f2XStart << " , " << f2XStop << "] to " << secondIntergral ) ; 

    double delta = 0.05 ; 
    // if firstIntegral - delta < 1 < firstIntergral + delta 
    if ( firstIntergral + delta > 1 && firstIntergral - delta < 1 && secondIntergral + delta > 1 && secondIntergral - delta < 1 )
        return true ; 

    m_error = IOperation::eNotIntegratingToOne ; 
    return false ; 
}

fl::FunctionBase* ConvolutionAdd::calculate()
{
	m_typeOp = eAdd ; 
	return ConvolutionOperation::calculate() ; 
}

fl::FunctionBase* ConvolutionMinus::calculate()
{
	//m_typeOp = eTimes ; 
	m_typeOp = eMinus ; 
	return ConvolutionOperation::calculate() ; 
}
fl::FunctionBase* ConvolutionTimes::calculate()
{
	m_typeOp = eTimes ; 
	return ConvolutionOperation::calculate() ; 
}
fl::FunctionBase* ConvolutionDiv::calculate()
{
	m_typeOp = eDiv; 
	return ConvolutionOperation::calculate() ; 
}