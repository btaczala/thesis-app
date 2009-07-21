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

#ifndef ADDFUNCTIONMIXEDDIALOG_H
#define ADDFUNCTIONMIXEDDIALOG_H

#include <QDialog>
#include <boost/shared_ptr.hpp>
#include <QItemDelegate>
#include <vector>

namespace Ui{
    class newFunctionMixed ;
}
namespace Thesis{
    namespace UI{

        class NewFunctionMixedDialog : public QDialog
        {
            Q_OBJECT
            public:
                NewFunctionMixedDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);
                virtual void done(int );
                virtual void accept();
                virtual void reject();
                const std::vector<QStringList> & funcDesc() const { return m_FunctionsDesc ; } 
            private:
                boost::shared_ptr<Ui::newFunctionMixed> m_pForm ; 
                int m_iCurrentRow ; 
                
                std::vector<QStringList> m_FunctionsDesc ; 
                
            private slots:
                void addRow() ;
                void deleteRow() ;
                
        };
//         class ComboBoxDelegate : public QItemDelegate{
//             Q_OBJECT
//             public:
//                 ComboBoxDelegate(QObject* parent = 0);
//                 virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;
//                 virtual void setEditorData(QWidget* editor, const QModelIndex& index) const;
//                 virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const;
//                 virtual void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const;
//         };
    }
}

#endif // ADDFUNCTIONMIXEDDIALOG_H
