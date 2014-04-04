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

Sequence* SequenceFactory::CreateSequence()
{
    return new Sequence(mContext);
}

SeqNode* SequenceFactory::CreateSeqNode(IModuleWrapper* m)
{
    return new SeqNode(mContext, m);
}

}

