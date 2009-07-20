/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.*/


#ifndef FUNCTION__EXCEPTION_H
#define FUNCTION__EXCEPTION_H


#include <exception>
#include <string>
#include <sstream>


namespace fl {
    
    class FunctionException : public std::exception {
        public :
            enum What{
                eGeneral = 0,
                eMuParser,
            };
            FunctionException(const std::string & exception, What = eGeneral):
            m_ExceptionDesc(exception),
	    m_Description("")
            {}
            const char * what() const throw() { 
                std::stringstream stream ; 
                switch ( m_What ) {
                    case eGeneral:
                        stream << " General exception occured: "; 
                        break ; 
                    case eMuParser:
                        stream << " muParser exception: "; 
                        break ; 	
                }
                stream << m_ExceptionDesc.c_str() << std::endl ; 
                m_Description = stream.str() ; 
                return m_Description.c_str();
            }
            virtual ~FunctionException() throw() {}
        private:
            std::string m_ExceptionDesc ; 
            What m_What ; 
            mutable std::string m_Description ; 
    };
}
#endif 