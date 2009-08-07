/*/*
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

#ifndef THESIS_UI_TABWIDGET_H
#define THESIS_UI_TABWIDGET_H

#include <QTabWidget>
#include <boost/shared_ptr.hpp>

#include "functionsproxy.h"

namespace Thesis {
    namespace UI {

        /**
         * \class	TabWidget
         *
         * \brief	Tab widget. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class TabWidget : public QTabWidget
        {
            Q_OBJECT
            public:

                /**
                 * \fn	TabWidget(QWidget* parent = 0)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	parent	If non-null, the parent. 
                **/

                TabWidget(QWidget* parent = 0);

                /**
                 * \fn	virtual ~TabWidget()
                 *
                 * \brief	Finaliser. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual ~TabWidget();

                /**
                 * \fn	void addTab()
                 *
                 * \brief	Adds  tab
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void addTab() ; 

                /**
                 * \fn	void closeTabAt( int index =-1 )
                 *
                 * \brief	Closes a tab at. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	index	Zero-based index of the. 
                **/

                void closeTabAt( int index =-1 ); 
                
                /**
                    \fn adds function to tab. 
                    \param index defines to which tab add a function
                */
                void addFunction (FunctionsProxy & fProxy, int index=-1);
                
                
            protected:
                int m_currentWorkspace ; 
                std::vector<bool> m_isWorkspaceUsed ; 
                
        };
    
    }
}

#endif // THESIS_UI_TABWIDGET_H*/
