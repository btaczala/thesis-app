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

#ifndef FUNCTIONBASE_H
#define FUNCTIONBASE_H

#include <string>

#include <muParser.h>

namespace fl{
    class FunctionBase
    {
        public:
            enum Type{
                eDiscrete = 0, 
                eContinous, 
                eMixed 
            } ;
            FunctionBase( const std::string & _functionName ) : m_FunctionName(_functionName) {}
            virtual ~FunctionBase() {}
            const std::string & name() const { return m_FunctionName ; } 
            void setName ( const std::string & _name ) { m_FunctionName = _name ; } 
            
            virtual double max() const = 0  ; 
            virtual double min() const = 0 ; 
            virtual int dimensions() { return m_iDimension ; } 
            virtual Type type() const { return m_Type ; }
            //virtual void serialize ( const std::string & _pathToFile ) = 0 ; 
        protected:
            std::string m_FunctionName ; 
            int m_iIdentifier ; 
            int m_iDimension ; 
            Type m_Type ; 
    };
    class FunctionContinousBase
    {
        public:
			FunctionContinousBase( const std::string & _equation ) : m_pParser( new mu::Parser() ) ,m_bMinMaxEval(false)
			{ 
				m_functionEquation = _equation ; 
				if ( !m_functionEquation.empty() )
					m_pParser->SetExpr(m_functionEquation);
                
			}
            virtual ~FunctionContinousBase() {}
            const std::string & equation() const { return m_functionEquation;}
            void setEquation( const std::string & _equation ) 
            { 
                m_functionEquation = _equation ; 
                m_pParser->SetExpr(_equation);
            }
			virtual void addVariable ( const std::string & varName  )
			{
				m_VariableMap[varName] = 0 ; 
				m_pParser->DefineVar(varName,&(m_VariableMap[varName]) );
			}
            std::vector<char> variables() const ; 
            
            double step() const { return m_dStep ; }
            void setStep( double _step ) { m_dStep = _step ; }
        protected:
            std::string m_functionEquation ; 
            std::auto_ptr<mu::Parser> m_pParser ; 
            double m_dStep ; 
            mutable std::map<std::string,double> m_VariableMap ; 
            
            mutable double m_iMin ;
            mutable double m_iMax ;
            mutable bool m_bMinMaxEval ; 
    };
}

#endif // FUNCTIONBASE_H
