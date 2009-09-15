#ifndef THESIS_FUNCTIONOPERATIONINTERFACE_H
#define THESIS_FUNCTIONOPERATIONINTERFACE_H

#include <string>

namespace fl{
	class FunctionBase ; 
}
namespace Thesis{

	class FunctionOperationInterface
	{
	public:
		FunctionOperationInterface();
		virtual ~FunctionOperationInterface();
		virtual void addFunction ( const fl::FunctionBase *pFunction ) = 0 ; 
	protected:
		std::string m_operationName ; 
		unsigned int m_functionsRequired ; 
	};
}

#endif // THESIS_FUNCTIONOPERATIONINTERFACE_H