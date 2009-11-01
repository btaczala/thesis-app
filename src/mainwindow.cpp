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

#include "mainwindow.h"
#include "commons.h"
#include "actions.h"
#include "tabwidget.h"
#include "plotwidget.h"
#include "newcontinousfunctiondialog.h"
#include "newfunctionmixeddialog.h"
#include "functionsproxy.h"
#include "workspacesettingsdialog.h"
#include "tabwidgetitem.h"
#include "convolutionpicker.h"
#include "approximatedialog.h"

#include <QStatusBar>
#include <QMenuBar>
#include <QKeyEvent>

#include <kplotwidget.h>
#include <QApplication>
#include <QLabel>
#include <QFileDialog>
#include <QToolBar>
#include <QFile>
#include <functionbase.h>
#include <function2dbase.h>
#include <functioncontinous.h>
#include "convolutionoperation.h"

using namespace Thesis::UI;

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : 
QMainWindow(parent, flags), m_iNumberOfWorkspaces(0)
{
    cLOG() ;
    setWindowTitle( tr("Thesis application") );
    
    createWidgets();
    createUI();
    initSignals();
    
    setStatusBarStatus(tr( "Program is ready to use" ),false);
    
    setWindowState(Qt::WindowMaximized);
    
    
//     newTab() ; 
//     // first funct
//     QStringList l1 ;
//     l1 << "0.5*x" << "x" << "0" << ">" << "2" << "<" ; 
//     QStringList l2 ;
//     l2 << "0" << "x" << "-inf" << ">" << "0" << "<=" ; 
//     QStringList l3;
//     l3 << "0" << "x" << "2" << ">=" << "inf" << "<";
//     
//     std::vector<QStringList> list ;
//     list.push_back(l1);
//     list.push_back(l2);
//     list.push_back(l3);
//     Thesis::FunctionsProxy prx ( list ) ;
//     fl::FunctionBase *pFunction1 = prx.proxy();
//     
//     // second func
//     list.clear();
//     l1.clear();
//     l2.clear();
//     l3.clear();
//     
//     l1 << "3/2 - 0.5*x" << "x" << "1" << ">" << "3" << "<";
//     l2 << "0" << "x" << "-inf" << ">" << "1" << "<=";
//     l3 << "0" << "x" << "3" << ">=" << "inf" << "<";
//     list.push_back(l1);
//     list.push_back(l2);
//     list.push_back(l3);
//     
//     Thesis::FunctionsProxy prx2 ( list ) ; 
//     fl::FunctionBase *pFunction2 = prx2.proxy();
// 
//     QList<const fl::FunctionBase*> pFunctionList;
//     pFunctionList << pFunction1 << pFunction2;
// 
//     TabWidgetItem *pTab=qobject_cast<TabWidgetItem*> ( m_pTabWidget->currentWidget());
//     //pTab->addFunction(pFunction1,Qt::white);
//     //pTab->addFunction(pFunction2,Qt::blue);
//     pTab->addFunctionAndOperation(pFunctionList,new ConvolutionMinus());
    

    //
    LOG("End of ");
}

MainWindow::~MainWindow()
{
    cLOG() ;
}
void MainWindow::createUI()
{
    cLOG() ;
    // set up menus 
    m_pFileMenu->addAction( Thesis::Actions::newTabAction() );
    
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(Thesis::Actions::quitAction());
    
//     m_pWorkspaceMenu
    m_pWorkspaceNewFunctionMenu->addAction(Thesis::Actions::newContinousFunctionAction());
    m_pWorkspaceNewDiscreteFunctionMenu->addAction(Thesis::Actions::newDiscreteFromFileAction());
    m_pWorkspaceNewMixedFunctionMenu->addAction( Thesis::Actions::newMixedFromFileAction() );
    m_pWorkspaceNewMixedFunctionMenu->addAction( Thesis::Actions::newMixedFunctionAction() );
    
    m_pWorkspaceNewFunctionMenu->addMenu(m_pWorkspaceNewDiscreteFunctionMenu);
    
    m_pWorkspaceNewFunctionMenu->addMenu(m_pWorkspaceNewMixedFunctionMenu);
    m_pWorkspaceMenu->addMenu(m_pWorkspaceNewFunctionMenu);
    m_pWorkspaceMenu->addSeparator();
    
    m_pWorkspaceMenu->addAction( Thesis::Actions::workspaceSettingsAction());
    m_pWorkspaceMenu->addSeparator();
    m_pWorkspaceMenu->addAction( Thesis::Actions::closeWorkspaceAction() );
    
	m_pAritmeticOperationMenu->addAction( Thesis::Actions::approximateOperation());
    m_pConvolutionBasedAritmeticOperationMenu->addAction(Thesis::Actions::convolutionAddOperation() ) ;
    m_pConvolutionBasedAritmeticOperationMenu->addAction(Thesis::Actions::convolutionMinusOperation() ) ; 
    m_pConvolutionBasedAritmeticOperationMenu->addAction(Thesis::Actions::convolutionTimesOperation() ) ; 
    m_pConvolutionBasedAritmeticOperationMenu->addAction(Thesis::Actions::convolutionDevideOperation() ) ; 
    m_pAritmeticOperationMenu->addMenu(m_pConvolutionBasedAritmeticOperationMenu);
    
    //m_pAritmeticOperationMenu->addAction(Thesis::Actions::calculateCenterOfMassOperatation());

    
    m_pAboutMenu->addAction(Thesis::Actions::aboutAction());
    m_pAboutMenu->addAction(Thesis::Actions::aboutQtAction());
    
    m_pMenuBar->addMenu( m_pFileMenu);
    
    
    m_pMenuBar->addMenu( m_pWorkspaceMenu);
    m_pMenuBar->addMenu( m_pAritmeticOperationMenu);
    m_pMenuBar->addMenu( m_pAboutMenu);
    
    m_pToolBar->addAction(Thesis::Actions::newTabAction());
    m_pToolBar->addAction(Thesis::Actions::quitAction());
    m_pToolBar->addSeparator();
    m_pToolBar->addAction(Thesis::Actions::workspaceSettingsAction());
    
    m_pToolBar->addAction(Thesis::Actions::workspaceZoomIn());
    m_pToolBar->addAction(Thesis::Actions::workspaceZoomOut());
    
    
    
    m_pStatusBar->addPermanentWidget(m_pStatusBarWidget);
    
    
    setStatusBar(m_pStatusBar);
    setMenuBar(m_pMenuBar);
    addToolBar(m_pToolBar);
    setCentralWidget(m_pTabWidget);
    setWindowIcon(QIcon(":/app_icon.png"));
    
	if ( m_pTabWidget->count() == 0 ) {
        m_pWorkspaceMenu->setEnabled(false);
		m_pAritmeticOperationMenu->setEnabled(false);
	}
}

void MainWindow::createWidgets()
{
    cLOG() ;
    m_pStatusBar = new QStatusBar(this) ; 
    m_pStatusBarWidget = new QLabel(m_pStatusBar);
    m_pMenuBar = new QMenuBar(this);
    m_pToolBar = new QToolBar(this);
    m_pFileMenu = new QMenu( tr("&File"),m_pMenuBar );
    /// WORKSPACE menu
    m_pWorkspaceMenu = new QMenu ( tr("&Workspace"), m_pMenuBar ) ; 
    m_pWorkspaceNewFunctionMenu = new QMenu ( tr("&New function") , m_pWorkspaceMenu) ; 
    m_pWorkspaceNewDiscreteFunctionMenu = new QMenu(tr("New discrete function"),m_pWorkspaceNewFunctionMenu);
    m_pWorkspaceNewMixedFunctionMenu = new QMenu(tr("New mixed function"),m_pWorkspaceNewFunctionMenu);
    
    m_pAritmeticOperationMenu  = new QMenu( tr("&Operations "), m_pMenuBar) ; 
    m_pConvolutionBasedAritmeticOperationMenu  = new QMenu( tr("Convolution based"), m_pAritmeticOperationMenu ) ; 
    
    m_pAboutMenu = new QMenu ( tr("&About"),m_pMenuBar ) ; 
    m_pTabWidget = new TabWidget(this);    
}

void MainWindow::initSignals()
{
    cLOG() ;
    connect ( Thesis::Actions::quitAction(),SIGNAL(triggered()),this,SLOT(closeApp()));
    connect ( Thesis::Actions::newTabAction(),SIGNAL(triggered()), this,SLOT(newTab()));
    
    connect( Thesis::Actions::newContinousFunctionAction(),SIGNAL(triggered()),this,SLOT(newContinousFunction()));
    connect ( Thesis::Actions::newDiscreteFromFileAction(),SIGNAL(triggered()),this,SLOT(newFunctionFromFile()));
    connect ( Thesis::Actions::newMixedFunctionAction(),SIGNAL(triggered()),this,SLOT(newMixedFunction()));
    connect ( Thesis::Actions::newMixedFromFileAction(),SIGNAL(triggered()),this,SLOT(newFunctionFromFile()));
    
    connect ( Thesis::Actions::workspaceSettingsAction(), SIGNAL(triggered()),this,SLOT(workspaceSettings()));
    
    connect ( Thesis::Actions::aboutQtAction(), SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect ( Thesis::Actions::aboutAction(), SIGNAL(triggered()), this, SLOT(about()));
    
    connect ( Thesis::Actions::closeWorkspaceAction(),SIGNAL(triggered()),this,SLOT(closeCurrentTab()));
    
    connect ( Thesis::Actions::workspaceZoomIn(),SIGNAL(triggered()),this,SLOT(zoomIn()));
    connect ( Thesis::Actions::workspaceZoomOut(),SIGNAL(triggered()),this,SLOT(zoomOut()));
    
    connect ( Thesis::Actions::convolutionAddOperation(),SIGNAL(triggered()),this,SLOT(convolutionOperation()));
    connect ( Thesis::Actions::convolutionMinusOperation(),SIGNAL(triggered()),this,SLOT(convolutionOperation()));
    connect ( Thesis::Actions::convolutionTimesOperation(),SIGNAL(triggered()),this,SLOT(convolutionOperation()));
    connect ( Thesis::Actions::convolutionDevideOperation(),SIGNAL(triggered()),this,SLOT(convolutionOperation()));

	connect ( Thesis::Actions::approximateOperation(), SIGNAL(triggered()), this, SLOT(approximate()));
    
}

void MainWindow::setStatusBarStatus(const QString& _status, bool isWorking)
{
    Q_UNUSED(isWorking);
    LOG(" _status=" << _status);
    m_pStatusBarWidget->setText(_status);
    m_pStatusBarWidget->setPixmap(QPixmap(":/ok.png").scaled(32,32)) ;
}

void MainWindow::closeApp()
{
    cLOG() ;
    QMainWindow::close();
}

void Thesis::UI::MainWindow::newTab(bool setFocus )
{
    cLOG() ; 
	++m_iNumberOfWorkspaces ;
    m_pTabWidget->addTab(setFocus);
    setStatusBarStatus(tr("New Workspace added"),false);
    m_pWorkspaceMenu->setEnabled(true);
	m_pAritmeticOperationMenu->setEnabled(true);
}

void Thesis::UI::MainWindow::about()
{
    cLOG() ; 
    QApplication::aboutQt();
}

void Thesis::UI::MainWindow::aboutQt()
{
    cLOG() ; 
    QApplication::aboutQt();
}

void Thesis::UI::MainWindow::closeCurrentTab()
{
    cLOG();
    --m_iNumberOfWorkspaces;
    if ( m_iNumberOfWorkspaces == 0 )
        m_pWorkspaceMenu->setEnabled(false);
    m_pTabWidget->closeTabAt();
}
void Thesis::UI::MainWindow::newContinousFunction()
{
    cLOG() ; 
    Thesis::UI::NewContinousFunctionDialog dialog ; 
    int iRet = dialog.exec();
    if ( iRet == QDialog::Accepted ) {
        QString functionEquation = dialog.fuction() ; 
        QStringList vars = dialog.variables();
        int dimension = dialog.dimensions();
        LOG("Created function :" << functionEquation <<" with variables:"<< vars );
        Thesis::FunctionsProxy prx( functionEquation,vars,dimension,FunctionsProxy::eContinous ) ; 
        prx.setColor(dialog.color());
        m_pTabWidget->addFunction(prx);
    }
    else {
        LOG("Dialog was rejected, hence no function added");
        return ; 
    }
}
void Thesis::UI::MainWindow::workspaceSettings()
{
    cLOG() ; 
    Thesis::UI::TabWidgetItem *pCurrent = qobject_cast< Thesis::UI::TabWidgetItem * >(m_pTabWidget->currentWidget() ) ; 
    Q_ASSERT( pCurrent != NULL ) ; 
    Thesis::UI::WorkspaceSettingsDialog dlg( pCurrent ); 
    
    dlg.exec();
    if ( dlg.result() == QDialog::Accepted ) {
        const Thesis::UI::RangeTab *pRange = dlg.rangeSettings(); 
        pCurrent->plotProxy()->changeRange( pRange->xMin(), pRange->xMax(),pRange->yMin(), pRange->yMax() );
    }
}
void Thesis::UI::MainWindow::newMixedFunction()
{
    cLOG() ; 
    Thesis::UI::NewFunctionMixedDialog dlg ;
    dlg.exec() ; 
    if ( dlg.result() == QDialog::Accepted ) {
        std::vector<QStringList> list = dlg.funcDesc();
        Thesis::FunctionsProxy prx ( list ) ; 
        m_pTabWidget->addFunction( prx );
    }
}
void Thesis::UI::MainWindow::newFunctionFromFile(){
    QString fileName = QFileDialog::getOpenFileName ( this , tr("choose file to open"),QDir::currentPath(),tr("Function files( *.fnt)" ) );
    if ( fileName.isEmpty()){
        LOG("Not opening file");
        return ; 
    }
    QFile f ( fileName);
    Thesis::FunctionsProxy::Type _type ; 
    if ( f.open(QIODevice::ReadOnly)){
        QByteArray decision= f.readLine() ; 
        if ( decision.contains("mixed"))
            _type = Thesis::FunctionsProxy::eMixed;
        else if ( decision.contains("discrete"))
            _type = Thesis::FunctionsProxy::eDiscrete;
        f.close() ;
        Thesis::FunctionsProxy prx ( fileName, _type) ; 
        m_pTabWidget->addFunction(prx);
    }
    else{
        LOG("Unable to open file:" << fileName);
    }

}
void Thesis::UI::MainWindow::zoomIn()
{
    TabWidgetItem *pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget()); 
    pTab->plotProxy()->zoomIn();
}
void Thesis::UI::MainWindow::zoomOut()
{
    TabWidgetItem *pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget()); 
    pTab->plotProxy()->zoomOut();
}

void Thesis::UI::MainWindow::convolutionOperation()
{
    int i = m_pTabWidget->count();
    TabWidgetItem *pTab=NULL;
    QStringList aa ; 
    QMap<QString,const fl::FunctionBase*> tempMap ; 
    Thesis::UI::ConvolutionPicker picker ( this ) ; 
    for ( int j=0 ; j < i ; ++j)
    {
        pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->widget(j)); 
        PlotWidgetProxy::FunctionsPlotMapType map = pTab->plotProxy()->plotMap() ; 
        QList<fl::FunctionBase*> keysaa = map.keys();
        Q_FOREACH ( const fl::FunctionBase *pFunc, keysaa ) {
            tempMap[pFunc->name().c_str()] = pFunc ; 
            aa.push_back(QString( pFunc->name().c_str()) );
        }
        picker.addFunctions(j+1,aa);
        aa.clear();
    }
    if ( picker.show() == QDialog::Accepted ) {
        TabWidgetItem *pTab ; 
        if ( picker.whereToAdd() != Thesis::UI::ConvolutionPicker::eCurrentWorkspace ){
            newTab(true);
        }
        QStringList listOfFunctionsToAdd = picker.selectedFunctions() ; 
        QList<const fl::FunctionBase*> pFunctionList; 
        foreach ( QString fName, listOfFunctionsToAdd ) {
			const fl::FunctionBase* pF = tempMap[fName];
			if ( pF == NULL ){
				qDebug() << "Why are you giving me NULL for ? Dummy"; 
			}
			else
				pFunctionList.push_back(pF);
        }
		if ( pFunctionList.size() != 2 ){
			LOG("Incorrect number of functions to calculate splot. Bye-bye");
		}
        pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget());
        ConvolutionOperation * pOperation = NULL ; 
        QAction *pObj = qobject_cast< QAction* >(sender());
        if ( pObj == Thesis::Actions::convolutionAddOperation() )
            pOperation = new ConvolutionAdd() ; 
        else if ( pObj == Thesis::Actions::convolutionMinusOperation() ) 
            pOperation = new ConvolutionMinus() ; 
		else if ( pObj == Thesis::Actions::convolutionTimesOperation())
			pOperation = new ConvolutionTimes() ; 
		else if ( pObj == Thesis::Actions::convolutionDevideOperation())
			pOperation = new ConvolutionDiv() ; 
		else
			pOperation = NULL ; 
		
		if ( pOperation== NULL){
			LOG("Dummy U're trying to give me NULL as IOperation.Not cool ;(");
			return ; 
		}
        pTab->addFunctionAndOperation(pFunctionList,pOperation );
    }
}
void Thesis::UI::MainWindow::approximate()
{
	cLOG();
	TabWidgetItem *pTab=NULL;
	ApproximateDialog dlg ; 
	QList<fl::FunctionBase *> allFuncs ; 
	int i = m_pTabWidget->count();
	for ( int j=0 ; j < i ; ++j)
	{
		pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->widget(j)); 
		PlotWidgetProxy::FunctionsPlotMapType map = pTab->plotProxy()->plotMap() ; 
		allFuncs.append(map.keys());
	}
	dlg.setAllFunctions(allFuncs);
	pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget());
	PlotWidgetProxy::FunctionsPlotMapType map = pTab->plotProxy()->plotMap() ; 
	dlg.setCurrentWorkspaceFunctions(map.keys());
	
	if ( dlg.show() == QDialog::Accepted ) {
		pTab = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget());
		fl::Function2D::Function2DBase * aa = dlg.resultFunction() ;
		if ( aa == NULL )
			return ; 
		fl::FunctionBase * pF = dynamic_cast<fl::FunctionBase *>(aa);
		pTab->addFunction(pF);
	}
}

void Thesis::UI::MainWindow::keyPressEvent( QKeyEvent * p)
{
    int k = p->key();
    if ( k == Qt::Key_Left || k == Qt::Key_Right || k == Qt::Key_Down ||k == Qt::Key_Up ){
        TabWidgetItem *pItem = qobject_cast<TabWidgetItem*>(m_pTabWidget->currentWidget());
        if ( pItem != NULL ){
            pItem->keyPressEvent(p);
        }
    }
}