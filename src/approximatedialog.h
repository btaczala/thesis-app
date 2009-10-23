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

#ifndef THESIS_UI_APPROXIMATEDIALOG_H
#define THESIS_UI_APPROXIMATEDIALOG_H

#include <QPointer>
#include <QDialog>
#include <boost/shared_ptr.hpp>

class QtColorPicker;
class KPlotWidget;
namespace Ui{
    class ApproximateDialogUI ; 
}
namespace fl{
	class FunctionBase ; 
	namespace Function2D{
		class FunctionContinous ; 
		class Function2DBase;
	}
}
namespace Thesis {
    namespace UI {
        class ApproximateDialog : public QDialog
        {
            Q_OBJECT
            public:
				ApproximateDialog( QWidget *pParent = NULL);
				~ApproximateDialog() ; 
				void setCurrentWorkspaceFunctions(const QList<fl::FunctionBase*> & functionList ) { m_currentWorkspaceFunctions = functionList;}
				void setAllFunctions(const QList<fl::FunctionBase*> & functionList ) { m_allWorkspaceFunctions = functionList ; } 
				int show() ; 
				fl::Function2D::Function2DBase * resultFunction(); 
            protected:
                boost::shared_ptr<Ui::ApproximateDialogUI> m_pDialog ; 
				QList<fl::FunctionBase*> m_currentWorkspaceFunctions;
				QList<fl::FunctionBase*> m_allWorkspaceFunctions;
				fl::Function2D::Function2DBase  * m_calculatedFunc ;

				boost::shared_ptr<KPlotWidget> m_pKPlotWidget ; 

				fl::Function2D::Function2DBase * proxy() ; 
			private slots:
				void populateList(int) ; 
				void preview() ;

        };
    }

}

#endif // THESIS_UI_APPROXIMATEDIALOG_H
