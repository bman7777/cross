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

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include "cross/Context/FlowDefine.h"

namespace Cross
{

class Context;
class Continuer;

class IModuleWrapper
{
public:
    typedef boost::uuids::uuid Key;

    virtual ~IModuleWrapper() {}
    virtual Key GetKey() const = 0;
    virtual void Run(Context* ctx, Continuer* cnt) = 0;

protected:
    static Key MakeKey()
    {
        return boost::uuids::random_generator()();
    }
};

}

#endif // FLOW_IMODULEWRAPPER_H_
