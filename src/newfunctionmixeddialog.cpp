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

#include "newfunctionmixeddialog.h"
#include "ui_functionMixed.h"
#include "commons.h"
#include <QComboBox>
#include "tooltips.h"

#include "functionsproxy.h"

using namespace Thesis::UI ;

Thesis::UI::NewFunctionMixedDialog::NewFunctionMixedDialog(QWidget* parent, Qt::WindowFlags f): QDialog(parent, f), m_pForm(new Ui::newFunctionMixed())
{
    m_iCurrentRow = 0 ; 
    m_pForm->setupUi(this);
    m_pForm->addRowButton->setToolTip(Thesis::ToolTips::UI::NewMixedDialog::scAddRowTooltip);
    m_pForm->deleteCurrentRow->setToolTip(Thesis::ToolTips::UI::NewMixedDialog::scDeleteRowTooltip);
    connect ( m_pForm->addRowButton, SIGNAL(pressed()),this,SLOT(addRow()));
    connect ( m_pForm->deleteCurrentRow, SIGNAL(pressed()),this,SLOT(deleteRow() ) );
    m_pForm->treeWidget->setHeaderLabels(QStringList() << " f(x)" << " variable" << "range ");
    m_pForm->treeWidget->setToolTip( Thesis::ToolTips::UI::NewMixedDialog::scMainToolTip ) ; 
    
    //m_pForm->treeWidget->setItemDelegateForColumn(2,new ComboBoxDelegate(this));
    m_pForm->treeWidget->setRootIsDecorated(false);
    
}
void NewFunctionMixedDialog::done(int i)
{
    QDialog::done(i);
}
void NewFunctionMixedDialog::accept()
{
    cLOG() ; 
    parse() ;
    QDialog::accept();
}

void Thesis::UI::NewFunctionMixedDialog::parse()
{
    QTreeWidgetItem * pItem = NULL ; 
    QStringList list ; 
    QString oneFunction ;
    
    for ( int i = 0 ; i < m_pForm->treeWidget->topLevelItemCount() ; ++i ) {
        list.clear();
        pItem = m_pForm->treeWidget->topLevelItem(i);
        oneFunction = pItem->text(0) + "," + pItem->text(1) + "," + pItem->text(2);
        list << Thesis::Helpers::parseOneFunction(oneFunction);
        m_FunctionsDesc.push_back(list);
    }
}

void NewFunctionMixedDialog::reject()
{
    QDialog::reject();
}
void NewFunctionMixedDialog::addRow()
{
    cLOG();
    QTreeWidgetItem *pTreeItem = new QTreeWidgetItem();
    pTreeItem->setText(1,"x");
    pTreeItem->setFlags(Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    pTreeItem->setToolTip(0,Thesis::ToolTips::UI::NewMixedDialog::scFunctionHeadertooltip);
    pTreeItem->setToolTip(1,Thesis::ToolTips::UI::NewMixedDialog::scVarHeaderTooltip);
    pTreeItem->setToolTip(2,Thesis::ToolTips::UI::NewMixedDialog::scRangeHeaderTooltip);
    m_pForm->treeWidget->addTopLevelItem(pTreeItem);
}
void NewFunctionMixedDialog::deleteRow()
{
    cLOG();
    QTreeWidgetItem *pTreeItem = m_pForm->treeWidget->currentItem();
    int i = m_pForm->treeWidget->indexOfTopLevelItem(pTreeItem) ;
    LOG(i);
    m_pForm->treeWidget->takeTopLevelItem(i);
}
