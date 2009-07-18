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

#ifndef THESIS_FUNCTIONSPROXY_H
#define THESIS_FUNCTIONSPROXY_H

#include <QString>
#include <QStringList>
#include <vector>
#include <boost/ref.hpp>

namespace fl{
    class FunctionBase;
}
namespace Thesis {

    class FunctionsProxy
    {
        public:
            enum Type{
                eDiscrete = 0, 
                eContinous, 
                eMixed 
            } ;
            typedef std::vector<std::pair<double,double> > CustomRangeContainer ; 
            FunctionsProxy( const QString & _equation, const QStringList & _vars, int _dimension,Type type,  bool bCustomRange = false, CustomRangeContainer _range =  CustomRangeContainer() ) ; 
            FunctionsProxy(const FunctionsProxy & _rhs ) ; 
            fl::FunctionBase * proxy() ; 
        private:
            QString m_functionEquation ; 
            int m_functionDimension ; 
            QStringList m_functionVars ; 
            bool m_bCustomRange ; 
            CustomRangeContainer m_CustomRange ; 
            Type m_Type ; 
             
    };

}

#endif // THESIS_FUNCTIONSPROXY_H
