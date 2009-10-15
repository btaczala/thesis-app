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

class QtColorPicker;
namespace Ui{
    class PasswordDialog ; 
}
class QTimer ; 
namespace Thesis {

    namespace UI {

        /**
         * \class	NewContinousFunctionDialog
         *
         * \brief	Dialog for setting the new continous function. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class NewContinousFunctionDialog : public QDialog
        {
            Q_OBJECT
            public:

                /**
                 * \fn	NewContinousFunctionDialog(QWidget* parent = 0, Qt::WindowFlags f = 0)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	parent	If non-null, the parent. 
                 * \param	f		The. 
                **/

                NewContinousFunctionDialog(QWidget* parent = 0, Qt::WindowFlags f = 0); 

                /**
                 * \fn	virtual ~NewContinousFunctionDialog()
                 *
                 * \brief	Finaliser. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual ~NewContinousFunctionDialog() {};

                /**
                 * \fn	virtual void done(int done)
                 *
                 * \brief	Dones. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	done	The done. 
                **/

                virtual void done(int done);

                /**
                 * \fn	virtual void accept()
                 *
                 * \brief	Accepts this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual void accept();

                /**
                 * \fn	const QString fuction() const
                 *
                 * \brief	Fuctions this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                const QString  fuction() const ;

                /**
                 * \fn	const QStringList variables() const
                 *
                 * \brief	Variables this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                const QStringList variables() const ; 

                /**
                 * \fn	int dimensions() const
                 *
                 * \brief	Dimensions this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                int dimensions() const ; 

                /**
                 * \fn	QColor color() const
                 *
                 * \brief	Colors this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	. 
                **/

                QColor color() const ; 
            protected:
                boost::shared_ptr<Ui::PasswordDialog> m_pDialog ; 
                QPointer<QTimer> m_pTimer ; 
                QPointer<QtColorPicker> m_pColorPicker ; 
            private slots:
                void customRangeChecked( bool checked ) ; 
                void checkIfOk() ; 
        };

    }

}

#endif // THESIS_UI_NEWCONTINOUSFUNCTIONDIALOG_H
