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

#include "actions.h"
#include <QAction>
#include "commons.h"

using namespace Thesis;


Actions::Actions()
{
    cLOG() ;
    addDefaultActions();
}

Actions::~Actions()
{
    cLOG() ;
}


Actions* Actions::instance()
{
    cLOG() ;
    static std::auto_ptr<Actions> apInstance ( new Actions()) ; 
    return apInstance.get();
}

void Actions::addDefaultActions()
{   
    LOG("adding default actions") ; 
    
    m_pquit.reset( new QAction(NULL) ) ;
    m_pquit->setText(QObject::tr("Quit") );
    m_pquit->setShortcut( QKeySequence( "Ctrl+X") );
    m_pquit->setIcon(QIcon(":/exit.png"));
    
    m_pnewTab.reset( new QAction(NULL) ) ; 
    m_pnewTab->setText(QObject::tr("New Tab") ) ;
    m_pnewTab->setShortcut( QKeySequence( "Ctrl+N") );
    m_pnewTab->setIcon(QIcon(":/new.png"));
    
    m_pabout.reset( new QAction(NULL) ) ; 
    m_pabout->setText(QObject::tr("About") );
    m_paboutQt.reset( new QAction(NULL) ) ; 
    m_paboutQt->setText(QObject::tr("About Qt ") );
    m_paboutQt->setIcon(QIcon(":/qt-logo.png"));
    
    m_pnewContinousFunction.reset( new QAction(NULL) ) ; 
    m_pnewContinousFunction->setText(QObject::tr("New continous function") );
    
    m_pnewDiscreteFromFile.reset( new QAction(NULL) ) ; 
//     m_pnewDiscreteFunction
    m_pnewDiscreteFromFile->setText(QObject::tr("New discrete function from file") );
    
    m_pnewMixedFunction.reset ( new QAction(NULL) ) ; 
    m_pnewMixedFunction->setText(QObject::tr("New mixed function") );
    
    m_pcloseWorkspace.reset( new QAction ( NULL) ) ; 
    m_pcloseWorkspace->setText( QObject::tr("Close current workspace") );
    m_pcloseWorkspace->setIcon(QIcon(":/cancel.png"));
    
    m_pworkspaceSettings.reset( new QAction(NULL) ) ;
    m_pworkspaceSettings->setText( QObject::tr("Workspace settings") );
    m_pworkspaceSettings->setIcon(QIcon(":/tool.png"));
    
    
}
