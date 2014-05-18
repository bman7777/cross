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
#include "cross/Service/Allocation.h"

namespace Cross
{

class Context;
class Continuer;

template <class M, class P=void>
class ModuleWrapper : public IModuleWrapper
{
public:
    ModuleWrapper(P* p=NULL) : mParam(p) {}
    virtual ~ModuleWrapper();

protected:
    void Run(Context* ctx, Continuer* cnt=NULL);

private:
    P* mParam;

    typedef std::pair<M*, Context*> ModulePair;
    typedef boost::container::list<ModulePair> ModuleTrackList;
    ModuleTrackList mModuleList;
};

/// \brief destruct the module wrapper and cleanup all modules
///         that have been allocated from this
template <class M, class P>
ModuleWrapper<M, P>::~ModuleWrapper()
{
    for(typename ModuleTrackList::iterator i = mModuleList.begin(); i != mModuleList.end(); i++)
    {
        Allocation::Get(i->second)->Delete(i->first);
    }
}

/// \brief run a module by allocating an internal module
///         and also track its memory for later cleanup
/// \param ctx - context to run/allocate with
/// \param cnt - continuer to use when module is done
template <class M, class P>
void ModuleWrapper<M, P>::Run(Context* ctx, Continuer* cnt)
{
    ModulePair p;
    p.first = Allocation::Get(ctx)->New<M>(ctx, cnt, mParam);
    p.second = ctx;

    mModuleList.push_back(p);
}

}

#endif // MODULE_WRAPPER_H_

