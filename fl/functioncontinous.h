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

#ifndef FUNCTIONCONTINOUS_H
#define FUNCTIONCONTINOUS_H

#include "function2dbase.h"
#include "function3dbase.h"

namespace fl{
    namespace Function2D{
        
        class FunctionContinous : public fl::Function2D::Function2DBase, public fl::FunctionContinousBase
        {
            public:
                FunctionContinous( const std::string & _functionEquation = "" , const std::string & _functionName = "") ; 
                virtual ~FunctionContinous() {}
                
                virtual void addVariable(const std::string & varName );
                virtual double eval(double point, bool *pCorrect ) const ;
                
                virtual Function2DBase* integrate(double start, double stop);
                virtual double max();
                virtual double min();
        };
    }
	namespace Function3D{

		class FunctionContinous : public fl::Function3D::Function3DBase, public fl::FunctionContinousBase {
			public:
				FunctionContinous( const std::string & _equation = "", const std::string & functionName= "" );
				virtual ~FunctionContinous(){}

				virtual void addVariable( const std::string & varName  );
				virtual double eval ( double x, double y ); 
				virtual Function3DBase* integrate(double start, double stop);
				virtual double max();
				virtual double min();
			protected:
		};
	}
}

#endif // FUNCTIONCONTINOUS_H
