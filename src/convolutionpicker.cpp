/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "convolutionpicker.h"
#include "commons.h"

using namespace Thesis::UI;
Thesis::UI::ConvolutionPicker::ConvolutionPicker ( QWidget* parent, Qt::WindowFlags f ) : QDialog ( parent, f ), m_pForm(new Ui::ConvolutionPicker() ),m_whereToAdd(eCurrentWorkspace)
{
    m_pForm->setupUi(this);
    connect ( m_pForm->comboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxValueChanged(int)));
    connect ( m_pForm->okButton, SIGNAL(clicked()),this,SLOT(accept()));
    connect ( m_pForm->cancelButton, SIGNAL(clicked()),this,SLOT(reject()));

    populateTreeWidget(0);
}

void Thesis::UI::ConvolutionPicker::populateTreeWidget ( int index )
{
    m_pForm->treeWidget->clear();
    QStringList l ;
    if ( index == 0 ) {
        l = m_allWorkspaceFunctions;
    }
    else
    {
        l = m_currentWorkspaceFunctions;
    }
    foreach(QString str, l ) {
        LOG(str);
        QTreeWidgetItem *pItem = new QTreeWidgetItem(m_pForm->treeWidget,QStringList(str));
        m_pForm->treeWidget->addTopLevelItem(pItem) ; 
    }
}

int  Thesis::UI::ConvolutionPicker::show()
{
    populateTreeWidget(0);
    return QDialog::exec();
}

void ConvolutionPicker::accept()
{
    QList<QTreeWidgetItem*> l = m_pForm->treeWidget->selectedItems();
    foreach(QTreeWidgetItem* pItem, l ) {
        m_selectedFunctions.push_back( pItem->text(0));
    }
    if ( m_pForm->comboBox_2->currentIndex() == 0 ) 
        m_whereToAdd = eCurrentWorkspace;
    else if ( m_pForm->comboBox_2->currentIndex() == 1 ) 
        m_whereToAdd = eCreateNewWorkspace;
    QDialog::accept();
}
void ConvolutionPicker::reject()
{
    QDialog::reject();
}
void Thesis::UI::ConvolutionPicker::comboBoxValueChanged ( const QString& changed )
{
}

void Thesis::UI::ConvolutionPicker::comboBoxValueChanged ( int pos )
{
    populateTreeWidget(pos);
}

void Thesis::UI::ConvolutionPicker::setCurrentWorkspaceFunctions( const QStringList & functions )
{
    LOG(functions);
    m_currentWorkspaceFunctions = functions;
}

void Thesis::UI::ConvolutionPicker::setAllWorkspaceFunctions( const QStringList & functions )
{
    LOG(functions);
    m_allWorkspaceFunctions = functions ; 

}