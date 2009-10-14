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

#include "convolutionadd.h"

#include "fl/function2dbase.h"
#include "fl/functiondiscrete.h"
#include <QDebug>

fl::FunctionBase* ConvolutionAdd::calculate()
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
    
    double f1XStart  = pFirst->xStartWhereIntegratingMakesSense() ; 
    double f2XStart  = pSecond->xStartWhereIntegratingMakesSense() ; 
    
    qDebug() << "starts" << f1XStart << " " << f2XStart ;
    
    double f1XStop  = pFirst->xStopWhereIntegratingMakesSense() ; 
    double f2XStop  = pSecond->xStopWhereIntegratingMakesSense() ;
    qDebug() << "stops " << f1XStop  << " " << f2XStop ;
    
    
    startRange = f1XStart + f2XStart ; 
    endRange = f1XStop+f2XStop ; 
    
    qDebug() << "Meaning full range [  "<< startRange << " , " << endRange<<" ]"; 

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
    for ( double sIter = startRange ; sIter < endRange+0.5 ; sIter +=0.1){
        x = sIter ; 
        double pp2=0;
        double pp1=0;
        for ( int jIter = 0 ; jIter < n_discrete;++jIter ){
            //int realIter = t.size() - jIter ; 
            pp1 = pFirst->eval( t[jIter],&bOk );
            if ( bOk ) {
                pp2 = pSecond->eval(sIter - t[jIter],&bOk);
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
    qDebug() << ys ; 
    fl::Function2D::Function2DBase * pResult = new fl::Function2D::FunctionDiscrete(xs,ys,"leather");
    return pResult;
}

