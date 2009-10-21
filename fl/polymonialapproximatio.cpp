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

#include "polymonialapproximatio.h"
#include <string>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>
#include <utility>
USING_PART_OF_NAMESPACE_EIGEN

using namespace std ; 
using namespace fl::Function2D;


fl::Function2D::PolymonialApproximation::PolymonialApproximation ( int m, const Function2D::FunctionDiscrete::DomainRange & _range) : 
fl::Function2D::IApproximation( _range ),
_m ( m )
{
}


fl::Function2D::FunctionContinous* fl::Function2D::PolymonialApproximation::approximate() const 
{
    fl::Function2D::FunctionContinous *pFunction ; 
    
    string ret ; 
    if ( ! ( (int)m_range.size() > _m+1 ) ) {
        return NULL;
    }
    vector<double> xs ; 
    vector<double> ys ; 
    for ( unsigned int i = 0 ; i < m_range.size() ; ++i ) {
        xs.push_back(m_range.at(i).first);
        ys.push_back(m_range.at(i).second);
    }
    // znajdź wartość sum Sk
    // s_k = sum ( i=1, n) { (x_i)^k } 
    const int realM = _m + 1; 
    vector<double > Sk ; 
    MatrixXd S( realM,realM ) ; 
    vector<double > tm ; 
    double var =0 ; 
    
    for ( int k = 0 ; k < 2 * realM ; ++k ) {
        for ( unsigned int j = 0 ; j < xs.size() ; ++j ) {
            var += pow(xs.at(j),k);
        }
        Sk.push_back(var);
        var = 0 ; 
    }
    for ( int cross = 0 ; cross < realM ; ++cross ) {
        for ( int j = 0 ; j < realM ; ++j ){
            S( j , cross ) = Sk.at(cross+j) ; 
        }
    }
    MatrixXd T(realM,1) ; 
    for ( int k = 0 ; k < realM ; ++k ) {
        for ( unsigned int j = 0 ; j < xs.size() ; ++j ) {
            var += pow(xs.at(j),k)*ys.at(j);
        }
        T(k,0) = var ; 
        var = 0 ; 
    }
    //cout << S << endl ; 
    //cout << T << endl ; 
    MatrixXd A(realM,1); 
    MatrixXd invS = S.inverse();
    A = invS * T ;
    //cout << A ;
    stringstream stream ;
    for ( int j = 0 ; j < A.rows() ; ++j ) 
        stream << "a("<< j << ") =" << A(j,0) <<endl ;
    cout << stream.str();
    stringstream result ; 
    for ( int i = 0 ; i < A.rows() ; ++ i ) {
        result << A(i,0)<< "*pow(x," << i <<")";
        if ( i != A.rows() -1 ) 
            result << " + " ;
    }
	pFunction = new fl::Function2D::FunctionContinous();
    pFunction->setEquation(result.str());
    pFunction->addVariable("x");
    return pFunction;
}
