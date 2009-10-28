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

#include "functioninfodialog.h"
#include "ui_functioninfo.h"

#include <QWidget>
#include <functionbase.h>
#include <fl/functiondiscrete.h>
#include <fl/functionMixed.h>
#include <QMessageBox>

Thesis::UI::FunctionInfoDialog::FunctionInfoDialog ( const fl::FunctionBase* pFun, QWidget* pParent ) : QDialog ( pParent ), m_pDialog( new Ui::FunctionDialogUI() ), m_pFun(NULL)
{
    m_pDialog->setupUi ( this ) ; 
    setFunction(pFun);
    
    m_pDialog->lineEdit_functionType->setEnabled(false);
    m_pDialog->treeWidget->setRootIsDecorated(false);
    
    //m_pDialog->lineEdit_functionEquation->setEnabled(false);
    //m_pDialog->lineEdit_functionName->setEnabled(false);
}
void Thesis::UI::FunctionInfoDialog::setFunction ( const fl::FunctionBase* pFun )
{
    if ( pFun != NULL ) {
        m_pFun = pFun ; 
    }
    else
        return; 
    QString funType, funName, funEq ; 
    QStringList headers ; 
    QList<QTreeWidgetItem*> treeWidgetItems ; 
    funName = m_pFun->name().c_str();
    switch ( pFun->type() ) {
        case fl::FunctionBase::eMixed : {
            funType = tr("Function mixed") ; 
            headers << tr("Function equation") << tr ("Function range");
            const fl::Function2D::FunctionMixed * pFunM = dynamic_cast<const fl::Function2D::FunctionMixed *> ( m_pFun ) ; 
            std::vector<fl::Function2D::FunctionMixed::FunctionRange> v ; 
            v = pFunM->functionRages() ; 
            QTreeWidgetItem *pItem = new QTreeWidgetItem(m_pDialog->treeWidget) ; 
            QString range ; 
            for ( int i = 0 ; i < v.size() ; ++i ) {
                pItem = new QTreeWidgetItem(m_pDialog->treeWidget) ; 
                pItem->setText(0,v[i].m_spFunction->equation().c_str() );
                range = QString::number( v[i].m_start ) ;
                range += v[i].m_operatorStart ==fl::Function2D::FunctionMixed::eGreaterEqual ? " <= " : " < "; 
                range += " x " ; 
                range += v[i].m_operatorStop ==fl::Function2D::FunctionMixed::eGreaterEqual ? " <= " : " < "; 
                range += QString::number( v[i].m_stop ) ;
                pItem->setText(1,range);
                treeWidgetItems << pItem ; 
            }
            
            connect ( m_pDialog->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(listWidgetItemDoubleClicked(QTreeWidgetItem*,int)));
            break ; 
        }
        case fl::FunctionBase::eContinous:{
            funType = tr("Function continous") ; 
            const fl::FunctionContinousBase * pFunC = dynamic_cast<const fl::FunctionContinousBase*> ( m_pFun ) ; 
            funEq = pFunC->equation().c_str();
            headers << tr("Function equation") << tr ("Function range");
            QTreeWidgetItem *pItem = new QTreeWidgetItem(m_pDialog->treeWidget) ; 
            pItem->setText(0,funEq);
            pItem->setText(1,"-inf < x < inf " );
            treeWidgetItems << pItem ; 
            connect ( m_pDialog->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(listWidgetItemDoubleClicked(QTreeWidgetItem*,int)));
            break ; 
        }
        case fl::FunctionBase::eDiscrete:{
            funType = tr("Function discrete") ; 
            const fl::Function2D::FunctionDiscrete* pFunD = dynamic_cast<const fl::Function2D::FunctionDiscrete*> ( m_pFun ) ; 
            headers << tr("x") << tr ("y");
            fl::Function2D::FunctionDiscrete::DomainRange r ; 
            r = pFunD->range() ; 
            QTreeWidgetItem *pItem = NULL ;
            for ( int i = 0 ; i < r.size() ; ++i ) {
                pItem = new QTreeWidgetItem(m_pDialog->treeWidget) ; 
                pItem->setText(0,QString::number(r.at(i).first));
                pItem->setText(1,QString::number(r.at(i).second));
                treeWidgetItems << pItem ; 
            }
            break ; 
        }
    }
    m_pDialog->lineEdit_functionType->setText( funType);
    m_pDialog->lineEdit_functionName->setText( funName );
    
    m_pDialog->treeWidget->setHeaderLabels(headers) ; 
    m_pDialog->treeWidget->addTopLevelItems(treeWidgetItems);
}

int Thesis::UI::FunctionInfoDialog::show()
{
    if ( m_pFun == NULL ) {
        ;
    }
    else{
        int r = QDialog::exec();
    }
}

void Thesis::UI::FunctionInfoDialog::listWidgetItemDoubleClicked(QTreeWidgetItem* pItem , int)
{
    QMessageBox msg ; 
    msg.setText(pItem->text(0));
    msg.exec() ;
}
