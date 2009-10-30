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
                static const char* scMainToolTip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog","Enter function with specified range. <br> \
                             Example: <br> \
                             For function : ss[s_]:=If[ 0 &lt; x &lt; 2,(1/2) * x, 0]<br>\
                             You should insert: <ul> \
                             <li> (1/2)*x || x || 0 &lt; x &lt; 2 </li>\
                             <li> 0 || x || -inf &lt; x &lt;= 0 </li>\
                             <li> 0 || x || 2 &lt;= x &lt; inf </li></ul> <br> \
                             <b>NOTE:</b><br> \
                             When specifing range, remember about spaces, since parser splits this expresion by space char.");
                static const char* scLineEditTooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog"," Enter function for specified range.\
                             <ul><li> (1/2)*x || x || 0 &lt; x &lt; 2 </li></ul>");
                static const char* scFunctionHeadertooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog"," Enter function equation");
                static const char* scVarHeaderTooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog"," Enter function variable");
                static const char* scRangeHeaderTooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog"," Enter range where function is defined<br> \
                             lowerBoundary &lt; ( or &lt;= ) variable ( or &lt;= ) upperBoundary<br>\
                             Examples:<br>\
                             0 &lt; x &lt; 2<br>-inf &lt; x &lt;= -1<br>-inf &lt; x &lt; inf ");
                static const char* scAddRowTooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog","Add function part for specified range");
                static const char* scDeleteRowTooltip = QT_TRANSLATE_NOOP("Thesis::UI::NewFunctionMixedDialog","Delete current function part");
            }
            namespace NewContinousFunctionDialog{
                static const char* scFunctionEditLineToolTip = QT_TRANSLATE_NOOP("Thesis::UI::NewContinousFunctionDialog","Place here a valid function equation. <br> Examples: \
                <ul> \
                <li> sin(x) </li>\
                <li> sin(cos(x)) </li>\
                <li> x*x*exp(x) </li>\
                </ul>\
                ") ; 
                static const char* scVariablesEditLineToolTip = QT_TRANSLATE_NOOP("Thesis::UI::NewContinousFunctionDialog","Place here coma separated characters which will be treated as function variables. Examples: \
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
