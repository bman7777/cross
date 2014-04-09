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

#include "cross/Context/Context.h"
#include "cross/Service/Service.h"

namespace Cross
{

class IModuleWrapper;
class Sequence;
class SeqNode;

class SequenceFactory : public Service
{
public:
    static const Service::Key KEY;

    SequenceFactory(Context* ctx) : mContext(ctx) {}
    virtual ~SequenceFactory() {}

    Sequence* CreateSequence();
    SeqNode* CreateSeqNode(IModuleWrapper* m = NULL);

    static SequenceFactory* Get(Context* ctx)
    {
        return static_cast<SequenceFactory*>(Service::Get(KEY, ctx));
    }

private:
    Context* mContext;
};

}


#endif /* SEQUENCEFACTORY_H_ */
