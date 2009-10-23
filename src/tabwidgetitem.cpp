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
#include <QColorDialog>

#include <plotting/kplotwidget.h>



using namespace Thesis::UI ; 


TabWidgetItem::TabWidgetItem(QWidget* parent, Qt::WindowFlags f) : 
QWidget(parent, f),
m_pPlotProxy( new PlotWidgetProxy(this) ),
m_pLayout( new QHBoxLayout(this) ),
m_pLeftLayout(new QVBoxLayout(this)),
m_pDeleteButton ( new QPushButton(tr("Delete me"))),
m_pListWidget( new QListWidget(this)),
m_pContextMenu( new ContextMenu(this,m_pListWidget))
{
    cLOG();
    m_pDeleteButton->setEnabled(false);
    m_pLeftLayout->addWidget(m_pListWidget);
    m_pLeftLayout->addWidget(m_pDeleteButton);
    
    m_pPlotProxy->widget()->setSizePolicy(QSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding));
    m_pListWidget->setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
	
	m_pListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    
    m_pLayout->addLayout(m_pLeftLayout);
    m_pLayout->addWidget(m_pPlotProxy->widget());
    setLayout(m_pLayout);
    
    
    connect ( m_pPlotProxy.get(), SIGNAL(functionAdded(const FunctionInfo & )),this,SLOT(functionAdded(const FunctionInfo & )));
    connect ( m_pListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(itemDoubleClicked(QListWidgetItem*)));
    connect ( m_pDeleteButton, SIGNAL(pressed()),this,SLOT(deleteFunction()));

	connect ( m_pListWidget, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenuForWidget(const QPoint &)));

	connect ( m_pContextMenu->_delete, SIGNAL(triggered()),this,SLOT(deleteFunction()));
	connect ( m_pContextMenu->_changeColor, SIGNAL(triggered()),this,SLOT(changeColorForFunction()));
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
	//m_mutex.unlock();
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
	//m_mutex.lock();
    m_pPlotProxy->addFunction(pFunction,color);
}
void Thesis::UI::TabWidgetItem::addFunctionAndOperation ( const QList< const fl::FunctionBase* >& list, IOperation* pOperation )
{
	
    fl::FunctionBase *pFunction=NULL ; 
	foreach( const fl::FunctionBase *pFunc, list){
        pOperation->addFunction(pFunc) ;
	}	
    pFunction = pOperation->calculate() ; 
    addFunction(pFunction,Qt::green);
}

void Thesis::UI::TabWidgetItem::showContextMenuForWidget( const QPoint & pos )
{
	cLOG() ; 

	m_pContextMenu->exec(mapToGlobal(pos));
	/*QMenu contextMenu(tr("Context menu"), this);
	contextMenu.addAction(new QAction(tr("Delete"), this));
	contextMenu.exec();*/
}

void Thesis::UI::TabWidgetItem::changeColorForFunction()
{
	cLOG();
	QListWidgetItem *pItem = m_pListWidget->currentItem();
	if  (pItem == NULL ) 
		return ; 
	KPlotObject * pObj = m_pPlotProxy->plotForFunction(pItem->text()) ; 

	QColor c = QColorDialog::getColor(pObj->brush().color(),this,tr("Pick a color"));
	if ( c.isValid()){
		pObj->setBrush(c);
		m_pPlotProxy->plotWidget()->update();
	}
}
void Thesis::UI::TabWidgetItem::showFunctionInformation()
{
	cLOG() ; 
	QListWidgetItem *pItem = m_pListWidget->currentItem() ;
	if ( pItem == NULL)
		return ; 
	//QMessageBox b ; 

}
Thesis::UI::TabWidgetItem::ContextMenu::ContextMenu( QWidget *pParent, const QListWidget  *pW ) : QMenu(pParent),_pListWidget(pW) 
{
	_showInfo = new QAction(tr("Show information"),this);
	_delete = new QAction(tr("Delete"),this);
	_changeColor = new QAction(tr("Change color"),this);

	
	addAction(_showInfo);
	addSeparator();
	addAction(_delete);
	addAction(_changeColor);	
}

Thesis::UI::TabWidgetItem::ContextMenu::~ContextMenu()
{
	delete _delete;
	delete _changeColor; 
}

QAction * Thesis::UI::TabWidgetItem::ContextMenu::exec( const QPoint & p )
{
	cLOG() ; 
	LOG(p);
	//LOG(mapTo(const_cast<QListWidget*>( _pListWidget ),p));
	LOG(mapFromGlobal(p));
	if ( _pListWidget->selectedItems().isEmpty() ){
		_delete->setEnabled(false);
		_changeColor->setEnabled(false);
	}
	else
	{
		_delete->setEnabled(true);
		_changeColor->setEnabled(true);

	}
	return QMenu::exec(p);
}
