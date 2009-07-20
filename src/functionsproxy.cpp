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
#include "fl/functiondiscrete.h"
#include <QFile>

using namespace Thesis;


FunctionsProxy::FunctionsProxy(const QString& _equation, const QStringList& _vars, int _dimension, Type type, bool bCustomRange, FunctionsProxy::CustomRangeContainer _range) :
m_functionEquation(_equation),
m_functionDimension(_dimension),
m_functionVars(_vars),
m_bCustomRange(bCustomRange),
m_CustomRange(_range),
m_Type(type),
m_functionFileNamePath("")
{
}

FunctionsProxy::FunctionsProxy(const QString& fileName):
m_functionEquation(""),
m_functionDimension(-1),
m_bCustomRange(true),
m_Type(eDiscrete),
m_functionFileNamePath ( fileName ) 
{
}


// FunctionsProxy::FunctionsProxy(const Thesis::FunctionsProxy& _rhs) :
// m_functionEquation(_rhs.m_functionEquation),
// m_functionDimension(_rhs.m_functionDimension),
// m_functionVars(_rhs.m_functionVars),
// m_bCustomRange(_rhs.m_bCustomRange),
// m_CustomRange(_rhs.m_CustomRange),
// m_Type(_rhs.m_Type)
// {
//     cLOG() ;
// }


fl::FunctionBase* FunctionsProxy::proxy()
{
    cLOG() ; 
    fl::FunctionBase *pFunction = NULL ; 
    if ( !m_functionEquation.isEmpty() ) {
        LOG("Proxying cont function");
        if ( m_functionDimension ==2 ) {
            if ( m_Type == eContinous ) {
                LOG("Proxying 2d continous function");
                fl::Function2D::FunctionContinous *pContFunc = new fl::Function2D::FunctionContinous(m_functionEquation.toStdString(),"name");
                pContFunc->addVariable(m_functionVars.at(0).toStdString());
                pFunction = dynamic_cast<fl::FunctionBase *> ( pContFunc ); 
                
            }   
        }
        if ( m_functionDimension == 3 ) {
            if ( m_Type == eContinous ) {
                LOG("Proxying 3d continous function");
                fl::Function3D::FunctionContinous *pContFunc = new fl::Function3D::FunctionContinous(m_functionEquation.toStdString(),"name");
                pContFunc->addVariable(m_functionVars.at(0).toStdString());
                pContFunc->addVariable(m_functionVars.at(1).toStdString());
                pFunction = dynamic_cast<fl::FunctionBase *> ( pContFunc ); 
            }
        }
    }
    else {
        LOG("Proxying discrete");
        QFile file ( m_functionFileNamePath );
        if ( !file.open(QIODevice::ReadOnly) )
            LOG("Unable to open file:" << m_functionFileNamePath );
        else{
            double x,y,z;
            std::vector<double> xs  ;
            std::vector<double> ys  ;
            std::vector<double> zs  ;
            fl::Function2D::FunctionDiscrete *pFunc2DDiscrete = NULL;
            fl::Function3D::FunctionDiscrete *pFunc3DDiscrete = NULL; 
            QByteArray arr ;
            QList<QByteArray> sp ;
            bool bOk ; 
            bool bOk2 ; 
            bool bOk3 ; 
            int dimensions ;
            arr = file.readLine();
            arr.remove(arr.size()-1,1);
            if ( ! arr.isEmpty() ) {
                LOG(arr);
                sp = arr.split(' ');
                dimensions = sp.size(); 
                x = sp.at(0).toDouble(&bOk) ;
                y = sp.at(1).toDouble(&bOk2) ;
                if ( dimensions == 3 )
                    z = sp.at(2).toDouble(&bOk3);
                if ( bOk && bOk2 ) {
                    LOG("Adding point (" << x << " , " << y << " )") ; 
                    xs.push_back(x);
                    ys.push_back(y);
                    if ( dimensions == 3 )
                        zs.push_back(z);
                }
                LOG("Dimensions:" << dimensions ) ; 
                for(;;){
                    arr = file.readLine();
                    arr.remove(arr.size()-1,1);
                    LOG(arr);
                    if ( arr.isEmpty() ) 
                        break ;
                    sp = arr.split(' ');
                    x = sp.at(0).toDouble(&bOk ) ;
                    y = sp.at(1).toDouble(&bOk2 ) ;
                    if ( dimensions == 3 )
                        z = sp.at(2).toDouble(&bOk3);
                    if ( bOk && bOk2 ) {
                        LOG("Adding point (" << x << " , " << y << " )") ; 
                        xs.push_back(x);
                        ys.push_back(y);
                        if ( dimensions == 3 )
                            zs.push_back(z);
                    }
                }
                if ( dimensions == 2 ) 
                {
                    pFunc2DDiscrete = new fl::Function2D::FunctionDiscrete(xs,ys,"some func") ; 
                    pFunction = dynamic_cast<fl::FunctionBase *> ( pFunc2DDiscrete ); 
                }
                else
                {
                    pFunc3DDiscrete = new fl::Function3D::FunctionDiscrete(xs,ys,zs,"some 3d func") ; 
                    pFunction = dynamic_cast<fl::FunctionBase *> ( pFunc2DDiscrete ); 
                }
            }
        }
    }
    Q_ASSERT(pFunction!=NULL);
    return pFunction ; 
}

