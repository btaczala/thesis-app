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

        class WorkspaceSettingsDialog : public QDialog
        {
            Q_OBJECT
            public:
                WorkspaceSettingsDialog( TabWidgetItem * pTabItem, QWidget *pParent = NULL ) ; 
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
                RangeTab (WorkspaceSettingsDialog *pParent ) ;  
                double xMin() const ; 
                double xMax() const ;
                double yMin() const ; 
                double yMax() const ; 
            public:
                WorkspaceSettingsDialog * m_pParent ; 
                Ui::RangeForm * m_pForm ; 
                
        };
            

    }

}

#endif // THESIS_UI_WORKSPACESETTINGSDIALOG_H
