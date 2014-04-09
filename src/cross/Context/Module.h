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

class Serial;
class Continuer;
class Context;

// encapsulates modular flow logic
class Module
{
public:
    Module(Context* ctx, Continuer* cnt=NULL, Serial* s=NULL) : mContext(ctx) {}

    virtual ~Module() {}

    void* operator new (size_t size, Context* ctx);

    void operator delete (void* module);

    void operator delete (void* module, Context* ctx);

    Context* GetContext() const { return mContext; }

private:
    Context* mContext;
};

}

#endif /* FLOW_MODULE_H_ */

