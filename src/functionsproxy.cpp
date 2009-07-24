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
#include "fl/functionMixed.h"
#include <QFile>
#include <limits>

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

FunctionsProxy::FunctionsProxy(const std::vector< QStringList >& functionsList) :
m_functionEquation(""),
m_functionDimension(-1),
m_bCustomRange(false),
m_Type(eMixed),
m_functionFileNamePath (""),
m_FunctionsVector(functionsList)
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
    
    switch ( m_Type ) {
        case eDiscrete : {
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
                        pFunc2DDiscrete = new fl::Function2D::FunctionDiscrete(xs,ys,m_functionFileNamePath.toStdString() ) ; 
                        pFunction = dynamic_cast<fl::FunctionBase *> ( pFunc2DDiscrete ); 
                    }
                    else
                    {
                        pFunc3DDiscrete = new fl::Function3D::FunctionDiscrete(xs,ys,zs,m_functionFileNamePath.toStdString() ) ; 
                        pFunction = dynamic_cast<fl::FunctionBase *> ( pFunc2DDiscrete ); 
                    }
                }
            }
        }
        case eContinous : {
            LOG("Proxying cont function");
            if ( m_functionDimension ==2 ) {
                if ( m_Type == eContinous ) {
                    LOG("Proxying 2d continous function");
                    fl::Function2D::FunctionContinous *pContFunc = new fl::Function2D::FunctionContinous(m_functionEquation.toStdString(),m_functionEquation.toStdString());
                    pContFunc->addVariable(m_functionVars.at(0).toStdString());
                    pFunction = dynamic_cast<fl::FunctionBase *> ( pContFunc ); 
                    
                }   
            }
            else if ( m_functionDimension == 3 ) {
                if ( m_Type == eContinous ) {
                    LOG("Proxying 3d continous function");
                    fl::Function3D::FunctionContinous *pContFunc = new fl::Function3D::FunctionContinous(m_functionEquation.toStdString(),m_functionEquation.toStdString());
                    pContFunc->addVariable(m_functionVars.at(0).toStdString());
                    pContFunc->addVariable(m_functionVars.at(1).toStdString());
                    pFunction = dynamic_cast<fl::FunctionBase *> ( pContFunc ); 
                }
            }
            break ;
        }
        case eMixed : {
            LOG("Proxying mixed function");
            fl::Function2D::FunctionMixed *pFuncMixed = NULL ;
            if ( ! m_FunctionsVector.empty() && m_functionFileNamePath.isEmpty() ) {
                LOG("Proxying mixed function from std::vector");
                srand(time(NULL));
                QString name = QString("Func mixed %1").arg(rand()) ; 
                pFuncMixed = new fl::Function2D::FunctionMixed(name.toStdString());
                double start, stop ; 
                QString qStart, qStop ;
                bool bOk = true ;
                bool bOk2 = true ; 
                foreach ( QStringList list, m_FunctionsVector ){
                    LOG(list);
                    if ( list.size() != 4 ) {
                        LOG("List is not correct");
                        continue ; 
                    }
                    fl::Function2D::FunctionContinous *pFuncCont = new fl::Function2D::FunctionContinous(list.at(0).toStdString(),"func tmp");
                    qStart = list.at(2) ;
                    if ( qStart == "-inf" ) {
                        start = - std::numeric_limits< double >::infinity();
                    } else if ( qStart == "+inf" ) {
                        start = std::numeric_limits< double >::infinity();
                    } else if ( qStart == "inf" ) {
                        start = std::numeric_limits< double >::infinity();
                    }
                    else
                        start = qStart.toDouble(&bOk);
                    
                    qStop = list.at(3) ;
                    if ( qStop == "-inf" ) {
                        stop = - std::numeric_limits< double >::infinity();
                    } else if ( qStop == "+inf" ) {
                        stop = std::numeric_limits< double >::infinity();
                    } else if ( qStop == "inf" ) {
                        stop = std::numeric_limits< double >::infinity();
                    }
                    else
                        stop = qStop.toDouble(&bOk2);
                    if (bOk && bOk2) {
                        LOG("adding function") ;
                        pFuncCont->addVariable(list.at(1).toStdString());
                        pFuncMixed->addFunction(pFuncCont,start,stop);
                    }
                    bOk = true ; 
                    bOk2 = true ; 
                }
                pFunction = dynamic_cast<fl::FunctionBase *> ( pFuncMixed ); 
            }
            else{
                LOG("Proxying mixed function from file");
            }
            break ;
        }
        default:
            break ; 
    }
    Q_ASSERT(pFunction!=NULL);
    return pFunction ; 
}

