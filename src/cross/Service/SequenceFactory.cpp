/****************************************************************/
/// \class Cross::SequenceFactory
/// \ingroup Service
/// \date Mar 25, 2013
/// \brief A service that provides creation for sequences and
///         nodes while building up a sequence stream.  This
///         class is specifically friended to be able to
///         perform these functions.
/****************************************************************/

#include "cross/Service/SequenceFactory.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{
const Service::Key SequenceFactory::KEY = Service::MakeKey();

/// \brief create a sequence using friendship to constructor
///         and passing along our local context (likely
///         genesis context.)
/// \return ptr to new sequence
Sequence* SequenceFactory::CreateSequence()
{
    return new Sequence(mContext);
}

/// \brief create a sequence node using friendship to
///         constructor and passing along our local context
///         (likely genesis context.)
/// \return ptr to new sequence node
SeqNode* SequenceFactory::CreateSeqNode(IModuleWrapper* m)
{
    return new SeqNode(mContext, m);
}

}

