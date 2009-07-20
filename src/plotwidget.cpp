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
#include <kplotwidget.h>
#include <kplotobject.h>

#include <qwt3d_surfaceplot.h>

#include <QScrollBar>

#include "fl/functionbase.h"
#include "fl/function2dbase.h"
#include "fl/functionException.h"
#include <QVBoxLayout>

using namespace Thesis::UI;


PlotWidgetProxy::PlotWidgetProxy(PlotWidgetProxy::PlotType type, QWidget *pParent ) : 
m_PlotType(type),
m_pParent(pParent),
m_pKPlotWidget( new KPlotWidget() ),
m_pSurfacePlotWidget( new Qwt3D::SurfacePlot() ),
m_xMin(-1),
m_xMax(3),
m_yMin(-2),
m_yMax(2)
{
    cLOG();
    m_pKPlotWidget->setAntialiasing( true );
    m_pKPlotWidget->setLimits( m_xMin,m_xMax,m_yMin,m_yMax);
    
    changeType(type);
}
PlotWidgetProxy::~PlotWidgetProxy()
{
    cLOG();
}

QWidget* PlotWidgetProxy::widget()
{
    cLOG();
    Q_ASSERT(m_pWidget.get() != NULL ) ; 
    return m_pWidget.get();
}

void PlotWidgetProxy::addFunction(fl::FunctionBase* pFunction)
{
    cLOG();
    
    if ( m_PlotType == ePlot2D && pFunction->dimensions() != 2 ) {
        //LOG("Unable to add function with dimensions:"<< pFunction->dimensions() <<" to a 2D plot " ) ; 
        changeType(ePlot3D);
    }
    if ( m_PlotType == ePlot3D && pFunction->dimensions() !=3 ) {
        changeType(ePlot2D);
    }
    
    //m_FunctionVector.push_back(boost::shared_ptr<fl::FunctionBase > ( pFunction ));
    
    if ( pFunction->dimensions() == 2 ) 
    {
        fl::Function2D::Function2DBase *pFunction2D = dynamic_cast<fl::Function2D::Function2DBase *>( pFunction ); 
        Q_ASSERT(pFunction2D != NULL ) ; 
        
        KPlotObject plotType ; 
        KPlotObject *pPlotObject = NULL ; 
        if ( pFunction2D->type() == fl::FunctionBase::eDiscrete ) 
            pPlotObject = new KPlotObject( Qt::red, KPlotObject::Points, 2 );
        else if ( pFunction2D->type() == fl::FunctionBase::eContinous ) 
            pPlotObject = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
            
//         KPlotObject *pPlotObject = new KPlotObject( Qt::red, plotType, 2 );
        bool bOk ; 
        double value ; 
        double maxValueY ; 
        double minValueY ; 
        for ( double t=m_xMin; t<=m_xMax; t+=0.01 ) {
            value = pFunction2D->eval(t,&bOk);
            if ( bOk ) {
                LOG("Adding points : ("<<t<<" , " << value<< ")") ; 
                pPlotObject->addPoint(t,value);  
            }
        }
        
        m_PlotsFunctions.insert(pPlotObject,pFunction);
        
        m_pKPlotWidget->addPlotObject(pPlotObject);
        m_pKPlotWidget->update();
    }
}

void PlotWidgetProxy::changeType(Thesis::UI::PlotWidgetProxy::PlotType newType)
{
    cLOG() ; 
    if ( newType == m_PlotType && m_pWidget != NULL ) {
        LOG("Returning without changing");
        return ;
    }
    if ( m_pWidget == NULL ) { // only one!!!!
        setWidget(m_PlotType);
        return ; 
    }
    LOG("Start switch - our");
    m_pWidget.reset() ;
    m_PlotType = newType ; 
    
    if ( m_PlotType == ePlot2D ) {
        LOG("setting 2d");
        setWidget(ePlot2D);
    }
    else 
        setWidget( ePlot3D );
    emit plotChanging();
    emit plotChanged();
}

void Thesis::UI::PlotWidgetProxy::setWidget(Thesis::UI::PlotWidgetProxy::PlotType _type)
{
    cLOG() ; 
    if ( _type == ePlot2D ) 
        m_pWidget = m_pKPlotWidget ;
    else if ( _type == ePlot3D )
        m_pWidget = m_pSurfacePlotWidget;
}

void Thesis::UI::PlotWidgetProxy::changeRange(double xstart, double xstop, double ystart, double ystop)
{
    LOG(" ( " << xstart << " , " << xstop << " x ( " << ystart << " , " << ystop << " ) " ) ; 
    if ( m_PlotType == ePlot3D ) 
    {
        LOG("unable to change 3d plot range");
        return ;
    }
    m_xMax = xstop ; 
    m_xMin = xstart ;
    m_yMax = ystop ; 
    m_yMin = ystart ; 
    
    m_pKPlotWidget->setLimits( m_xMin,m_xMax,m_yMin,m_yMax);
    QMap<KPlotObject*, fl::FunctionBase *>::iterator it = m_PlotsFunctions.begin() ; 
    fl::Function2D::Function2DBase *p2DFunc = NULL; 
    KPlotObject *pPlotObject = NULL ; 
    double val;
    bool bOk ; 
    while( it != m_PlotsFunctions.end()) {
        pPlotObject = it.key();
        p2DFunc = dynamic_cast<fl::Function2D::Function2DBase *> ( it.value() );
        Q_ASSERT ( pPlotObject != NULL && p2DFunc != NULL ) ; 
        if ( p2DFunc->type() == fl::FunctionBase::eDiscrete ) 
            continue ; 
        pPlotObject->clearPoints() ;
        for ( double i = m_xMin ; i < m_xMax ; i += 0.01 ) {
            val = p2DFunc->eval(i,&bOk);
            if ( bOk ) {
                LOG("Adding points : ("<<i<<" , " << val<< ")") ; 
                pPlotObject->addPoint(i,val);  
            }
        }
        ++it ; 
    }
}
