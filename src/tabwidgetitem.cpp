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

#include "tabwidgetitem.h"
#include "plotwidget.h"
#include <QLayout>
#include "commons.h"

using namespace Thesis::UI ; 


TabWidgetItem::TabWidgetItem(QWidget* parent, Qt::WindowFlags f) : 
QWidget(parent, f),
m_pPlotProxy( new PlotWidgetProxy(Thesis::UI::PlotWidgetProxy::ePlot2D,this) ),
m_pLayout( new QHBoxLayout(this) )
{
    cLOG();
    m_pLayout->addWidget(m_pPlotProxy->widget());
    setLayout(m_pLayout);
    
    connect ( m_pPlotProxy.get(), SIGNAL(plotChanging()),this,SLOT(plotAboutToChange()));
    connect ( m_pPlotProxy.get(), SIGNAL(plotChanged()),this,SLOT(plotChaged() ) );
}
TabWidgetItem::~TabWidgetItem()
{
    cLOG();
}

PlotWidgetProxy* TabWidgetItem::plotProxy()
{
    cLOG();
    return m_pPlotProxy.get();
}

void TabWidgetItem::plotAboutToChange()
{
    cLOG();
    m_pLayout->removeWidget(m_pPlotProxy->widget());
}
void Thesis::UI::TabWidgetItem::plotChaged()
{
    cLOG();
    m_pLayout->addWidget(m_pPlotProxy->widget());
}
