/***************************************************************************
 *   Copyright (C) 2009 by Bartek Taczała   *
 *   b@kontrasty.szczecin.pl   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "commons.h"
#include <QErrorMessage>
#include <QStringList>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    translator.load("thesis_en");
    app.installTranslator(&translator);
    Q_INIT_RESOURCE(main);
    qDebug() << Thesis::Strings::applicationVersionString() ; 
    Thesis::UI::MainWindow wnd ;
    wnd.show();
    return app.exec()  ; 
}