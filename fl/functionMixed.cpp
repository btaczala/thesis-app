
#include "functionMixed.h"

fl::Function2D::FunctionMixed::FunctionMixed( const std::string & _functionName ) :
fl::Function2D::Function2DBase(_functionName)
{
}

void fl::Function2D::FunctionMixed::addFunction( fl::Function2D::Function2DBase * pFunction, double start, double stop )
{
	FunctionRange frFunction ; 
	frFunction.m_spFunction.reset(pFunction);
	frFunction.m_start = start ; 
	frFunction.m_stop = stop ; 
	m_Functions.push_back(frFunction);
}