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

#include "function2dbase.h"

using namespace fl::Function2D; 

Function2DBase::Function2DBase(const std::string& _functionName): FunctionBase(_functionName)
{
    m_iDimension = 2;
}

double fl::Function2D::Function2DBase::integrate ( double start, double stop, double dStep ) const
{
    double a ; 
    double b ; 
    double fa ; 
    double fb ;
    bool bOk ; 
    const double t = 2.0f ; 
    double result = 0; 
    for ( double iterator = start ; iterator <= stop ; iterator += dStep ) {
        a = iterator ; 
        b = iterator + dStep ; 
        fa = eval(a,&bOk);
        if ( bOk ) 
        {
            fb = eval ( b, &bOk );
            if ( bOk ){
                result += (b-a) * ((fa+fb)/t);
            }
        }
    }
    return result ; 
}
