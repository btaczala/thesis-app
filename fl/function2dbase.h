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

#ifndef FUNCTION2DBASE_H
#define FUNCTION2DBASE_H

#include <string>
#include "functionbase.h"


namespace fl{
    namespace Function2D{
        
        class Function2DBase : public fl::FunctionBase
        {
            public:
                Function2DBase( const std::string & _functionName = "unnamed" ) ; 
                virtual ~Function2DBase() {}
                virtual double eval( double point, bool * pCorrect ) const  = 0 ; 
                virtual double integrate( double start, double stop, double dStep ) ; 
                
                virtual double max() const = 0 ; 
                virtual double min() const = 0 ; 
                
                virtual double xStartWhereIntegratingMakesSense() const = 0 ;
                virtual double xStopWhereIntegratingMakesSense() const =  0 ; 
        };
    }
}

#endif // FUNCTION2DBASE_H
