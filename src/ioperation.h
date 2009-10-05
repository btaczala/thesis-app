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

#ifndef IOPERATION_H
#define IOPERATION_H

#include "fl/functionbase.h"
#include <vector>
#include <boost/shared_ptr.hpp>

class IOperation
{
    public:
        typedef boost::shared_ptr<fl::FunctionBase> FunctionBaseShPtr ; 
        virtual ~IOperation() {}
        virtual void addFunction( fl::FunctionBase* pPtr ) ; 
        
        virtual fl::FunctionBase * calculate() = 0 ; 
    protected:
        std::vector<FunctionBaseShPtr> m_functions ; 
};

#endif // IOPERATION_H
