/****************************************************************/
/// \class Cross::GenesisContext
/// \ingroup Sequence
/// \date Mar 28, 2014
/// \brief The context used for generating the construction of
///         sequences.  This is then forked and split as
///         sequences are run throughout an iterator.
/****************************************************************/

#include "cross/Sequence/GenesisContext.h"

namespace Cross
{

/// \brief constructor for genesis context.  The parent context
///         *is* also the genesis context since there is no
///         higher context.  This also provides the allocation
///         and sequence factory services that are common to
///         most use-cases for Cross.
GenesisContext::GenesisContext() : Context(this), mAllocService(this), mSeqFactoryService(this)
{
    RegisterService(Allocation::KEY, &mAllocService);
    RegisterService(SequenceFactory::KEY, &mSeqFactoryService);
}

/// \brief get the genesis context.  This should only be used
///         in creation of sequences and nodes.  This will
///         be propagated into other nodes eventually.  If it
///         doesn't exist yet, it will be lazy instantiated.
/// \return ptr to the context
Context* GenesisContext::Get()
{
    static GenesisContext sGenesis;
    return &sGenesis;
}

}

