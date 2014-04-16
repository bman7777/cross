/****************************************************************/
/// \class Cross::ModuleWrapper
/// \ingroup Context
/// \date Oct 4, 2013
/// \brief A functional wrapper for runtime modules that can
///         perform some task or service according to their
///         function.  ModuleWrappers also contain a UUID that
///         can uniquely identify them as a module.
/****************************************************************/

#ifndef MODULE_WRAPPER_H_
#define MODULE_WRAPPER_H_

#include <cassert>
#include <stddef.h>
#include "cross/Context/IModuleWrapper.h"

namespace Cross
{

class Context;
class Continuer;
class Serial;

template <class T>
class ModuleWrapper : public IModuleWrapper
{
public:
    ModuleWrapper(Serial* s=NULL) :
        mFlow(NULL),
        mSerial(s)
    {}

    virtual ~ModuleWrapper()
    {
        if(mFlow)
        {
            delete mFlow;
            mFlow = NULL;
        }
    }

protected:
    void Run(Context* ctx, Continuer* cnt=NULL)
    {
        // make sure we never run a module twice!
        assert(!mFlow);

        mFlow = new(ctx) T(ctx, cnt, mSerial);
    }

private:
    T* mFlow;
    Serial* mSerial;
};

}

#endif // MODULE_WRAPPER_H_

