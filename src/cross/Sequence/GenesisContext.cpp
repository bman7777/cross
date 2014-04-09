/****************************************************************/
/// \class Cross::GenesisContext
/// \ingroup Sequence
/// \date Mar 28, 2014
/// \brief The context used for generating the construction of
///         sequences.  This is then forked and split as
///         sequences are run throughout an iterator.
/****************************************************************/

#include "cross/Service/Allocation.h"
#include "cross/Service/SequenceFactory.h"
#include "cross/Context/Context.h"
#include "cross/Sequence/GenesisContext.h"

namespace Cross
{

static GenesisContext sGenesis;
static Context sContext;
static Allocation sAlloc(&sContext);
static SequenceFactory sFactory(&sContext);
static bool sIsRegistered = false;

/// \brief get the genesis context.  This should only be used
///         in creation of sequences and nodes.  This will
///         be propagated into other nodes eventually.  If it
///         doesn't exist yet, it will be lazy instantiated.
/// \return ptr to the context
Context* GenesisContext::Get()
{
    if(!sIsRegistered)
    {
        sIsRegistered = true;
        sContext.EnsureService(Allocation::KEY, &sAlloc);
        sContext.EnsureService(SequenceFactory::KEY, &sFactory);
    }

    return &sContext;
}

}

