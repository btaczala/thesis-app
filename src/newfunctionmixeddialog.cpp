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

using namespace Thesis::UI ;

Thesis::UI::NewFunctionMixedDialog::NewFunctionMixedDialog(QWidget* parent, Qt::WindowFlags f): QDialog(parent, f), m_pForm(new Ui::newFunctionMixed())
{
    m_iCurrentRow = 0 ; 
    m_pForm->setupUi(this);
    
    connect ( m_pForm->addRowButton, SIGNAL(pressed()),this,SLOT(addRow()));
    connect ( m_pForm->deleteCurrentRow, SIGNAL(pressed()),this,SLOT(deleteRow() ) );
    m_pForm->treeWidget->setHeaderLabels(QStringList() << " f(x" << " variable" << "range start" <<"range stop");
    
    //m_pForm->treeWidget->setItemDelegateForColumn(2,new ComboBoxDelegate(this));
    m_pForm->treeWidget->setRootIsDecorated(false);
    
    

    QTreeWidgetItem *pTreeItem = new QTreeWidgetItem();
    pTreeItem->setText(0,"sin(x)");
    pTreeItem->setText(1,"x");
    pTreeItem->setText(2,"-inf");
    pTreeItem->setText(3,"0");
    m_pForm->treeWidget->addTopLevelItem(pTreeItem);
    
    QTreeWidgetItem *pTreeItem2 = new QTreeWidgetItem();
    pTreeItem2->setText(0,"sin(x)");
    pTreeItem2->setText(1,"x");
    pTreeItem2->setText(2,"0");
    pTreeItem2->setText(3,"0");
    m_pForm->treeWidget->addTopLevelItem(pTreeItem2);
    
    QTreeWidgetItem *pTreeItem3 = new QTreeWidgetItem();
    pTreeItem3->setText(0,"cos(sin(x))");
    pTreeItem3->setText(1,"x");
    pTreeItem3->setText(2,"0");
    pTreeItem3->setText(3,"+inf");
    m_pForm->treeWidget->addTopLevelItem(pTreeItem3);
    
}
void NewFunctionMixedDialog::done(int i)
{
    QDialog::done(i);
}
void NewFunctionMixedDialog::accept()
{
    cLOG() ; 
    QTreeWidgetItem * pItem = NULL ; 
    for ( int i = 0 ; i < m_pForm->treeWidget->topLevelItemCount() ; ++i ) {
        pItem = m_pForm->treeWidget->topLevelItem(i);
        QStringList l ;
        l << pItem->text(0) << pItem->text(1) << pItem->text(2) << pItem->text(3) ; 
        LOG(l);
        m_FunctionsDesc.push_back( l );
    }    
    QDialog::accept();
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


// Thesis::UI::ComboBoxDelegate::ComboBoxDelegate(QObject* parent): QItemDelegate(parent)
// {
// }
// 
// QWidget* Thesis::UI::ComboBoxDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
// {
//     QComboBox *pEditor = new QComboBox(parent);
//     pEditor->addItem(">");
//     pEditor->addItem("<");
//     pEditor->addItem("=");
//     pEditor->addItem(">=");
//     pEditor->addItem("<=");
//     return pEditor ; 
// }
// 
// void Thesis::UI::ComboBoxDelegate::setEditorData(QWidget* editor, const QModelIndex& index) const
// {
//     QItemDelegate::setEditorData(editor, index);
// }
// 
// void Thesis::UI::ComboBoxDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
// {
//     editor->setGeometry(option.rect);
// }
// void Thesis::UI::ComboBoxDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
// {
//     QItemDelegate::setModelData(editor, model, index);
// }
// 