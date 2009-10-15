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
#include "plotwidget.h"

class QListWidgetItem;
class QPushButton;
class QButtonGroup;
class QScrollBar;
class QVBoxLayout ; 
class QHBoxLayout ; 
class QListWidget ; 

class IOperation ; 
namespace fl{
    class FunctionBase ; 
}
namespace Thesis{
    namespace UI{
        class PlotWidgetProxy ; 

        /**
         * \class	TabWidgetItem
         *
         * \brief	Tab widget item. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class TabWidgetItem : public QWidget
        {
            Q_OBJECT
            public:

                /**
                 * \fn	TabWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	parent	If non-null, the parent. 
                 * \param	f		The. 
                **/

                TabWidgetItem(QWidget* parent = 0, Qt::WindowFlags f = 0);

                /**
                 * \fn	virtual ~TabWidgetItem()
                 *
                 * \brief	Finaliser. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual ~TabWidgetItem();

                /**
                 * \fn	const QString& text() const
                 *
                 * \brief	Texts this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                const QString& text() const { return m_text ; }

                /**
                 * \fn	void settext( const QString & _rhs )
                 *
                 * \brief	Settexts. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	_rhs	The right hand side. 
                **/

                void settext( const QString & _rhs ) { m_text = _rhs ; } 

                /**
                 * \fn	const int& numberOfPlots() const
                 *
                 * \brief	Number of plots. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	The total number of plots. 
                **/

                const int& numberOfPlots() const { return m_NumberOfPlots  ; }

                /**
                 * \fn	void setNumberOfPlots( int _rhs )
                 *
                 * \brief	Sets a number of plots. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	_rhs	The right hand side. 
                **/

                void setNumberOfPlots( int _rhs ) { m_NumberOfPlots  = _rhs ; } 

                /**
                 * \fn	PlotWidgetProxy * plotProxy()
                 *
                 * \brief	Plot proxy. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	null if it fails, else. 
                **/

                PlotWidgetProxy * plotProxy() ;

                /**
                 * \fn	void addFunction( fl::FunctionBase* pFunction, const QColor & color)
                 *
                 * \brief	Adds a function to 'color'. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pFunction	If non-null, the function. 
                 * \param	color		The color. 
                **/

                void addFunction( fl::FunctionBase* pFunction, const QColor & color) ; 
                
                
                void addFunctionAndOperation( const QList<const fl::FunctionBase*> & list, IOperation * pOperation ) ; 
                
            protected:
                QString m_text ; 
                boost::shared_ptr<PlotWidgetProxy> m_pPlotProxy ; 
                QPointer<QHBoxLayout> m_pLayout ;
                QPointer<QVBoxLayout> m_pLeftLayout ;
                QPointer<QPushButton> m_pDeleteButton ; 
                QPointer<QListWidget> m_pListWidget ; 
                int m_NumberOfPlots ; 
            private slots:

                /**
                 * \fn	void functionAdded( const FunctionInfo & fInfo )
                 *
                 * \brief	Function added. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	fInfo	The information. 
                **/

                void functionAdded( const FunctionInfo & fInfo ) ; 

                /**
                 * \fn	void deleteFunction()
                 *
                 * \brief	Deletes a function. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void deleteFunction() ; 

                /**
                 * \fn	void itemDoubleClicked ( const QListWidgetItem * pItem )
                 *
                 * \brief	Item double clicked. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	pItem	If non-null, the item. 
                **/

                void itemDoubleClicked ( const QListWidgetItem * pItem ) ; 
        };
    }
}

#endif // TABWIDGETITEM_H
