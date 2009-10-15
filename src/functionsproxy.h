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
//#include <boost/ref.hpp>

#include <QColor>

namespace fl{
    class FunctionBase;
}
namespace Thesis {

    /**
     * \class	FunctionsProxy
     *
     * \brief	Functions proxy. 
     *
     * \author	Bartosz Taczala
     * \date	2009-08-07
    **/

    class FunctionsProxy
    {
        public:
            enum Type{
                eDiscrete = 0, 
                eContinous, 
                eMixed 
            } ;
            typedef std::vector<std::pair<double,double> > CustomRangeContainer ; 

            /**
             * \fn	FunctionsProxy( const QString & _equation, const QStringList & _vars, int _dimension,
             * 		Type type, bool bCustomRange = false,
             * 		CustomRangeContainer _range = CustomRangeContainer() )
             *
             * \brief	Constructor. 
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \param	_equation		The equation. 
             * \param	_vars			The variables. 
             * \param	_dimension		The dimension. 
             * \param	type			The type. 
             * \param	bCustomRange	true to custom range. 
             * \param	_range			The range. 
            **/

            FunctionsProxy( const QString & _equation, const QStringList & _vars, int _dimension,Type type,  bool bCustomRange = false, CustomRangeContainer _range =  CustomRangeContainer() ) ; 

            /**
             * \fn	FunctionsProxy( const QString & fileName, Type type = eDiscrete)
             *
             * \brief	Constructor. 
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \param	fileName	Filename of the file. 
             * \param	type		The type. 
            **/

            FunctionsProxy( const QString & fileName, Type type = eDiscrete) ; 

            /**
             * \fn	FunctionsProxy ( const std::vector<QStringList> & functionsList )
             *
             * \brief	Constructor. 
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \param	functionsList	List of functions. 
            **/

            FunctionsProxy ( const std::vector<QStringList> & functionsList ) ; 

            /**
             * \fn	void setColor ( const QColor & color )
             *
             * \brief	Sets a color. 
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \param	color	The color. 
            **/

            void setColor ( const QColor & color ) { m_functionColor = color ; } 

            /**
             * \fn	QColor color() const
             *
             * \brief	Return current function color.
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \return	. 
            **/

            QColor color() const { return m_functionColor ; } 
            //FunctionsProxy(const FunctionsProxy & _rhs ) ; 

            /**
             * \fn	fl::FunctionBase * proxy()
             *
             * \brief	Proxies this object. 
             *
             * \author	Bartosz Taczala
             * \date	2009-08-07
             *
             * \return	null if it fails, else. 
            **/

            fl::FunctionBase * proxy() ; 
        private:
            QString m_functionEquation ; 
            int m_functionDimension ; 
            QStringList m_functionVars ; 
            bool m_bCustomRange ; 
            CustomRangeContainer m_CustomRange ; 
            Type m_Type ; 
            QString m_functionFileNamePath ; 
            std::vector<QStringList> m_FunctionsVector ;  
            
            QColor m_functionColor ; 
    };
}

#endif // THESIS_FUNCTIONSPROXY_H
