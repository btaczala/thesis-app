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

#ifndef FUNCTIONMIXED_H
#define FUNCTIONMIXED_H

#include <boost/shared_ptr.hpp>
#include <string>

#include "function2dbase.h"

namespace fl{
    namespace Function2D{
        class FunctionMixed : public fl::Function2D::Function2DBase
        {
            public:
                struct FunctionRange{
                    boost::shared_ptr< fl::Function2D::Function2DBase> m_spFunction ; 
                    double m_start ; 
                    double m_stop ; 
                };
            public:
                FunctionMixed(const std::string & _functionName );
                virtual ~FunctionMixed(){}

                virtual double eval( double point , bool *pOk ) ; 
                virtual Function2DBase * integrate( double start, double stop ) ; 

                virtual double max() ; 
                virtual double min() ; 

                void addFunction( fl::Function2D::Function2DBase * pFunction, double start, double stop);
            private:
                std::vector<FunctionRange> m_Functions ; 
        };
    }
}


#endif //FUNCTIONMIXED_H