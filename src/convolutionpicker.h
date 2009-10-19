/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef THESIS_UI_CONVOLUTIONPICKER_H
#define THESIS_UI_CONVOLUTIONPICKER_H

#include <QDialog>
#include <boost/shared_ptr.hpp>
#include "ui_convolutionpicker.h"

namespace Thesis{
    namespace UI{

        class ConvolutionPicker : public QDialog
        {
            Q_OBJECT
            public:
                enum WhereToAdd{
                    eCurrentWorkspace=0,
                    eCreateNewWorkspace
                };
                ConvolutionPicker ( QWidget* parent = 0, Qt::WindowFlags f = 0 );
                virtual void accept();
                virtual void reject();
                void addFunctions ( int index, const QStringList & names ) ; 
                int  show() ; 
                
                const QStringList & selectedFunctions() const { return m_selectedFunctions ; } 
                const WhereToAdd whereToAdd() const { return m_whereToAdd ; } 
                
            private:
                void populateTreeWidget(int index = -1 ) ; 
                
                boost::shared_ptr<Ui::ConvolutionPicker> m_pForm ; 
                QMap<int,QStringList> m_functions ; 
                QStringList m_selectedFunctions ; 
                WhereToAdd m_whereToAdd ; 
                
            private slots:
                void comboBoxValueChanged( const QString & ) ; 
                void comboBoxValueChanged( int ) ;
                
        };
    }
}

#endif // THESIS_UI_CONVOLUTIONPICKER_H
