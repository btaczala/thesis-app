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
#ifndef THESIS_FUNCTIONOPERATIONINTERFACE_H
#define THESIS_FUNCTIONOPERATIONINTERFACE_H

#include <QString>


class QWidget ; 

namespace fl{
	class FunctionBase ; 
}
namespace Thesis{
	class FunctionOperationInterface
	{
	public:
		FunctionOperationInterface();
		virtual ~FunctionOperationInterface();
		virtual bool addFunction ( const fl::FunctionBase *pFunction ) = 0 ; 
		virtual QWidget * resultPlot() = 0 ;
		virtual bool isFinished()  = 0 ; 
		virtual QString lastError() = 0 ; 
	protected:
		QString m_operationName ; 
		unsigned int m_functionsRequired ;
		QString m_lastError ; 
	};
}

#endif // THESIS_FUNCTIONOPERATIONINTERFACE_H