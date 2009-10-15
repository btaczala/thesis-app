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

#include "functioncontinous.h"
#include "functionException.h"
#include <muParserError.h>

fl::Function2D::FunctionContinous::FunctionContinous(const std::string& _functionEquation, const std::string& _functionName) : 
fl::FunctionContinousBase(_functionEquation), 
fl::Function2D::Function2DBase(_functionName)
{
	m_Type = eContinous ;
}

void fl::Function2D::FunctionContinous::addVariable(const std::string & varName )
{
	if ( m_VariableMap.size() == 0 ) {
		fl::FunctionContinousBase::addVariable(varName);
	}
}

double fl::Function2D::FunctionContinous::eval(double point, bool *pCorrect) const
{
    double toRet = -1; 
    try{
		std::map<std::string, double>::iterator it = m_VariableMap.begin() ;
		it->second = point ; 
		toRet = m_pParser->Eval() ;
        *pCorrect = true ; 
        if ( !m_bMinMaxEval ) {
            m_iMax = toRet ;
            m_iMin = toRet ;
             
            m_bMinMaxEval = true ;
        }
        else{
            if( toRet > m_iMax ) 
                m_iMax = toRet ; 
            if ( toRet < m_iMin ) 
                m_iMin = toRet ; 
        }
    }
    catch ( mu::Parser::exception_type & e ) {
		e;
        *pCorrect = false ; 
    }
    return toRet ; 
}

fl::Function2D::Function2DBase* fl::Function2D::FunctionContinous::integrate(double start, double stop)
{
    //TODO:implement ?!
	return NULL ; 
}

double fl::Function2D::FunctionContinous::max() const 
{
	return m_iMax; 
}

double fl::Function2D::FunctionContinous::min() const 
{
	return m_iMin;
}

fl::Function3D::FunctionContinous::FunctionContinous( const std::string & _equation /*= ""*/, const std::string & functionName/*= "" */ ) :
fl::FunctionContinousBase(_equation), 
fl::Function3D::Function3DBase(functionName)
{
	m_Type = eContinous ;
}

void fl::Function3D::FunctionContinous::addVariable( const std::string & varName )
{
    //TODO:implement ?! 
}

double fl::Function3D::FunctionContinous::eval( double x, double y )
{
    //TODO:implement ?!
	return -1 ; 
}

fl::Function3D::Function3DBase* fl::Function3D::FunctionContinous::integrate( double start, double stop )
{
    //TODO:implement ?!
	return NULL; 

}

double fl::Function3D::FunctionContinous::max() const 
{
    //TODO:implement ?!
	return -1 ; 

}

double fl::Function3D::FunctionContinous::min() const 
{
    //TODO:implement ?!
	return -1 ; 

}

double fl::Function2D::FunctionContinous::xStartWhereIntegratingMakesSense() const 
{
    //TODO:implement ?!
    return -1 ; 
}

double fl::Function2D::FunctionContinous::xStopWhereIntegratingMakesSense() const 
{
    //TODO:implement ?!
    return -1 ;
}
