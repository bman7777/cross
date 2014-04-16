/****************************************************************/
/// \class Cross::IModuleWrapper
/// \ingroup Context
/// \date Oct 3, 2013
/// \brief A wrapper for runtime modules that can perform some
///         task or service according to their function.
///         context can be used for dependencies.
/****************************************************************/

#ifndef FLOW_IMODULEWRAPPER_H_
#define FLOW_IMODULEWRAPPER_H_

#include "cross/Context/DataContext.h"

namespace Cross
{

class Context;
class Continuer;

class IModuleWrapper : public DataContext
{
public:
    virtual ~IModuleWrapper() {}
    virtual void Run(Context* ctx, Continuer* cnt) = 0;
};

}

#endif // FLOW_IMODULEWRAPPER_H_
