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
#include "commons.h"
#include "ioperation.h"

#include <QLayout>
#include <QScrollBar>
#include <QListWidget>
#include <QButtonGroup>
#include <QPushButton>


using namespace Thesis::UI ; 


TabWidgetItem::TabWidgetItem(QWidget* parent, Qt::WindowFlags f) : 
QWidget(parent, f),
m_pPlotProxy( new PlotWidgetProxy(this) ),
m_pLayout( new QHBoxLayout(this) ),
m_pLeftLayout(new QVBoxLayout(this)),
m_pDeleteButton ( new QPushButton(tr("Delete me"))),
m_pListWidget( new QListWidget(this))
{
    cLOG();
    
    
    m_pDeleteButton->setEnabled(false);
    m_pLeftLayout->addWidget(m_pListWidget);
    m_pLeftLayout->addWidget(m_pDeleteButton);
    
    m_pPlotProxy->widget()->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    m_pListWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
    
    m_pLayout->addLayout(m_pLeftLayout);
    m_pLayout->addWidget(m_pPlotProxy->widget());
    setLayout(m_pLayout);
    
    
    connect ( m_pPlotProxy.get(), SIGNAL(functionAdded(const FunctionInfo & )),this,SLOT(functionAdded(const FunctionInfo & )));
    connect ( m_pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect ( m_pDeleteButton, SIGNAL(pressed()),this,SLOT(deleteFunction()));
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


void Thesis::UI::TabWidgetItem::functionAdded(const FunctionInfo & fInfo )
{
    cLOG();
    m_pDeleteButton->setEnabled(true);
    QListWidgetItem *pItem = new QListWidgetItem(m_pListWidget);
    pItem->setText(fInfo._fId);
    pItem->setBackground(fInfo._fColor);
    
    m_pListWidget->addItem(pItem);
}

void Thesis::UI::TabWidgetItem::deleteFunction()
{
    cLOG();
    QListWidgetItem *pItem = m_pListWidget->currentItem();
    if  (pItem == NULL ) 
        return ; 
    LOG(pItem->text());
    m_pPlotProxy->deleteFunction(pItem->text());
    int i = m_pListWidget->currentRow();
    delete m_pListWidget->takeItem(i);
    
    if ( m_pListWidget->count() == 0 ) 
        m_pDeleteButton->setEnabled(false);
}
void Thesis::UI::TabWidgetItem::itemDoubleClicked(const QListWidgetItem* pItem)
{
    cLOG() ; 
    LOG(pItem->text());
    QString oldFunctionName = pItem->text();
}
void Thesis::UI::TabWidgetItem::addFunction(fl::FunctionBase* pFunction, const QColor& color)
{
    m_pPlotProxy->addFunction(pFunction,color);
}
void Thesis::UI::TabWidgetItem::addFunctionAndOperation ( const QList< const fl::FunctionBase* >& list, IOperation* pOperation )
{
    fl::FunctionBase *pFunction=NULL ; 
    foreach( const fl::FunctionBase *pFunc, list)
        pOperation->addFunction(pFunc) ;
    pFunction = pOperation->calculate() ; 
    addFunction(pFunction,Qt::green);
}
