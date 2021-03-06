/****************************************************************/
/// \class Cross::RunContext
/// \ingroup Sequence
/// \date Feb 14, 2014
/// \brief A surrogate for running a node with a strategy.  This
///         would be duplicated in several places if not for this
///         class which manages the running context and
///         continuer.
/****************************************************************/

#ifndef RUNCONTEXT_H_
#define RUNCONTEXT_H_

#include "cross/Context/Context.h"
#include "cross/Context/Continuer.h"
#include "cross/Sequence/SequenceIterator.h"

namespace Cross
{

class IDirectionStrategy;

class RunContext : public Context, public Continuer
{
public:
    RunContext(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy = NULL);
    virtual ~RunContext() {}

    static void BeginRun(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy = NULL);
    static void FinishRun(RunContext* ctx);

protected:

    virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE);

private:
    Continuer* mContinue;
    SequenceIterator mIter;
    Context* mContext;
};

}

#endif /* RUNCONTEXT_H_ */
