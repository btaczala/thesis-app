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

#ifndef THESIS_MAINWINDOW_H
#define THESIS_MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

class KPlotWidget ; 
class TabWidget ; 
class QLabel ; 
class QToolBar ; 

namespace Thesis {
    namespace UI {
        class TabWidget ; 

        /**
         * \class	MainWindow
         *
         * \brief	Form for viewing the main. 
         *
         * \author	Bartosz Taczala
         * \date	2009-08-07
        **/

        class MainWindow : public QMainWindow
        {
            Q_OBJECT
            public:

                /**
                 * \fn	MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0)
                 *
                 * \brief	Constructor. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	parent	If non-null, the parent. 
                 * \param	flags	The flags. 
                **/

                MainWindow(QWidget* parent = 0, Qt::WindowFlags flags = 0);

                /**
                 * \fn	~MainWindow()
                 *
                 * \brief	Finaliser. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                ~MainWindow() ; 
                
            public slots:

                /**
                 * \fn	void closeApp()
                 *
                 * \brief	Closes the application. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void closeApp() ; 

                /**
                 * \fn	void newTab()
                 *
                 * \brief	New tab. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void newTab( bool setFocus = false);

                /**
                 * \fn	void about()
                 *
                 * \brief	Abouts this application. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void about() ; 

                /**
                 * \fn	void aboutQt()
                 *
                 * \brief	About Qt framework
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void aboutQt();

                /**
                 * \fn	void closeCurrentTab()
                 *
                 * \brief	Closes the current tab. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void closeCurrentTab();

                /**
                 * \fn	void newContinousFunction()
                 *
                 * \brief	New continous function. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void newContinousFunction();

                /**
                 * \fn	void newDiscreteFunctionFromFile()
                 *
                 * \brief	New discrete function from file. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void newDiscreteFunctionFromFile() ; 

                /**
                 * \fn	void newMixedFunction()
                 *
                 * \brief	New mixed function. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void newMixedFunction() ; 

                /**
                 * \fn	void newMixedFunctionFromFile()
                 *
                 * \brief	New mixed function from file. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void newMixedFunctionFromFile();

                /**
                 * \fn	void workspaceSettings()
                 *
                 * \brief	Workspace settings. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void workspaceSettings() ; 

                /**
                 * \fn	void zoomIn()
                 *
                 * \brief	Zooms in current workspace widget.
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void zoomIn();

                /**
                 * \fn	void zoomOut()
                 *
                 * \brief	Zooms out current workspace widget.
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                **/

                void zoomOut();
                
                /**
                 * \fn  void convolutionOperation()
                 *
                 * \brief   Zooms out current workspace widget.
                 *
                 * \author  Bartosz Taczala
                 * \date    2009-08-07
                **/
                void convolutionOperation() ; 
            private:
                Q_DISABLE_COPY(MainWindow) ;
                
                
                /** Functions **/
                
                /**
                    \fn   void createUI() ; 
                    Fuction sets up ui 
                */
                void createUI() ; 
                /**
                    \fn void createWidgets() 
                    Function allocates memory for all widgets. Nothing more
                */
                void createWidgets() ;
                /**
                    \fn void initSignals()  
                    Function connects signal and slots with each other
                */
                void initSignals() ; 

                /**
                 * \fn	void setStatusBarStatus( const QString & _status, bool isWorking )
                 *
                 * \brief	Sets the status bar status. 
                 *
                 * \author	Bartosz Taczala
                 * \date	2009-08-07
                 *
                 * \param	_status		The status. 
                 * \param	isWorking	true if is working. 
                **/

                void setStatusBarStatus( const QString & _status, bool isWorking ) ; 
                
                
                /** MEMBERS **/
                QPointer<QStatusBar> m_pStatusBar ; 
                QPointer<QLabel> m_pStatusBarWidget ; 
                QPointer<QMenuBar> m_pMenuBar ; 
                QPointer<QToolBar> m_pToolBar ; 
                
                QPointer<QMenu> m_pFileMenu ;
                QPointer<QMenu> m_pWorkspaceMenu ;  
                QPointer<QMenu> m_pWorkspaceNewFunctionMenu ; 
                QPointer<QMenu> m_pWorkspaceNewDiscreteFunctionMenu ; 
                QPointer<QMenu> m_pWorkspaceNewMixedFunctionMenu ;
                QPointer<QMenu> m_pAritmeticOperationMenu ;
                QPointer<QMenu> m_pConvolutionBasedAritmeticOperationMenu ; 
                
                
                QPointer<QMenu> m_pAboutMenu ;  
                QPointer<TabWidget> m_pTabWidget ; 

                int m_iNumberOfWorkspaces ; 
        };
    }
}
#endif // THESIS_MAINWINDOW_H
