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

#ifndef THESIS_TOOLTIPS_H
#define THESIS_TOOLTIPS_H

#include <QString>
#include <QObject>
namespace Thesis
{
    namespace ToolTips{
        namespace UI {
            namespace NewMixedDialog{
                static const QString scMainToolTip = QObject::tr(
                            "Insert here functions with selected range. <br> \
                             Example: <br> \
                             (1/2) * x 0 x 2 <br> \
                             0 -inf x 0 <br> \
                             0 2 x '<'inf <br>\
                             ") ; 
            }
            namespace NewContinousFunctionDialog{
                static const QString scFunctionEditLineToolTip = QObject::tr("Place here a valid function equation. <br> Examples: \
                <ul> \
                <li> sin(x) </li>\
                <li> sin(cos(x)) </li>\
                <li> x*x*exp(x) </li>\
                </ul>\
                ") ; 
                static const QString scVariablesEditLineToolTip = QObject::tr("Place here coma separated characters which will be treated as function variables. Examples: \
                <ul> \
                <li> x </li>\
                <li> x,y </li>\
                </ul>\
                ") ;
                
            }
        }
    };

}

#endif // THESIS_TOOLTIPS_H
