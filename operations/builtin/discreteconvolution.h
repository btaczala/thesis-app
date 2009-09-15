#ifndef THESIS_DISCRETECONVULTION_H
#define THESIS_DISCRETECONVULTION_H
#include "functionoperationinterface.h"
#include <QObject>

namespace Thesis{
	class DiscreteConvolution : public Thesis::FunctionOperationInterface
	{
		Q_OBJECT
		Q_INTERFACES(Thesis::FunctionOperationInterface)
	public:
		DiscreteConvolution();
		virtual ~DiscreteConvolution();
	};
}
#endif // THESIS_DISCRETECONVULTION_H