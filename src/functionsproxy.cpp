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

#include "functionsproxy.h"
#include "commons.h"
#include "fl/functionbase.h"
#include "fl/functioncontinous.h"

using namespace Thesis;


FunctionsProxy::FunctionsProxy(const QString& _equation, const QStringList& _vars, int _dimension, Type type, bool bCustomRange, FunctionsProxy::CustomRangeContainer _range) :
m_functionEquation(_equation),
m_functionDimension(_dimension),
m_functionVars(_vars),
m_bCustomRange(bCustomRange),
m_CustomRange(_range),
m_Type(type)
{
}

FunctionsProxy::FunctionsProxy(const Thesis::FunctionsProxy& _rhs) :
m_functionEquation(_rhs.m_functionEquation),
m_functionDimension(_rhs.m_functionDimension),
m_functionVars(_rhs.m_functionVars),
m_bCustomRange(_rhs.m_bCustomRange),
m_CustomRange(_rhs.m_CustomRange),
m_Type(_rhs.m_Type)
{
    cLOG() ;
}


fl::FunctionBase* FunctionsProxy::proxy()
{
    cLOG() ; 
    fl::FunctionBase *pFunction = NULL ; 
    if ( m_functionDimension ==2 ) {
        if ( m_Type == eContinous ) {
            LOG("Proxying 2d continous function");
            pFunction = new fl::Function2D::FunctionContinous(m_functionEquation.toStdString(),"name");
        }   
    }
    Q_ASSERT(pFunction!=NULL);
    return pFunction ; 
}

