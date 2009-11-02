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

#include "approximatedialog.h"
#include "ui_approximation.h"
#include "commons.h"

#include <QMessageBox>

#include "fl/functionbase.h"
#include "fl/function2dbase.h"
#include "fl/functioncontinous.h"
#include "plotting/kplotwidget.h"
#include "plotting/kplotobject.h"
#include "fl/iapproximation.h"
#include "fl/polymonialapproximatio.h"

Thesis::UI::ApproximateDialog::ApproximateDialog( QWidget *pParent /*= NULL*/ ) : QDialog(pParent),
m_pDialog( new Ui::ApproximateDialogUI()),
m_calculatedFunc( NULL ),
m_pKPlotWidget( new KPlotWidget(this)),
m_whereToAdd ( eCurrentWorkspace)
{
    SET_MAIN_APPLICATION_ICON;
	m_pDialog->setupUi(this);
	
	connect ( m_pDialog->showFromCombobox, SIGNAL(currentIndexChanged ( int )),this,SLOT(populateList(int)));
	connect ( m_pDialog->okButton, SIGNAL(pressed()), this, SLOT(accept()));
	connect ( m_pDialog->cancelButton, SIGNAL(pressed()), this, SLOT(reject()));
	connect ( m_pDialog->previewButton, SIGNAL(pressed()), this, SLOT(preview()));

	m_pDialog->previewLayout->addWidget(m_pKPlotWidget.get());
}
Thesis::UI::ApproximateDialog::~ApproximateDialog()
{
	//delete m_calculatedFunc;

}
int Thesis::UI::ApproximateDialog::show()
{
	populateList(0);
	return QDialog::exec();
}

void Thesis::UI::ApproximateDialog::populateList(int index )
{
	m_pDialog->listWidget->clear();
	if ( index == 0 ){
		foreach ( fl::FunctionBase * pFunc, m_currentWorkspaceFunctions){
			m_pDialog->listWidget->addItem(new QListWidgetItem(QString(pFunc->name().c_str()),m_pDialog->listWidget));
		}
	}
	else {
		foreach ( fl::FunctionBase * pFunc, m_allWorkspaceFunctions){
			m_pDialog->listWidget->addItem(new QListWidgetItem(QString(pFunc->name().c_str()),m_pDialog->listWidget));
		}
	}
}
void Thesis::UI::ApproximateDialog::preview()
{
	if ( m_pDialog->listWidget->currentItem()== NULL){
		QMessageBox msgBox;
		msgBox.setText(QObject::tr("Select a function to be approximated."));
		msgBox.exec();
		return ; // from what i have to approximate ??? 
	}
	KPlotObject *obj = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
	fl::Function2D::Function2DBase *pFunction = proxy() ;
	if ( pFunction == NULL)
		return ; 
	m_pKPlotWidget->addPlotObject(kplotobjFromFunction(pFunction,pFunction->xStartWhereIntegratingMakesSense(),pFunction->xStopWhereIntegratingMakesSense()));
	m_pKPlotWidget->show();	
}
fl::Function2D::Function2DBase  * Thesis::UI::ApproximateDialog::resultFunction()
{
	if ( m_calculatedFunc != NULL )
		return m_calculatedFunc;
	return proxy() ; 
}
fl::Function2D::Function2DBase  * Thesis::UI::ApproximateDialog::proxy()
{
	fl::Function2D::IApproximation *pApproxAlgorithm = NULL ;
	if ( m_pDialog->listWidget->currentItem() == NULL )
		return NULL ; 
	std::string funName = m_pDialog->listWidget->currentItem()->text().toStdString();
	fl::FunctionBase *pFunction = NULL ; 
	foreach ( fl::FunctionBase *pF, m_allWorkspaceFunctions){
		if ( pF->name() == funName ){
			pFunction = pF ;
			break ;
		}
	}
	Q_ASSERT(pFunction != NULL );
	if ( pFunction->type() != fl::FunctionBase::eDiscrete){
		QMessageBox msgBox;
		msgBox.setText(QObject::tr("Only discrete functions can be approximated."));
		msgBox.exec();
		return NULL; 
	}
	fl::Function2D::FunctionDiscrete *pFunctionD = dynamic_cast<fl::Function2D::FunctionDiscrete *> ( pFunction);
	m_pKPlotWidget->setLimits( pFunctionD->xMin(), pFunctionD->xMax(), pFunctionD->min(),pFunctionD->max());
	pApproxAlgorithm = new fl::Function2D::PolymonialApproximation(m_pDialog->polymonialDegreeSpinbox->value(),pFunctionD->range());

	fl::Function2D::FunctionContinous *pResultFunc = pApproxAlgorithm->approximate();
	pResultFunc->setName("APPROXIMATION");

	m_calculatedFunc = pResultFunc ; 

	QMessageBox msgBox;
	msgBox.setText(tr("Crop approximation function"));
	msgBox.setInformativeText(tr("Do you want to crop appoximation function to range where it acctually make sense?"));
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No) ; 
	int ret = msgBox.exec();
	if ( ret == QMessageBox::Yes ){
		m_calculatedFunc = fl::Function2D::IApproximation::cropFunction(m_calculatedFunc,pFunctionD->xMin(),pFunctionD->xMax());
	}
	return m_calculatedFunc ; 
}

void Thesis::UI::ApproximateDialog::accept()
{
    if ( m_pDialog->comboBox_2->currentIndex() == 0 )
        m_whereToAdd = eCurrentWorkspace;
    else if ( m_pDialog->comboBox_2->currentIndex() == 1 ) 
        m_whereToAdd = eCreateNewWorkspace;
    QDialog::accept();
}