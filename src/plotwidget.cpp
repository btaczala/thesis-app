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

#include "fl/functionbase.h"
#include "fl/function2dbase.h"

using namespace Thesis::UI;


PlotWidgetProxy::PlotWidgetProxy(PlotWidgetProxy::PlotType type, QWidget *pParent ) : 
m_PlotType(type)
{
    cLOG();
    if ( m_PlotType == ePlot2D ) {
        m_pKPlotWidget.reset( new KPlotWidget(pParent));
        m_pKPlotWidget->setAntialiasing( true );
        m_pKPlotWidget->setLimits( -0.1, 6.38, -1.1, 1.1 );
        m_pWidget = m_pKPlotWidget;
    }
}
PlotWidgetProxy::~PlotWidgetProxy()
{
    cLOG();
}

QWidget* PlotWidgetProxy::widget()
{
    cLOG();
    return m_pWidget.get();
}

void PlotWidgetProxy::addFunction(fl::FunctionBase* pFunction)
{
    cLOG();
    
    if ( m_PlotType == ePlot2D && pFunction->dimensions() != 2 ) {
        LOG("Unable to add function with dimensions:"<< pFunction->dimensions() <<" to a 2D plot " ) ; 
        return ; 
    }
    
    m_FunctionVector.push_back(boost::shared_ptr<fl::FunctionBase > ( pFunction ));
    
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

