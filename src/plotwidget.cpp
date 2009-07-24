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
    with this program; if not, write to the Free Software Foundationtal lines, blank lines, lines with comments, nonbla, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include "plotwidget.h"
#include "commons.h"
#include "kplotwidget.h"
#include "kplotobject.h"

#include <qwt3d_surfaceplot.h>

#include <QScrollBar>
#include <QProgressDialog>

#include "fl/functionbase.h"
#include "fl/function2dbase.h"
#include "fl/functionException.h"
#include <QVBoxLayout>

using namespace Thesis::UI;

static int g_colors[] = {Qt::white,Qt::green, Qt::darkRed, Qt::darkGreen, Qt::blue, Qt::darkBlue, Qt::cyan, Qt::darkCyan};

QColor randomColor()  {
    srand(time(NULL));
    return QColor(rand()%32*8,rand()%32*8,rand()%32*8);
}

PlotWidgetProxy::PlotWidgetProxy(QWidget* pParent ) : 
m_pParent(pParent),
m_pKPlotWidget( new KPlotWidget() ),
m_xMin(-1),
m_xMax(3),
m_yMin(-2),
m_yMax(2),
m_pCalcThread(new CalculatingThread()),
m_pLastAddedFunction(NULL)
{
    cLOG();
    
    connect ( m_pCalcThread.get(),SIGNAL(finished()),this,SLOT(threadEnded()));
    
    m_pKPlotWidget->setAntialiasing( true );
    m_pKPlotWidget->setLimits( m_xMin,m_xMax,m_yMin,m_yMax);
    
}
PlotWidgetProxy::~PlotWidgetProxy()
{
    cLOG();
    m_pCalcThread->freeLists();
    FunctionsPlotMapType::iterator it = m_PlotsFunctions.begin() ; 
    FunctionsPlotMapType::iterator itEnd = m_PlotsFunctions.end() ; 
    for ( it ; it != itEnd ; ++ it ) {
        delete it.key() ; 
    }
}

QWidget* PlotWidgetProxy::widget()
{
    cLOG();
    Q_ASSERT(m_pKPlotWidget.get() != NULL ) ; 
    return m_pKPlotWidget.get();
}

void PlotWidgetProxy::addFunction(fl::FunctionBase* pFunction, const QColor & color )
{
    cLOG();
    
    KPlotObject *pPlotObject = NULL ; 
    fl::Function2D::Function2DBase *pFunction2D = dynamic_cast<fl::Function2D::Function2DBase *>( pFunction ); 
    Q_ASSERT(pFunction2D != NULL ) ; 
    QColor fnColor ; 
    if ( ! color.isValid() )
        fnColor = randomColor();
    else
        fnColor = color ; 
    if ( pFunction2D->type() == fl::FunctionBase::eDiscrete ) 
        pPlotObject = new KPlotObject( fnColor, KPlotObject::Points, 2 );
    else if ( pFunction2D->type() == fl::FunctionBase::eContinous || pFunction2D->type() == fl::FunctionBase::eMixed ) 
        pPlotObject = new KPlotObject( fnColor, KPlotObject::Lines, 2 );
    m_pLastAddedFunction = pFunction ; 
    m_PlotsFunctions.insert(pFunction,pPlotObject);
    
    m_pKPlotWidget->addPlotObject(pPlotObject);
    
    m_pCalcThread->setFunctions(m_PlotsFunctions);
    m_pCalcThread->setLimits(m_xMin,m_xMax,m_yMin,m_yMax);
    m_pCalcThread->setWorkType(CalculatingThread::eAdd);
    
    m_pCalcThread->start();
    
    // RUN RUN RUN
}

void Thesis::UI::PlotWidgetProxy::deleteFunction(const QString& fID)
{
    cLOG();
    FunctionsPlotMapType::iterator it = m_PlotsFunctions.begin() ; 
    FunctionsPlotMapType::iterator itEnd = m_PlotsFunctions.end() ; 
    for ( it ; it != itEnd ; ++ it ) {
        if ( it.key()->name() == fID.toStdString() ) {
            m_pKPlotWidget->removeObject(it.value());
        }
    }
    m_pKPlotWidget->update();

}


void Thesis::UI::PlotWidgetProxy::changeRange(double xstart, double xstop, double ystart, double ystop)
{   
    m_xMin = xstart; 
    m_xMax = xstop; 
    m_yMin = ystart; 
    m_yMax = ystop; 
    
    foreach( KPlotObject *pObject , m_pKPlotWidget->plotObjects() ) {
        pObject->clearPoints();
    }
    m_pCalcThread->setFunctions(m_PlotsFunctions);
    m_pCalcThread->setLimits(m_xMin,m_xMax,m_yMin,m_yMax);
    m_pCalcThread->setWorkType(CalculatingThread::eRecalculate);
    
    m_pKPlotWidget->setLimits(m_xMin,m_xMax,m_yMin,m_yMax);
    
    m_pCalcThread->start() ; 
    
//     LOG(" ( " << xstart << " , " << xstop << " x ( " << ystart << " , " << ystop << " ) " ) ; 
//     if ( m_PlotType == ePlot3D ) 
//     {
//         LOG("unable to change 3d plot range");
//         return ;
//     }
//     m_xMax = xstop ; 
//     m_xMin = xstart ;
//     m_yMax = ystop ; 
//     m_yMin = ystart ; 
//     
//     m_pKPlotWidget->setLimits( m_xMin,m_xMax,m_yMin,m_yMax);
//     
//     // RUN RUN RUN 
//     QProgressDialog dlg ( "calc","abort",m_xMin,m_xMax * m_PlotsFunctions.size() );
//     FunctionsPlotMapType::iterator it = m_PlotsFunctions.begin() ; 
//     fl::Function2D::Function2DBase *p2DFunc = NULL; 
//     KPlotObject *pPlotObject = NULL ; 
//     double val;
//     bool bOk ; 
//     int counter = 1 ; 
//     while( it != m_PlotsFunctions.end()) {
//         pPlotObject = it.key();
//         p2DFunc = dynamic_cast<fl::Function2D::Function2DBase *> ( it.value() );
//         Q_ASSERT ( pPlotObject != NULL && p2DFunc != NULL ) ; 
//         if ( p2DFunc->type() == fl::FunctionBase::eDiscrete ) 
//             continue ; 
//         pPlotObject->clearPoints() ;
//         for ( double i = m_xMin ; i < m_xMax ; i += 0.01 ) {
//             LOG(i);
//             val = p2DFunc->eval(i,&bOk);
//             dlg.setValue(i * counter);
//             if ( bOk ) {
//                 LOG("Adding points : ("<<i<<" , " << val<< ")") ; 
//                 pPlotObject->addPoint(i,val);  
//             }
//         }
//         ++counter;
//         ++it ; 
//     }
}

void Thesis::UI::PlotWidgetProxy::threadEnded()
{
    cLOG();
    if ( m_pCalcThread->workType() == CalculatingThread::eAdd ) {
        FunctionInfo info ; 
        info._fId = QString( m_pLastAddedFunction->name().c_str());
        info._fColor = m_PlotsFunctions[m_pLastAddedFunction]->brush().color();
        LOG("Emit functionAdded");
        emit functionAdded(info);
    }
    else{
        LOG("Recalculating over, no adding functions");
    }
    m_pKPlotWidget->update();
}


void Thesis::UI::CalculatingThread::setLimits(double x, double x1, double y, double y1)
{
    
    cLOG();
    m_mutex.lock();
    m_xMin = x; 
    m_xMax = x1;
    m_yMin = y;
    m_yMax = y1;
    m_mutex.unlock();
}

Thesis::UI::CalculatingThread::CalculatingThread() : QThread()
{
}

Thesis::UI::CalculatingThread::~CalculatingThread()
{
    wait();
    m_functionToCalculate.clear();
    m_plotsCalculated.clear();
}

void Thesis::UI::CalculatingThread::run()
{
    m_mutex.lock();
    
    if ( m_WorkType == eAdd ) {
        LOG("Adding a function");
        if ( m_functionToCalculate.size() == 0 ) {
            LOG("No functions is container");
            return ;
        }
        fl::FunctionBase *pFunction = m_functionToCalculate.at(m_functionToCalculate.size()-1);
        if ( pFunction->dimensions() == 2 ) 
        {
            fl::Function2D::Function2DBase *pFunction2D = dynamic_cast<fl::Function2D::Function2DBase *>( pFunction ); 
            Q_ASSERT(pFunction2D != NULL ) ; 
            KPlotObject *pPlotObject = m_plotsCalculated.at(m_plotsCalculated.size()-1);
            bool bOk ; 
            double value ; 
            double start ;
            double stop ;
            if ( pFunction2D->type() == fl::FunctionBase::eDiscrete ) {
                // add all values
                start = pFunction2D->min();
                stop = pFunction2D->max();
            } else {
                start = m_xMin ;
                stop = m_xMax ;
            }
            for ( double t=start; t<=stop; t+=0.01 ) {
                value = pFunction2D->eval(t,&bOk);
                if ( bOk ) {
                    pPlotObject->addPoint(t,value);  
                }
            }
        }
    }
    else {
        LOG("recalculating function");
        fl::Function2D::Function2DBase *p2DFunc = NULL; 
        KPlotObject *pPlotObject = NULL ; 
        double val;
        bool bOk ; 
        int counter = 1 ; 
        for ( int i = 0 ; i < m_functionToCalculate.size() ;++ i){
            pPlotObject = m_plotsCalculated.at(i);
            p2DFunc = dynamic_cast<fl::Function2D::Function2DBase *> ( m_functionToCalculate.at(i) );
            Q_ASSERT ( pPlotObject != NULL && p2DFunc != NULL ) ; 
            if ( p2DFunc->type() == fl::FunctionBase::eDiscrete ) 
                continue ; 
            for ( double i = m_xMin ; i < m_xMax ; i += 0.01 ) {
                val = p2DFunc->eval(i,&bOk);
                if ( bOk ) {
                    pPlotObject->addPoint(i,val);  
                }
            }
        }
    }
    m_mutex.unlock();
}

void Thesis::UI::CalculatingThread::setFunctions(const Thesis::UI::PlotWidgetProxy::FunctionsPlotMapType& pFunctionPlotMap)
{
    cLOG();
    m_mutex.lock();
    freeLists();
    PlotWidgetProxy::FunctionsPlotMapType::const_iterator it = pFunctionPlotMap.begin();
    PlotWidgetProxy::FunctionsPlotMapType::const_iterator itEnd = pFunctionPlotMap.end();
    for ( it ; it != itEnd ; ++it ) {
        m_functionToCalculate.append(it.key());
        m_plotsCalculated.append(it.value());
    }
    m_mutex.unlock() ; 
}
void Thesis::UI::CalculatingThread::freeLists()
{
    cLOG();
    m_functionToCalculate.clear();
    m_plotsCalculated.clear();
}

void Thesis::UI::PlotWidgetProxy::zoomIn()
{
    cLOG();
    double xMn = xMin();
    if ( xMn < 0 ) 
        xMn +=1 ; 
    else
        xMn -= 1 ; 
    double xMx = xMax();
    if ( xMx < 0 ) 
        xMx +=1 ; 
    else
        xMx -= 1 ; 
    changeRange(xMn,xMx,yMin(),yMax());
}

void Thesis::UI::PlotWidgetProxy::zoomOut()
{
    cLOG();
    double xMn = xMin();
    if ( xMn < 0 ) 
        xMn -=1 ; 
    else
        xMn += 1 ; 
    double xMx = xMax();
    if ( xMx < 0 ) 
        xMx -=1 ; 
    else
        xMx += 1 ; 
    changeRange(xMn,xMx,yMin(),yMax());

}
