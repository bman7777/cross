/****************************************************************/
/// \class Cross::SequenceFactory
/// \ingroup Service
/// \date Mar 25, 2013
/// \brief A service that provides creation for sequences and
///         nodes while building up a sequence stream.  This
///         class is specifically friended to be able to
///         perform these functions.
/****************************************************************/

#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqNode.h"
#include "cross/Service/Allocation.h"
#include "cross/Service/SequenceFactory.h"

namespace Cross
{

/// \brief constructor for sequence factory to create
///         sequences and nodes
/// \param ctx - context for the construction
SequenceFactory::SequenceFactory(Context* ctx):
    mAllocator(NULL), mContext(ctx)
{
}

/// \brief create a sequence using friendship to constructor
///         and passing along our local context (likely
///         genesis context.)
/// \return ptr to new sequence
Sequence* SequenceFactory::CreateSequence()
{
    return new(mContext) Sequence(mContext);
}

/// \brief create a sequence node using friendship to
///         constructor and passing along our local context
///         (likely genesis context.)
/// \return ptr to new sequence node
SeqNode* SequenceFactory::CreateSeqNode(IModuleWrapper* m)
{
    return new(mContext) SeqNode(mContext, m);
}

/// \brief destroy a particular node that was created by
///         this factory
void SequenceFactory::Destroy(SeqNode* s)
{
    delete s;
}

/// \brief helper for getting the sequence factory context
///         that will prevent/hide the need for static
///         casts.
/// \param context - which context to use for getting
///         the service
SequenceFactory* SequenceFactory::Get(Context* ctx)
{
    return static_cast<SequenceFactory*>(Service::Get(typeid(SequenceFactory), ctx));
}

}

