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

fl::FunctionBase* ConvolutionOperation::calculate()
{
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
    std::vector<double> t ; 
    for ( int iter = 0 ; iter < n_discrete ; ++iter ) {
        double to_insert = a1 + delta*( iter-1/2 ) ;
        t.push_back( to_insert ) ;
    }
    std::vector<double> result;
    double res = 0 ; 
    double temp = 0 ; 
    bool bOk ; 
    for ( double ss = startRange ; ss < endRange ; ++ss ) {    
        for ( int iter = 0 ; iter < n_discrete ; ++iter ) {
            temp = pFirst->eval( t[iter],&bOk );
            if ( bOk ) {
                temp *= pSecond->eval(ss - t[iter],&bOk);
                if ( bOk ) {
                    ;
                }
            }
        }
        res = delta * temp ; 
        result.push_back(res);
    }
}
void ConvolutionOperation::addFunction ( fl::FunctionBase* pPtr )
{
    if ( m_functions.size() == 2 ) 
        return ; // cannot add more than 2 functions. 
    IOperation::addFunction ( pPtr );
}
