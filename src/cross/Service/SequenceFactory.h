/****************************************************************/
/// \class Cross::SequenceFactory
/// \ingroup Service
/// \date Mar 25, 2013
/// \brief A service that provides creation for sequences and
///         nodes while building up a sequence stream.  This
///         class is specifically friended to be able to
///         perform these functions.
/****************************************************************/

#ifndef SEQUENCEFACTORY_H_
#define SEQUENCEFACTORY_H_

#include "cross/Service/Service.h"

namespace Cross
{

class Allocation;
class IModuleWrapper;
class Sequence;
class SeqNode;

class SequenceFactory : public Service
{
public:
    explicit SequenceFactory(Context* ctx);
    virtual ~SequenceFactory() {}

    Sequence* CreateSequence();
    SeqNode* CreateSeqNode(IModuleWrapper* m = NULL);

    void Destroy(SeqNode* s);

    static SequenceFactory* Get(Context* ctx);

private:
    Allocation* mAllocator;
    Context* mContext;
};

}


#endif /* SEQUENCEFACTORY_H_ */
