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
#include <QDebug>
using namespace Thesis::UI;
Thesis::UI::ConvolutionPicker::ConvolutionPicker ( QWidget* parent, Qt::WindowFlags f ) : QDialog ( parent, f ), m_pForm(new Ui::ConvolutionPicker() ),m_whereToAdd(eCurrentWorkspace)
{
    m_pForm->setupUi(this);
    //TODO: smth 
    //FIXME: sss 
//    connect ( m_pForm->comboBox, SIGNAL(currentIndexChanged(QString)),this,SLOT(comboBoxValueChanged(QString)));
    connect ( m_pForm->comboBox, SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxValueChanged(int)));
}

void Thesis::UI::ConvolutionPicker::populateTreeWidget ( int index )
{
    m_pForm->treeWidget->clear();
    Q_ASSERT ( index == -1 || ( index > 0 && index < m_functions.size() ) ) ;
    if ( index ==-1 ) {
        foreach(QStringList list, m_functions){
            foreach(QString str, list ) {
                QTreeWidgetItem *pItem = new QTreeWidgetItem(m_pForm->treeWidget,QStringList(str));
                m_pForm->treeWidget->addTopLevelItem(pItem) ; 
            }
        }
    }
    else
    {
        QStringList l = m_functions[index];
        foreach(QString str, l ) {
            QTreeWidgetItem *pItem = new QTreeWidgetItem(m_pForm->treeWidget,QStringList(str));
            m_pForm->treeWidget->addTopLevelItem(pItem) ; 
        }
    }
}

int  Thesis::UI::ConvolutionPicker::show()
{
    populateTreeWidget();
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
void Thesis::UI::ConvolutionPicker::addFunctions ( int index, const QStringList& names )
{
    m_functions[index] = names ;
    QString text=tr("Show from workspace: %1").arg(index);
    m_pForm->comboBox->addItem(text);
}
void Thesis::UI::ConvolutionPicker::comboBoxValueChanged ( const QString& changed )
{
    qDebug() << changed ; 
    int index = -2 ; 
    if ( changed.compare("Show from all ")){
        index = -1 ; 
    }
    else if ( changed.compare("Show from current")){
        index = -1 ; 
    }
    else
    {
        ;
    }
    populateTreeWidget(index);
}

void Thesis::UI::ConvolutionPicker::comboBoxValueChanged ( int pos )
{
    qDebug() << pos ; 
    int index ; 
    if ( pos == 0 ) 
        index = -1 ; 
    else if( pos == 1 ) 
        index = -1 ; 
    else
        index = pos -2 ; 
    
    qDebug() << "populateTreeWidget("<<index<<");";
}
