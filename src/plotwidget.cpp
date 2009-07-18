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

#include "plotwidget.h"
#include "commons.h"
#include <kplotwidget.h>
#include <kplotobject.h>

#include <qwt3d_surfaceplot.h>

#include "fl/functionbase.h"
#include "fl/function2dbase.h"

using namespace Thesis::UI;


PlotWidgetProxy::PlotWidgetProxy(PlotWidgetProxy::PlotType type, QWidget *pParent ) : 
m_PlotType(type),
m_pParent(pParent)
{
    cLOG();
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
        
        KPlotObject *pPlotObject = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
        for ( float t=0.0; t<=6.28; t+=0.04 ) {
            LOG("Adding points : ("<<t<<" , " << pFunction2D->eval(t) ) ; 
            pPlotObject->addPoint(t,pFunction2D->eval(t));
        }
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
    if ( m_pWidget == NULL ) {
        if ( m_PlotType == ePlot2D ) {
        m_pKPlotWidget.reset( new KPlotWidget(m_pParent));
        m_pKPlotWidget->setAntialiasing( true );
        m_pKPlotWidget->setLimits( -0.1, 6.38, -1.1, 1.1 );
        m_pWidget = m_pKPlotWidget;
        }
        else 
        {
            m_pSurfacePlotWidget.reset ( new Qwt3D::SurfacePlot(m_pParent) ) ; 
            m_pWidget = m_pSurfacePlotWidget;
        }
        return ; 
    }
    LOG("Start switch - our");
    m_pWidget.reset() ;
    m_PlotType = newType ; 
    
    if ( m_PlotType == ePlot2D ) {
        LOG("setting 2d");
        m_pKPlotWidget.reset( new KPlotWidget(m_pParent));
        m_pKPlotWidget->setAntialiasing( true );
        m_pKPlotWidget->setLimits( -0.1, 6.38, -1.1, 1.1 );
        
        m_pSurfacePlotWidget.reset();
        
        m_pWidget = m_pKPlotWidget;
    }
    else 
    {
        LOG("setting 3d");
        m_pSurfacePlotWidget.reset ( new Qwt3D::SurfacePlot(m_pParent) ) ; 
        m_pKPlotWidget.reset();
        m_pWidget = m_pSurfacePlotWidget;
    }
    
    
    emit plotChanging();
    emit plotChanged();
}
