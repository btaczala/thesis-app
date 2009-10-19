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

#ifndef THESIS_UI_WORKSPACESETTINGSDIALOG_H
#define THESIS_UI_WORKSPACESETTINGSDIALOG_H

#include <QDialog>
#include <QPointer>
#include <boost/shared_ptr.hpp>


class QDialogButtonBox;
class QTabWidget;

namespace Ui{
    class RangeForm ; 
}

namespace Thesis {

    namespace UI {
        class TabWidgetItem ; 
        class RangeTab ;

        /**
         * \class	WorkspaceSettingsDialog
         *
         * \brief	Dialog for setting the workspace settings. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class WorkspaceSettingsDialog : public QDialog
        {
            Q_OBJECT
            public:

                /**
                 * \fn	WorkspaceSettingsDialog( TabWidgetItem * pTabItem, QWidget *pParent = NULL )
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pTabItem	If non-null, the tab item. 
                 * \param	pParent		If non-null, the parent. 
                **/

                WorkspaceSettingsDialog( TabWidgetItem * pTabItem, QWidget *pParent = NULL ) ; 

                /**
                 * \fn	const RangeTab * rangeSettings() const
                 *
                 * \brief	Range settings. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	null if it fails, else. 
                **/

                const RangeTab * rangeSettings() const { return m_pRangeTab.get() ; } 
            private:
                QPointer<QTabWidget> m_pTabWidget ; 
                boost::shared_ptr<RangeTab> m_pRangeTab ;
                QPointer<QDialogButtonBox> m_pButtonBox;
                TabWidgetItem *m_pTabItem ; 
                
                friend class RangeTab ; 
                
        };
        class RangeTab : public QWidget {
            Q_OBJECT
            public:

                /**
                 * \fn	RangeTab (WorkspaceSettingsDialog *pParent )
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pParent	If non-null, the parent. 
                **/

                RangeTab (WorkspaceSettingsDialog *pParent ) ;  

                /**
                 * \fn	double xMin() const
                 *
                 * \brief	X coordinate minimum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double xMin() const ; 

                /**
                 * \fn	double xMax() const
                 *
                 * \brief	X coordinate maximum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double xMax() const ;

                /**
                 * \fn	double yMin() const
                 *
                 * \brief	Y coordinate minimum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double yMin() const ; 

                /**
                 * \fn	double yMax() const
                 *
                 * \brief	Y coordinate maximum. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                double yMax() const ; 
            public:
                WorkspaceSettingsDialog * m_pParent ; 
                Ui::RangeForm * m_pForm ;                 
        };
    }

}

#endif // THESIS_UI_WORKSPACESETTINGSDIALOG_H
