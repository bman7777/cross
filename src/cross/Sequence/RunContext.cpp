/****************************************************************/
/// \class Cross::RunContext
/// \ingroup Sequence
/// \date Feb 14, 2014
/// \brief A surrogate for running a node with a strategy.  This
///         would be duplicated in several places if not for this
///         class which manages the running context and
///         continuer.
/****************************************************************/

#include "cross/Sequence/RunContext.h"

namespace Cross
{

/// \brief constructor for the run context that can be used as a
///         helper to run an iterator while internally handling
///         the continuer.
/// \param context - the context used to run
/// \param continuer - when run is done, call this
/// \param node - which node to start running with
/// \param strategy - strategy that can inject decision-making
RunContext::RunContext(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy) :
    Context(ctx),
    mContinue(cnt),
    mIter(node, strategy),
    mContext(ctx)
{
}

/// \brief entry point for the run context is a static function
///         that will construct a runcontext.
/// \param context - the context used to run
/// \param continuer - when run is done, call this
/// \param node - which node to start running with
/// \param strategy - strategy that can inject decision-making
void RunContext::BeginRun(Context* ctx, Continuer* cnt, SeqNode* node, IDirectionStrategy* strategy)
{
    if(node)
    {
        RunContext* runCtx = Allocation::Get(ctx)->New<RunContext>(ctx, cnt, node, strategy);
        runCtx->mIter.Run(ctx, runCtx);
    }
    else
    {
        cnt->Continue(ctx, ERR_NONE);
    }
}

/// \brief when the run is complete, use this as a callback to
///         clean up the run and proceed
/// \param context - the context that was run with
/// \param error - error, if any, occurred
void RunContext::Continue(Context* ctx, ErrorCode e)
{
    mContinue->Continue(ctx, e);

    RunContext::FinishRun(this);
}

/// \brief static exit point for the run that will clean up
///         the run allocations and return the state of
///         the system to pre-run conditions.
/// \param context - the runcontext that was created for the
///         run.
void RunContext::FinishRun(RunContext* ctx)
{
    Allocation::Get(ctx->mContext)->Delete(ctx);
}

}
