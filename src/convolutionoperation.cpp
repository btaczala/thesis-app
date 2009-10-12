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



ConvolutionOperation::ConvolutionOperation ( ConvolutionOperation::OperationType type ) : IOperation (), m_operationType (type)
{
    switch ( m_operationType ) {
        case eAdd : 
            m_opposedOperationType = eMinus ;
            break ; 
        case eMinus : 
            m_opposedOperationType = eMinus ;
            break ; 
        case eTimes:
            m_opposedOperationType = eSub ;
            break ;
        case eSub:
            m_opposedOperationType = eTimes ;
            break ; 
    }
}
double p1( double x){
    if ( x > 0 && x< 2 )
        return x/2 ;
    else
        return 0 ;
}
double p2( double x){
    if ( x > 1 && x< 3 )
        return (double) (1.5f - (x/2));
    else
        return 0 ;
}

fl::FunctionBase* ConvolutionOperation::calculate()
{
    qDebug() << Q_FUNC_INFO ;
    int n = 100 ; 
    double startRange = 0 ; 
    double endRange = 5 ; 
    double epsilon = ( endRange - startRange ) / ((double)n) ; 
    int n_discrete = 100 ; 
    int a1 = 0 ; 
    int b1 = 2 ;
    double delta = (b1 - a1) /(double)n_discrete ; 

    qDebug() <<"delta: "<<delta<<" a1: "<<a1<<" b1: "<<b1<<" epsilon: ";
    const fl::Function2D::Function2DBase * pFirst = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[0].get() ); 
    const fl::Function2D::Function2DBase * pSecond = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[1].get() ); 
    
    std::vector<double> t ; // those are my x's
    double to_insert;
    for ( double j = 1 ; j < n_discrete ; ++j ) {
        to_insert = a1 + epsilon*( j - 1/2 ) ;
        qDebug() << to_insert;
        t.push_back( to_insert ) ;
    }
    std::vector<double> result;
    std::vector<double> xs;
    double res = 0 ; 
    double first_mem= 0 ;
    double second_mem= 0 ;
    double partialResult;
    bool bOk ; 

    for ( double ss = startRange ; ss < endRange ; ss+=0.1 ) {
        xs.push_back(ss);
        for ( int iter = 1 ; iter < n_discrete ; ++iter ) {
            first_mem = /*pFirst->eval( t[iter],&bOk )*/ p1(t[iter]);
            if ( bOk ) {
                second_mem = /*pSecond->eval(ss - t[iter],&bOk)*/ p2(ss-t[iter]);
                if ( bOk ) {
                    partialResult += first_mem * second_mem ;
                }
                else{
                    qDebug() <<"Cannot calculate second_mem for:"<< iter<<" " << t[iter];
                }
            }
            else{
                qDebug() <<"Cannot calculate first_mem for:"<< iter<<" " << t[iter];
            }
            first_mem=0;
            second_mem=0;
        }

        res = delta * partialResult ;
        result.push_back(res);
        partialResult=0;
    }
    /*
    qDebug() << "xs:" << xs;
    qDebug() << "Ys:" << result ;
    */
    for ( int i = 0 ; i < xs.size() ; ++i){
        qDebug() << "f(" <<xs.at(i)<<") = " <<result.at(i);
    }
    fl::Function2D::Function2DBase * pResult = new fl::Function2D::FunctionDiscrete(xs,result,"leather");
    return pResult;
}
void ConvolutionOperation::addFunction ( fl::FunctionBase* pPtr )
{
    if ( m_functions.size() == 2 ) 
        return ; // cannot add more than 2 functions. 
    IOperation::addFunction ( pPtr );
}
