/****************************************************************/
/// \class Cross::GenesisContext
/// \ingroup Sequence
/// \date Mar 28, 2014
/// \brief The context used for generating the construction of
///         sequences.  This is then forked and split as
///         sequences are run throughout an iterator.
/****************************************************************/

#ifndef GENESISCONTEXT_H_
#define GENESISCONTEXT_H_

#include "cross/Context/Context.h"
#include "cross/Service/Allocation.h"

namespace Cross
{

class GenesisContext : public Context
{
public:
    GenesisContext();
    virtual ~GenesisContext() {}

    static Context* Get();

private:
    Allocation mAllocService;
};
}

#endif /* GENESISCONTEXT_H_ */
