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
#include "cross/Context/AllocationContext.h"

namespace Cross
{

class Serial;
class Continuer;
class Context;

// encapsulates modular flow logic
class Module : public AllocationContext
{
public:
    Module(Context* ctx, Continuer* cnt=NULL, Serial* s=NULL) : AllocationContext(ctx) {}
    virtual ~Module() {}
};

}

#endif /* FLOW_MODULE_H_ */

