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

#ifndef THESIS_UI_NEWCONTINOUSFUNCTIONDIALOG_H
#define THESIS_UI_NEWCONTINOUSFUNCTIONDIALOG_H

#include <QPointer>
#include <QDialog>
#include <boost/shared_ptr.hpp>

namespace Ui{
    class PasswordDialog ; 
}
class QTimer ; 
namespace Thesis {

    namespace UI {

        class NewContinousFunctionDialog : public QDialog
        {
            Q_OBJECT
            public:
                NewContinousFunctionDialog(QWidget* parent = 0, Qt::WindowFlags f = 0); 
                virtual ~NewContinousFunctionDialog() {};
                virtual void done(int done);
                virtual void accept();
                const QString  fuction() const ;
                const QStringList variables() const ; 
                int dimensions() const ; 
            protected:
                boost::shared_ptr<Ui::PasswordDialog> m_pDialog ; 
                QPointer<QTimer> m_pTimer ; 
            private slots:
                void customRangeChecked( bool checked ) ; 
                void checkIfOk() ; 
        };

    }

}

#endif // THESIS_UI_NEWCONTINOUSFUNCTIONDIALOG_H
