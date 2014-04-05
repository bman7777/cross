/****************************************************************/
/// \class Cross::GenesisContext
/// \ingroup Sequence
/// \date Mar 28, 2014
/// \brief The context used for generating the construction of
///         sequences.  This is then forked and split as
///         sequences are run throughout an iterator.
/****************************************************************/

#include "cross/Service/SequenceFactory.h"
#include "cross/Context/Context.h"
#include "cross/Sequence/GenesisContext.h"

namespace Cross
{

static GenesisContext sGenesis;
static Context sContext;
static SequenceFactory sFactory(&sContext);
static bool sIsRegistered = false;

Context* GenesisContext::Get()
{
    if(!sIsRegistered)
    {
        sIsRegistered = true;
        sContext.EnsureService(SequenceFactory::KEY, &sFactory);
    }

    return &sContext;
}

}

