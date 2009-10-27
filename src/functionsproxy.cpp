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
#include "newfunctionmixeddialog.h"
#include <QFile>
#include <limits>

using namespace Thesis;

QByteArray removeJunk( const QString & bArray){
    QByteArray arr ; 
    char sign ; 
    for ( int i = 0; i< bArray.size() ; ++i ){
        sign = bArray.at(i).toAscii();
        if ( isdigit(sign) || sign =='-' || sign =='.' || isalpha(sign) || sign =='(' || sign ==')' || sign == '+' || sign == '*' || sign == '/' || sign == '<' || sign == '=' || sign == '>' ){
            arr += sign ; 
        }
    }
    return arr ; 
}

QStringList Helpers::parseOneFunction ( const QString& str)
{
    /*
        str has to have format sin(x),x,0 < x < 2
    */
    QStringList toRet ; 
    QStringList parsed = str.split(',') ;
    if ( parsed.size() != 3 ) {
        qDebug() << "Error while parsing one function!" ; 
        return QStringList() ; 
    }
    toRet << removeJunk( parsed.at(0) ) << removeJunk( parsed.at(1) )<< parseRange( parsed.at(2),parsed.at(1)) ; 
    qDebug() <<  toRet ;
    return toRet ; 
}
QStringList Helpers::parseRange(const QString & str, const QString & varName )
{
    // parse 0<x<2 
    QStringList toRet= str.split(' ',QString::SkipEmptyParts);
    toRet.removeAll(varName);
    QStringList damn ; 
    damn << toRet.at(0);
    damn << toRet.at(1);
    QString g = toRet.at(2);
    if ( g == "<"){
        g = ">";
    }
    else if ( g == ">"){
        g = "<";
    }
    else if ( g == "<="){
        g = ">=";
    }
    else if ( g == ">="){
        g = "<=";
    }
    damn << toRet.at(3);
    damn << g ; 

    return damn ;
}


fl::Function2D::FunctionMixed::Operator stringToOperator( const QString & str){
    if ( str == "<")
        return fl::Function2D::FunctionMixed::eLess;
    else if ( str == "<=")
        return fl::Function2D::FunctionMixed::eLessEqual;
    else if ( str == ">")
        return fl::Function2D::FunctionMixed::eGreater;
    else if ( str == ">=")
        return fl::Function2D::FunctionMixed::eGreaterEqual;
    else 
        return fl::Function2D::FunctionMixed::eWTF;
}


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

FunctionsProxy::FunctionsProxy(const QString& fileName, Type type ):
m_functionEquation(""),
m_functionDimension(-1),
m_bCustomRange(true),
m_Type(type),
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
    if ( m_FunctionsVector.empty() ) 
        throw std::logic_error("FunctionsProxy::FunctionsProxy(const std::vector< QStringList >& functionsList)");
        
}

fl::FunctionBase* FunctionsProxy::proxy()
{
    cLOG() ; 
    fl::FunctionBase *pFunction = NULL ; 
    
    switch ( m_Type ) {
        case eDiscrete : {
            return proxyDiscrete();
            break ; 
        }
        case eContinous : {
            return proxyContinous();
            break ;
        }
        case eMixed : {
            return proxyMixed() ; 
            break ;
        }
        default:
            break ; 
    }
    Q_ASSERT(pFunction!=NULL);
    return pFunction ; 
}

fl::FunctionBase* FunctionsProxy::proxyDiscrete()
{
    fl::FunctionBase * pFunction = NULL ; 
    cLOG() ;
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
        if ( !arr.contains("discrete")){
            LOG("This shouldn't happen. This is not discrete function");
            return NULL ; 
        }
        arr = file.readLine();
        arr.remove(arr.size()-1,1);
        if ( ! arr.isEmpty() ) {
            //LOG(arr);	
            sp = arr.split(' ');
            dimensions = sp.size(); 
            QByteArray num1 =  removeJunk( sp.at(0) );
            QByteArray num2 =  removeJunk( sp.at(1) );
            x = num1.toDouble(&bOk) ;
            y = num2.toDouble(&bOk2) ;
            if ( dimensions == 3 )
                z = sp.at(2).toDouble(&bOk3);
            if ( bOk && bOk2 ) {
                //LOG("Adding point (" << x << " , " << y << " )") ; 
                xs.push_back(x);
                ys.push_back(y);
                if ( dimensions == 3 )
                    zs.push_back(z);
            } else {
                LOG("Unable to add!!");
            }
            //LOG("Dimensions:" << dimensions ) ; 
            for(;;){
                arr = file.readLine();
                arr.remove(arr.size()-1,1);
                //LOG(arr);
                if ( arr.isEmpty() ) 
                    break ;
                sp = arr.split(' ');
                num1 =  removeJunk( sp.at(0) );
                num2 =  removeJunk( sp.at(1) );
                x = num1.toDouble(&bOk) ;
                y = num2.toDouble(&bOk2) ;
                if ( dimensions == 3 )
                    z = sp.at(2).toDouble(&bOk3);
                if ( bOk && bOk2 ) {
                    //LOG("Adding point (" << x << " , " << y << " )") ; 
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
    return pFunction ; 
}

fl::FunctionBase* FunctionsProxy::proxyContinous()
{
    fl::FunctionBase * pFunction = NULL ;
    cLOG() ;
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
    return pFunction ; 
}

fl::FunctionBase* Thesis::FunctionsProxy::proxyMixed()
{
    fl::FunctionBase * pFunction = NULL ;
    cLOG() ;
    fl::Function2D::FunctionMixed *pFuncMixed = NULL ;
    if ( ! m_FunctionsVector.empty() ) {
        LOG("Proxying mixed function from std::vector");
        srand(time(NULL));
        QString name = QString("Func mixed %1").arg(rand()) ; 
        if ( !m_functionFileNamePath.isEmpty() )
            name = m_functionFileNamePath;
        if ( !m_functionFileNamePathTmp.isEmpty())
            name = m_functionFileNamePathTmp;
        pFuncMixed = new fl::Function2D::FunctionMixed(name.toStdString());
        double start, stop ; 
        QString qStart, qStop, qStartOp,qStopOp;
        bool bOk = true ;
        bool bOk2 = true ; 
        foreach ( QStringList list, m_FunctionsVector ){
            LOG(list);
            if ( list.size() != 6 ) {
                LOG("List is not correct");
                continue ; 
            }
            fl::Function2D::FunctionContinous *pFuncCont = new fl::Function2D::FunctionContinous(list.at(0).toStdString(),"func tmp");
            // 2 arg. start range
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

            // 3. Operator for start range ( less, greater, equal ) 
            fl::Function2D::FunctionMixed::Operator op1 = stringToOperator(list.at(3));
            qStop = list.at(4) ;

            if ( qStop == "-inf" ) {
                stop = - std::numeric_limits< double >::infinity();
            } else if ( qStop == "+inf" ) {
                stop = std::numeric_limits< double >::infinity();
            } else if ( qStop == "inf" ) {
                stop = std::numeric_limits< double >::infinity();
            }
            else
                stop = qStop.toDouble(&bOk2);

            fl::Function2D::FunctionMixed::Operator op2 = stringToOperator(list.at(5));
            
            if (bOk && bOk2) {
                LOG("adding function") ;
                pFuncCont->addVariable(list.at(1).toStdString());
                pFuncMixed->addFunction(pFuncCont,start,op1,stop,op2);
            }
            bOk = true ; 
            bOk2 = true ; 
        }
        pFunction = dynamic_cast<fl::FunctionBase *> ( pFuncMixed ); 
    }
    else{
        LOG("Proxying mixed function from file");
        /// from file 

        QList<QByteArray> sp ;
        QByteArray tmp ; 
        std::vector<QStringList> functionVector; 
        QStringList oneFunction ; 
        QFile file ( m_functionFileNamePath );
        if ( !file.open(QIODevice::ReadOnly ) ){
            LOG("Unable to open file" << m_functionFileNamePath);
        } else {
            QByteArray arr ; 
            arr = file.readLine();
            if ( !arr.contains("mixed") ) {
                LOG("This is not mixed function?");
            }
            else{
                for (;;) {
                    arr = file.readLine();
                    if ( arr.isEmpty())
                        break ; 
                    oneFunction = Helpers::parseOneFunction( arr ) ; 
                    LOG(oneFunction);
                    functionVector.push_back(oneFunction);
                    oneFunction.clear();
                    arr="";
                    sp.clear();
                }
                
                file.close();
                m_FunctionsVector = functionVector;
                m_functionFileNamePathTmp = m_functionFileNamePath; 
                m_functionFileNamePath.clear();
                return proxy() ; 
            }   
        }
    }
    return pFunction ; 
}
