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

#ifndef TABWIDGETITEM_H
#define TABWIDGETITEM_H

#include <QWidget>
#include <boost/shared_ptr.hpp>
#include <QPointer>

class QScrollBar;
class QVBoxLayout ; 
namespace Thesis{
    namespace UI{
        class PlotWidgetProxy ; 
        class TabWidgetItem : public QWidget
        {
            Q_OBJECT
            public:
                TabWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);
                virtual ~TabWidgetItem();
                const QString& text() const { return m_text ; }
                void settext( const QString & _rhs ) { m_text = _rhs ; } 
                
                const int& numberOfPlots() const { return m_NumberOfPlots  ; }
                void setNumberOfPlots( int _rhs ) { m_NumberOfPlots  = _rhs ; } 
                
                PlotWidgetProxy * plotProxy() ;
                
            protected:
                QString m_text ; 
                boost::shared_ptr<PlotWidgetProxy> m_pPlotProxy ; 
                QPointer<QVBoxLayout> m_pLayout ;
                QPointer<QLayout> m_pPlotAndOtherWidgets ; 
                QPointer<QScrollBar> m_pVerticalScrollBar ; 
                QPointer<QScrollBar> m_pHorizontalScrollBar ; 
                int m_NumberOfPlots ; 
            private slots:
                void plotAboutToChange() ; 
                void plotChaged() ; 
        };
    }
}

#endif // TABWIDGETITEM_H
