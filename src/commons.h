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
#ifndef commons_h__
#define commons_h__



#include <QString>
#include <qobject.h>
#include <QDebug>
#include <QStringList>



#define VERSION_MAJOR 0 
#define VERSION_MINOR 1 
#define VERSION_PATCH 0

#define LOG(a) qDebug() << Q_FUNC_INFO << "---->" << a 
#define cLOG() qDebug() << Q_FUNC_INFO ;

namespace Thesis{
    namespace Math{
        bool isInfinite( double val );
    }
}

namespace Thesis{
    class Strings {
        public:
            static const QString applicationName /*= QObject::tr("Thesis application") */; 
            static const QString applicationAuthor /*= QObject::tr("Bartosz Taczała") */; 
            static const QString applicationEmail /*= QObject::tr("bartosz.taczala@wi.ps.pl")*/ ;
            static const QString applicationVersion /*= QObject::tr( QString::number(VERSION_MAJOR) + QString::number(VERSION_MINOR) + QString::number(VERSION_PATCH) ) */; 
        public:
            static const QString applicationVersionString() { return applicationName + " : " + applicationVersion ; } 
    };
}
QDebug operator<< ( QDebug dbg, const std::string & str ) ;
QDebug operator<< ( QDebug dbg, QStringList & strList ) ;

#endif // commons_h__
