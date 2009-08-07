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

#ifndef THESIS_ACTIONS_H
#define THESIS_ACTIONS_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <qglobal.h>

class QAction ; 

namespace Thesis {

    /**
     * \class	Actions
     *
     * \brief	Actions. 
     *
     * \author	Bartosz Taczala
     * \date	2009-08-07
    **/

    class Actions
    {
        public:
            ~Actions() ; 
            static QAction * quitAction() { Actions * pInstance = instance() ; return pInstance->m_pquit.get() ; }
            static QAction * newTabAction() { Actions * pInstance = instance() ; return pInstance->m_pnewTab.get() ; }
            //static QAction * newDiscreteFunctionAction() { Actions * pInstance = instance() ; return pInstance->m_pnewDiscreteFunction.get() ; }
            static QAction * newDiscreteFromFileAction() { Actions * pInstance = instance() ; return pInstance->m_pnewDiscreteFromFile.get() ; }
            static QAction * newMixedFunctionAction() { Actions * pInstance = instance() ; return pInstance->m_pnewMixedFunction.get() ; }
            static QAction * newContinousFunctionAction() { Actions * pInstance = instance() ; return pInstance->m_pnewContinousFunction.get() ; }
            static QAction * aboutAction() { Actions * pInstance = instance() ; return pInstance->m_pabout.get() ; }
            static QAction * aboutQtAction() { Actions * pInstance = instance() ; return pInstance->m_paboutQt.get() ; }
            static QAction * closeWorkspaceAction() { Actions * pInstance = instance() ; return pInstance->m_pcloseWorkspace.get() ; }
            static QAction * workspaceSettingsAction() { Actions * pInstance = instance() ; return pInstance->m_pworkspaceSettings.get() ; }
            static QAction * newMixedFromFileAction() { Actions * pInstance = instance() ; return pInstance->m_pnewMixedFromFile.get() ; }
            static QAction * workspaceZoomOut() { Actions * pInstance = instance() ; return pInstance->m_pworkspaceZoomOut.get() ; }
            static QAction * workspaceZoomIn() { Actions * pInstance = instance() ; return pInstance->m_pworkspaceZoomIn.get() ; }
        private:
            Actions() ; 
            static Actions* instance() ;
            Q_DISABLE_COPY(Actions);
            void addDefaultActions() ;
            boost::shared_ptr<QAction> m_pquit ; 
            boost::shared_ptr<QAction> m_pnewTab ; 
            boost::shared_ptr<QAction> m_pnewDiscreteFromFile ; 
            boost::shared_ptr<QAction> m_pnewMixedFromFile ; 

            
            boost::shared_ptr<QAction> m_pnewMixedFunction ; 
            boost::shared_ptr<QAction> m_pnewContinousFunction ; 
            boost::shared_ptr<QAction> m_pabout ; 
            boost::shared_ptr<QAction> m_paboutQt ;
            boost::shared_ptr<QAction> m_pcloseWorkspace ; 
            
            boost::shared_ptr<QAction> m_pworkspaceSettings ;
            
            boost::shared_ptr<QAction> m_pworkspaceZoomOut ;
            boost::shared_ptr<QAction> m_pworkspaceZoomIn ;


            

            
    };
}

#endif // THESIS_ACTIONS_H
