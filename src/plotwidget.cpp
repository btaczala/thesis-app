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
#include "kplotpoint.h"
#include "kplotaxis.h"

//#include <qwt3d_surfaceplot.h>

#include <QScrollBar>
#include <QProgressDialog>

#include "fl/functionbase.h"
#include "fl/function2dbase.h"
#include "fl/functionException.h"
#include "fl/functiondiscrete.h"
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
	m_pKPlotWidget->setShowGrid(true);
	m_pKPlotWidget->setObjectToolTipShown(true);
	m_pKPlotWidget->setBackgroundColor(Qt::white);
	m_pKPlotWidget->setForegroundColor(Qt::black);
	m_pKPlotWidget->axis(KPlotWidget::Axis::BottomAxis)->setLabel("x");
	m_pKPlotWidget->axis(KPlotWidget::Axis::LeftAxis)->setLabel("y");
    
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
    Q_ASSERT(pFunction != NULL );
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
	QList<KPlotPoint*> points = pPlotObject->points();
	foreach ( KPlotPoint *onePoint, points)
		
		onePoint->setLabel(pFunction2D->name().c_str());
    m_pLastAddedFunction = pFunction ; 
	LOG("inserting :" <<pFunction <<pPlotObject);
    m_PlotsFunctions.insert(pFunction,pPlotObject);
    
    //m_pKPlotWidget->addPlotObject(pPlotObject);
    
    //m_pCalcThread->setFunctions(m_PlotsFunctions);
	m_pCalcThread->setLastFunctionAdded(m_pLastAddedFunction);
	m_pCalcThread->setLastPlotAdded(pPlotObject);
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
			LOG("deleting" << it.key()->name() << "with address:" << it.value());
            m_pKPlotWidget->removeObject( it.value() );
			delete it.key();
			it = m_PlotsFunctions.erase(it);
        }
    }
    //m_pKPlotWidget->update();

}
void Thesis::UI::PlotWidgetProxy::changeRange(double xstart, double xstop, double ystart, double ystop)
{   
    m_xMin = xstart; 
    m_xMax = xstop; 
    m_yMin = ystart; 
    m_yMax = ystop; 
    
    FunctionsPlotMapType::iterator it = m_PlotsFunctions.begin();
    FunctionsPlotMapType::iterator itEnd = m_PlotsFunctions.end();
    for ( it ; it != itEnd ; ++it ){
        if( it.key()->type() == fl::FunctionBase::eDiscrete ){      
            continue ; 
        }
        else
            it.value()->clearPoints();
    }

    m_pCalcThread->setFunctions(m_PlotsFunctions);
    m_pCalcThread->setLimits(m_xMin,m_xMax,m_yMin,m_yMax);
    m_pCalcThread->setWorkType(CalculatingThread::eRecalculate);
    
    m_pKPlotWidget->setLimits(m_xMin,m_xMax,m_yMin,m_yMax);
    
    m_pCalcThread->start() ; 
}

void Thesis::UI::PlotWidgetProxy::threadEnded()
{
    cLOG();
    if ( m_pCalcThread->workType() == CalculatingThread::eAdd ) {
        FunctionInfo info ; 
        info._fId = QString( m_pLastAddedFunction->name().c_str());
		KPlotObject *pLastObject = m_PlotsFunctions[m_pLastAddedFunction];
		Q_ASSERT(pLastObject);
        info._fColor = pLastObject->brush().color();
		//pLastObject->la
		m_pKPlotWidget->addPlotObject(pLastObject);
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

Thesis::UI::CalculatingThread::CalculatingThread() : QThread(), m_pLastPlotAdded(NULL),m_pLastFunctionAdded(NULL)
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
		Q_ASSERT( m_pLastFunctionAdded != NULL && m_pLastPlotAdded != NULL );
        fl::FunctionBase *pFunction = m_pLastFunctionAdded;
        if ( pFunction->dimensions() == 2 ) 
        {
            fl::Function2D::Function2DBase *pFunction2D = dynamic_cast<fl::Function2D::Function2DBase *>( pFunction ); 
			LOG(pFunction2D->name() << " size of arr" << m_functionToCalculate.size() );
            Q_ASSERT(pFunction2D != NULL ) ; 
            KPlotObject *pPlotObject = m_pLastPlotAdded;
            bool bOk ; 
            double value;
            double start;
            double stop;
            if ( pFunction2D->type() == fl::FunctionBase::eDiscrete ) {
                // add all values
				fl::Function2D::FunctionDiscrete *pF = dynamic_cast<fl::Function2D::FunctionDiscrete *>(pFunction2D);
                start = pF->xMin();
                stop = pF->xMax();
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
                    //LOG("Adding :" << i << " - " << val);
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
	/// zoom about 10% of value
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

KPlotObject * Thesis::UI::PlotWidgetProxy::plotForFunction( const QString & fID )
{
	cLOG();
	KPlotObject * pRet = NULL ; 
	FunctionsPlotMapType::iterator it = m_PlotsFunctions.begin() ; 
	FunctionsPlotMapType::iterator itEnd = m_PlotsFunctions.end() ; 
	for ( it ; it != itEnd ; ++ it ) {
		if ( it.key()->name() == fID.toStdString() ) {
			pRet = it.value();
			break ; 
		}
	}
	return pRet ; 
}