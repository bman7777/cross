/****************************************************************/
/// \class Cross::Module
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief A base class for modules that allows allocations to
///         always draw from services.
/****************************************************************/

#ifndef FLOW_MODULE_H_
#define FLOW_MODULE_H_

#include <stddef.h>

namespace Cross
{

class Context;

// encapsulates modular flow logic
class Module
{
public:
    Module(Context* ctx) {}
    virtual ~Module() {}
};

}

#endif /* FLOW_MODULE_H_ */

