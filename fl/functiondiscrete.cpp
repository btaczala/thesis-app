/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "functiondiscrete.h"
#include "functionException.h"

#include <algorithm>
#include <iterator>
#include <numeric>

#include <boost/bind.hpp>

#define EPSILON 0.0001   // Define your own tolerance
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))


double pair_first ( const std::pair<double,double> & pair) 
{
    return pair.first ;
}
struct  is_approximately {
    double x;
    public:
        is_approximately ( double what ) : x ( what ) {}
        bool operator() ( const std::pair<double,double> & _pair ) const {
            return FLOAT_EQ(x,_pair.first);
        }
};
struct comparePairsMax{
    public:
        bool operator()( const std::pair<double,double> & pair1,const std::pair<double,double> & pair2 )
        {
            if ( pair1.second < pair2.second ) 
                return true ; 
            return false ; 
        }
};
struct comparePairsMax2{
public:
	bool operator()( const std::pair<double,double> & pair1,const std::pair<double,double> & pair2 )
	{
		if ( pair1.first < pair2.first ) 
			return true ; 
		return false ; 
	}
};
struct comparePairsMin{
    public:
        bool operator()( const std::pair<double,double> & pair1,const std::pair<double,double> & pair2 )
        {
            if ( pair1.second > pair2.second ) 
                return true ; 
            return false ; 
        }
};
struct comparePairsMin2{
public:
	bool operator()( const std::pair<double,double> & pair1,const std::pair<double,double> & pair2 )
	{
		if ( pair1.first < pair2.first ) 
			return true ; 
		return false ; 
	}
};

fl::Function2D::FunctionDiscrete::FunctionDiscrete(const std::vector< double > & _x, const std::vector< double > & _y, const std::string& _functionName): Function2DBase(_functionName)
{
    m_Type = eDiscrete;
    for( size_t i = 0 ; i< _x.size() ; ++i ) 
        m_xy.push_back(std::make_pair( _x.at(i),_y.at(i) ) );
}

fl::Function2D::FunctionDiscrete::~FunctionDiscrete()
{
}
double fl::Function2D::FunctionDiscrete::eval( double _xs, bool * pCorrect ) const
{
    if ( m_xy.size() == 0 ) 
        return -1 ; 
    DomainRangeIterator it  = std::find_if ( m_xy.begin(), m_xy.end(), is_approximately(_xs) ) ; 
    if ( it != m_xy.end() ) {
        *pCorrect = true ; 
        return it->second ;
    } else {
        *pCorrect = false ; 
        return -1 ; 
    }
}

double fl::Function2D::FunctionDiscrete::max() const 
{
    if ( m_xy.size() == 0 ) 
        return -1 ; 
    DomainRangeIterator it = std::max_element( m_xy.begin(), m_xy.end(), comparePairsMax() );
    //if ( it != m_xy.end() ) 
    return it->second ; 
}
double fl::Function2D::FunctionDiscrete::min() const 
{
    if ( m_xy.size() == 0 ) 
        return -1 ; 
    DomainRangeIterator it = std::min_element( m_xy.begin(), m_xy.end(), comparePairsMax() );
//     if ( it != m_xy.end() ) 
    return it->second ; 
}
double fl::Function2D::FunctionDiscrete::xMin() const {
	
	if ( m_xy.size() == 0 ) 
		return -1 ; 
	DomainRangeIterator it = std::min_element( m_xy.begin(), m_xy.end(), comparePairsMin2() );
	return it->first; 
}
double fl::Function2D::FunctionDiscrete::xMax() const {

	if ( m_xy.size() == 0 ) 
		return -1 ; 
	DomainRangeIterator it = std::max_element( m_xy.begin(), m_xy.end(), comparePairsMax2() );
	return it->first ; 
}

fl::Function3D::FunctionDiscrete::FunctionDiscrete( const std::vector< double >& _x, const std::vector< double >& _y, const std::vector< double >& _z, const std::string& _functionName ) : Function3DBase( _functionName )
{
	m_Type = eDiscrete;
    if ( _x.size() != _y.size() || _x.size() != _z.size() )
        throw fl::FunctionException("Unable to construct function3D with incorect domain, range") ; 
    for ( unsigned int i = 0 ; i < _x.size() ; ++i ) 
    {
        m_xyz.push_back( boost::make_tuple(_x.at(i), _y.at(i), _z.at(i) ) ) ;
    }
}

double fl::Function3D::FunctionDiscrete::max() const 
{
    double dMax = -1 ; 
    if ( m_xyz.size() == 0 ) 
        throw fl::FunctionException("Unable to get max() where no values") ;
    for ( DomainRangeIterator it = m_xyz.begin() ; it != m_xyz.end() ; ++it ) 
    {
        if ( it == m_xyz.begin() ) 
            dMax = it->get<2>() ;
        else
        {
            if ( dMax < it->get<2>() )
                dMax = it->get<2>() ; 
        }
    }
	return dMax; 
}

double fl::Function3D::FunctionDiscrete::min() const 
{
	double dMin = -1 ; 
    if ( m_xyz.size() == 0 ) 
        throw fl::FunctionException("Unable to get max() where no values") ;
    for ( DomainRangeIterator it = m_xyz.begin() ; it != m_xyz.end() ; ++it ) 
    {
        if ( it == m_xyz.begin() ) 
            dMin = it->get<2>() ;
        else
        {
            if ( dMin > it->get<2>() )
                dMin = it->get<2>() ; 
        }
    }
    return dMin; 
}

double fl::Function3D::FunctionDiscrete::eval( double x,double y )
{
	double eval  = -1 ; 
    if ( m_xyz.size() == 0 ) 
        throw fl::FunctionException("Unable to get max() where no values") ;
    for ( DomainRangeIterator it = m_xyz.begin() ; it != m_xyz.end() ; ++it ) 
    {
        if ( it->get<0>() == x && it->get<1>() == y ) {
            eval = it->get<2>();
            break ; 
        }
    }
    return eval; 
}

double fl::Function2D::FunctionDiscrete::xStartWhereIntegratingMakesSense() const 
{
    return xMin();
}

double fl::Function2D::FunctionDiscrete::xStopWhereIntegratingMakesSense() const 
{
    return xMax();
}
fl::Function2D::FunctionContinous * fl::Function2D::FunctionDiscrete::approximate( ) const
{
    static const int m = 5 ; 
    return NULL ; 
}
bool sort_pred(const fl::Function2D::FunctionDiscrete::Point &x, const fl::Function2D::FunctionDiscrete::Point & x2){
    return x.first < x.second ; 
}
double fl::Function2D::FunctionDiscrete::integrate( double start, double stop,double dStep ) const 
{
    DomainRange sorted ( m_xy.size());
    std::copy(m_xy.begin(),m_xy.end(),sorted.begin());
    std::sort(sorted.begin(),sorted.end(),sort_pred);
    // sort with x's
    double a ; 
    double b ; 
    double fa ; 
    double fb ;
    const double t = 2.0f ; 
    double result = 0; 
    DomainRangeIterator it = sorted.begin();
    DomainRangeIterator itTmp ;
    const DomainRangeIterator itEnd = sorted.end();

    for ( it ; it != itEnd ; ++it  ){
        a = it->first ; 
        itTmp= it+1;
        if ( itTmp == itEnd){
            continue ; 
        }
        b = itTmp->first; 
        fa = it->second ; 
        fb = itTmp->second;

        result += (b-a) * ((fa+fb)/t);

    }

    /*for ( double iterator = start ; iterator <= stop ; iterator += dStep ) {
        a = iterator ; 
        b = iterator + dStep ; 
        fa = eval(a,&bOk);
        if ( bOk ) 
        {
            fb = eval ( b, &bOk );
            if ( bOk ){
                result += (b-a) * ((fa+fb)/t);
            }
        }
    }*/
    return result ; 
}