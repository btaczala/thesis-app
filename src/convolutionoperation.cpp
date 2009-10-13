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
    if ( x> 0 && x< 2 )
        return x/2 ; 
    return 0;
}
double p2( double x){
    if ( x> 1 && x< 3 )
        return 1.5f - x/2 ; 
    return 0;
}
double pp ( double x){
    double y =0 ; 
    double temp =0 ; 
    double ppp1 ; 
    double ppp2 ; 
    QString stringgg = QString("1/50 * pp[%1] = ").arg(x);
    QString stringgg2="";
    for ( double i = 2L ; i > 0 ; i-= 0.02){
        ppp1 = p1(i);
        ppp2 = p2(x-i);
        stringgg2 += QString("p1(%1)p2(%2-%3)\n").arg(i).arg(x).arg(i);
        temp = ppp1*ppp2 ;
        y+= temp ; 
    }
    y *= 0.02f ; 
    qDebug() << stringgg << stringgg2;
    return y; 
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
    const fl::Function2D::Function2DBase * pFirst = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[0].get() ); 
    const fl::Function2D::Function2DBase * pSecond = dynamic_cast<const fl::Function2D::Function2DBase*>( m_functions[1].get() ); 
    
    std::vector<double> t ; // those are my x's
    double to_insert;
    for ( double j = 1 ; j < n_discrete+1 ; ++j ) {
        to_insert = j - 0.5f; 
        to_insert *=delta ; 
        to_insert+= a1 ; 
        t.push_back( to_insert ) ;
    }
    qDebug() << " Xs: [" << t ;
    std::vector<double> xs ; 
    std::vector<double> ys ; 
    std::vector<double> ys2 ; 
    double partialResult=0;
    bool bOk ; 
    double x=0; 
    double y=0; 
    for ( double sIter = 0 ; sIter < 6 ; sIter +=0.1){
        x = sIter ; 
        double pp2=0;
        double pp1=0;
        for ( int jIter = 1 ; jIter < n_discrete+1;++jIter ){
            int realIter = t.size() - jIter ; 
            pp1 = pFirst->eval( t[realIter],&bOk );
            if ( bOk ) {
                pp2 = pSecond->eval(sIter - t[realIter],&bOk);
                if ( bOk ) {
                    y += pp1 * pp2 ;
                }
            }
        }
        y*= (double)delta;
        xs.push_back(x);
        ys.push_back(y);
        ys2.push_back( pp( sIter ) );
        x=0;
        y=0;
    }
    qDebug() << ys ; 
    //fl::Function2D::Function2DBase * pResult = new fl::Function2D::FunctionDiscrete(xs,ys,"leather");
    fl::Function2D::Function2DBase * pResult = new fl::Function2D::FunctionDiscrete(xs,ys2,"leather");

    return pResult;
}
void ConvolutionOperation::addFunction ( fl::FunctionBase* pPtr )
{
    if ( m_functions.size() == 2 ) 
        return ; // cannot add more than 2 functions. 
    IOperation::addFunction ( pPtr );
}

