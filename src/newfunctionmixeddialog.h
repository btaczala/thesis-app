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

        /**
         * \class	NewFunctionMixedDialog
         *
         * \brief	Dialog for setting the new function mixed. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class NewFunctionMixedDialog : public QDialog
        {
            Q_OBJECT
            public:

                /**
                 * \fn	NewFunctionMixedDialog(QWidget* parent = 0, Qt::WindowFlags f = 0)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	parent	If non-null, the parent. 
                 * \param	f		The. 
                **/

                NewFunctionMixedDialog(QWidget* parent = 0, Qt::WindowFlags f = 0);

                /**
                 * \fn	virtual void done(int )
                 *
                 * \brief	Dones. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param		The. 
                **/

                virtual void done(int );

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
                 * \fn	virtual void reject()
                 *
                 * \brief	Rejects this object. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                virtual void reject();

                /**
                 * \fn	const std::vector<QStringList> & funcDesc() const
                 *
                 * \brief	Func description. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \return	A list of. 
                **/

                const std::vector<QStringList> & funcDesc() const { return m_FunctionsDesc ; } 
            private:
                boost::shared_ptr<Ui::newFunctionMixed> m_pForm ; 
                int m_iCurrentRow ; 
                std::vector<QStringList> m_FunctionsDesc ; 
            private:
                void parse() ; 
            public:
            private slots:

                /**
                 * \fn	void addRow()
                 *
                 * \brief	Adds  row
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void addRow() ;

                /**
                 * \fn	void deleteRow()
                 *
                 * \brief	Deletes a row. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void deleteRow() ;
        };
    }
}

#endif // ADDFUNCTIONMIXEDDIALOG_H
