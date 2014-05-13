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

template <class M, class P=void>
class ModuleWrapper : public IModuleWrapper
{
public:
    ModuleWrapper(P* p=NULL) :
        mModule(NULL),
        mParam(p),
        mContext(NULL)
    {
    }

    virtual ~ModuleWrapper()
    {
        if(mModule)
        {
            Allocation::Get(mContext)->Delete(mModule);
            mModule = NULL;
        }
    }

protected:
    void Run(Context* ctx, Continuer* cnt=NULL)
    {
        // TODO: should this be allowed?  should destruction be async?
        if(mModule)
        {
            Allocation::Get(mContext)->Delete(mModule);
        }

        mContext = ctx;
        mModule = Allocation::Get(mContext)->New<M>(mContext, cnt, mParam);
    }

private:
    M* mModule;
    P* mParam;
    Context* mContext;
};

}

#endif // MODULE_WRAPPER_H_

