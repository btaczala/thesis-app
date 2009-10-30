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

#include "commons.h"
#include <float.h>
using namespace Thesis ; 

const QString Strings::applicationAuthor = ("Bartosz Taczala") ;
const QString Strings::applicationEmail = ("bartosz.taczala@wi.ps.pl") ;
const QString Strings::applicationVersion = QString::number(VERSION_MAJOR) +"."+ QString::number(VERSION_MINOR) +"."+ QString::number(VERSION_PATCH); 

QDebug operator<<(QDebug dbg, const std::string& str)
{
    dbg.nospace() << str.c_str() ;
    return dbg.space() ; 
}
QDebug operator<< ( QDebug dbg, QStringList & strList )
{
    foreach( QString str, strList){
        dbg.nospace() << str ;
    }
    return dbg.space();
}

bool Thesis::Math::isInfinite( double val ){
#ifdef WIN32 
    return ( _finite(val)==0 ) ; 
#endif
#ifdef UNIX
    return std::isinf<double>(value) ; 
#endif
}

KPlotObject * Thesis::kplotobjFromFunction( fl::Function2D::Function2DBase * pFunc, double startx, double stopx )
{
	KPlotObject *obj = new KPlotObject( Qt::red, KPlotObject::Lines, 2 );
	bool bOk ; 
	double valD ; 
	for ( double d = startx ; d < stopx ; d+=0.1){
		valD = pFunc->eval(d,&bOk);
		if ( bOk)
			obj->addPoint(d,valD);
	}

	return obj ; 
}