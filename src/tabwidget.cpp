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

#include "tabwidget.h"
#include "plotwidget.h"
#include "commons.h"
#include "tabwidgetitem.h"

using namespace Thesis::UI;


TabWidget::TabWidget(QWidget* parent) : 
QTabWidget(parent),
m_currentWorkspace(0)
{
    cLOG();
    
}

TabWidget::~TabWidget()
{
    cLOG();
}

void TabWidget::addTab(bool bSetFocus)
{
    cLOG();
    TabWidgetItem *pItemWidget = new TabWidgetItem(this);
    QString currentWorkspaceText = QObject::tr("Workspace") +" " +  QString::number(m_currentWorkspace+1) ; 
    int iPos = QTabWidget::addTab(pItemWidget,currentWorkspaceText );
    if ( bSetFocus ) 
        QTabWidget::setCurrentWidget(pItemWidget);
    m_currentWorkspace++ ;     
}

void TabWidget::closeTabAt(int index /*=-1*/)
{
    cLOG();
    int iCloseTabIndex = index==-1 ? currentIndex() : index ;
    if ( iCloseTabIndex == -1 ) {
        LOG("Unable to close tab at: "<<index);
        return ; 
    }
    QTabWidget::removeTab(iCloseTabIndex);
}

void TabWidget::addFunction(Thesis::FunctionsProxy & fProxy, int index)
{
    cLOG();
    Q_UNUSED(index);
    QWidget *pWidget = currentWidget() ; 
    TabWidgetItem *pTabWidgetItem = qobject_cast< TabWidgetItem* >(pWidget);
    if ( pTabWidgetItem == NULL ){
        qDebug() << "Unable to get current tab widget item. Probably there is no workspace";
        return ;
    }
    pTabWidgetItem->addFunction(fProxy.proxy(),fProxy.color());
}

