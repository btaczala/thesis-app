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

#include "iapproximation.h"
#include <limits>
#include <fl/function2dbase.h>
#include <fl/functioncontinous.h>
fl::Function2D::IApproximation::IApproximation(const Function2D::FunctionDiscrete::DomainRange & _range) : m_range( _range )
{
}
fl::Function2D::IApproximation::~IApproximation()
{
}

fl::Function2D::FunctionMixed * fl::Function2D::IApproximation::cropFunction( fl::Function2D::Function2DBase * pFunc, double xstart, double xstop )
{
	fl::Function2D::FunctionMixed *pFun = new fl::Function2D::FunctionMixed("cropped");
	fl::Function2D::FunctionContinous *pOne = new fl::Function2D::FunctionContinous("0");
	pOne->addVariable("x");
	fl::Function2D::FunctionContinous *pTwo= new fl::Function2D::FunctionContinous("0");
	pTwo->addVariable("x");

	double d = pFunc->integrate(xstart,xstop,0.01);
	fl::Function2D::FunctionContinous *pC = dynamic_cast<fl::Function2D::FunctionContinous *>(pFunc) ;
	std::stringstream aa ; 
	aa << "(" << pC->equation() << ")/" << d ; 
	pC->setEquation(aa.str());
	pFun->addFunction(pC,xstart,fl::Function2D::FunctionMixed::eGreaterEqual,xstop,fl::Function2D::FunctionMixed::eGreaterEqual);
	pFun->addFunction(pOne,-1* std::numeric_limits<double>::infinity(), fl::Function2D::FunctionMixed::eGreater, xstart, fl::Function2D::FunctionMixed::eGreater ) ; 
	pFun->addFunction(pTwo,xstop, fl::Function2D::FunctionMixed::eGreater, std::numeric_limits<double>::infinity(), fl::Function2D::FunctionMixed::eGreater ) ; 
	return pFun ; 
}
