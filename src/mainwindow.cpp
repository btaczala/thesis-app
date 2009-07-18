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
#include "functionsproxy.h"

#include <QStatusBar>
#include <QMenuBar>

#include <kplotwidget.h>
#include <QApplication>
#include <QLabel>

using namespace Thesis::UI;

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags flags) : 
QMainWindow(parent, flags)
{
    cLOG() ;
    setWindowTitle( Thesis::Strings::applicationName );
    
    createWidgets();
    createUI();
    initSignals();
    
    setStatusBarStatus(tr( "Program is ready to use" ),false);
    
    setWindowState(Qt::WindowMaximized);
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
//     m_pFileMenu->addAction(Thesis::Actions::action(Thesis::Actions::Names::scNewFunctionActionName));
    m_pFileMenu->addAction( Thesis::Actions::newTabAction() );
    
    m_pFileMenu->addSeparator();
    m_pFileMenu->addAction(Thesis::Actions::quitAction());
    
//     m_pWorkspaceMenu
    m_pWorkspaceNewFunctionMenu->addAction(Thesis::Actions::newContinousFunctionAction());
    m_pWorkspaceNewFunctionMenu->addAction(Thesis::Actions::newDiscreteFunctionAction());
    m_pWorkspaceNewFunctionMenu->addAction(Thesis::Actions::newMixedFunctionAction());
    m_pWorkspaceMenu->addMenu(m_pWorkspaceNewFunctionMenu);
    
    m_pWorkspaceMenu->addAction( Thesis::Actions::closeWorkspaceAction() );
    
    m_pAboutMenu->addAction(Thesis::Actions::aboutAction());
    m_pAboutMenu->addAction(Thesis::Actions::aboutQtAction());
    
    m_pMenuBar->addMenu( m_pFileMenu);
    
    
    m_pMenuBar->addMenu( m_pWorkspaceMenu);
    m_pMenuBar->addMenu( m_pAboutMenu);
    
    
    m_pStatusBar->addPermanentWidget(m_pStatusBarWidget);
    
    
    setStatusBar(m_pStatusBar);
    setMenuBar(m_pMenuBar);
    setCentralWidget(m_pTabWidget);
    setWindowIcon(QIcon(":/app_icon.png"));
    
    if ( m_pTabWidget->count() == 0 ) 
        m_pWorkspaceMenu->setEnabled(false);
    
//     m_pTabWidget->addTab(/*pProxy->widget(),"test"*/);
    
}
void MainWindow::createWidgets()
{
    cLOG() ;
    m_pStatusBar = new QStatusBar(this) ; 
    m_pStatusBarWidget = new QLabel(m_pStatusBar);
    m_pMenuBar = new QMenuBar(this);
    m_pFileMenu = new QMenu( tr("&File"),m_pMenuBar );
    /// WORKSPACE menu
    m_pWorkspaceMenu = new QMenu ( tr("&Workspace"), m_pMenuBar ) ; 
    m_pWorkspaceNewFunctionMenu = new QMenu ( tr("&New function") , m_pWorkspaceMenu) ; 
    
    
    m_pAboutMenu = new QMenu ( tr("&About"),m_pMenuBar ) ; 
        
    m_pTabWidget = new TabWidget(this);    
}

void MainWindow::initSignals()
{
    cLOG() ;
    connect ( Thesis::Actions::quitAction(),SIGNAL(triggered()),this,SLOT(closeApp()));
    connect ( Thesis::Actions::newTabAction(),SIGNAL(triggered()), this,SLOT(newTab()));
    
    connect( Thesis::Actions::newContinousFunctionAction(),SIGNAL(triggered()),this,SLOT(newContinousFunction()));
    
    connect ( Thesis::Actions::aboutQtAction(), SIGNAL(triggered()), this, SLOT(aboutQt()));
    connect ( Thesis::Actions::aboutAction(), SIGNAL(triggered()), this, SLOT(about()));
    
    connect ( Thesis::Actions::closeWorkspaceAction(),SIGNAL(triggered()),this,SLOT(closeCurrentTab()));
}

void MainWindow::setStatusBarStatus(const QString& _status, bool isWorking)
{
    Q_UNUSED(isWorking);
    LOG(" _status=" << _status);
    m_pStatusBarWidget->setText(_status);
    m_pStatusBarWidget->setPixmap(QPixmap(":/ok.png")) ;
}

void MainWindow::closeApp()
{
    cLOG() ;
    QMainWindow::close();
}

void Thesis::UI::MainWindow::newTab()
{
    cLOG() ; 
    m_pTabWidget->addTab();
    setStatusBarStatus(tr("New Workspace added"),false);
    m_pWorkspaceMenu->setEnabled(true);
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
        m_pTabWidget->addFunction(prx);
    }
    else {
        LOG("Dialog was rejected, hence no function added");
        return ; 
    }
}

void Thesis::UI::MainWindow::newDiscreteFunction()
{
}

