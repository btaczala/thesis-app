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

#ifndef FUNCTIONINFODIALOG_H
#define FUNCTIONINFODIALOG_H


#include <QDialog>
#include <boost/shared_ptr.hpp>

namespace Ui{
    class FunctionDialogUI ; 
}
namespace fl{
    class FunctionBase ; 
}
class QTreeWidgetItem ; 
namespace Thesis{
    namespace UI{
        class FunctionInfoDialog : public QDialog
        {
            Q_OBJECT
            public:
                FunctionInfoDialog(const fl::FunctionBase *pFun =NULL,  QWidget *pParent=NULL) ; 
                void setFunction( const fl::FunctionBase * pFun ) ; 
                int show() ; 
                QString oldFunctionName() const ; 
                QString newFunctionName() const ; 
            private:
                boost::shared_ptr<Ui::FunctionDialogUI> m_pDialog ; 
                const fl::FunctionBase * m_pFun;
            private slots:
                void listWidgetItemDoubleClicked(QTreeWidgetItem*,int) ; 
                
        };
    }
}

#endif // FUNCTIONINFODIALOG_H
