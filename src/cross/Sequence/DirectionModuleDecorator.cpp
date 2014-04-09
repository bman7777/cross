/****************************************************************/
/// \class Cross::DirectionModuleDecorator
/// \ingroup Sequence
/// \date Feb 4, 2014
/// \brief A module that can force a direction change in a flow
///         in a specific way.  This depends heavily on
///         directional strategies that ultimately determine
///         flow.
/****************************************************************/

#include "cross/Context/Continuer.h"
#include "cross/Context/IModuleWrapper.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/DirectionModuleDecorator.h"

namespace Cross
{

/// \brief construct the decorator with all dependencies
/// \param strategy - this contains algorithm for determining
///         the next direction to proceed.
/// \param newDir - the new direction to trigger when a
///         Continue() occurs
/// \param module - the module to run (this is what we are
///         ultimately decorating)
DirectionModuleDecorator::DirectionModuleDecorator(AutoDirectionStrategy* strat, Direction newDir, IModuleWrapper* mod) :
	mStrategy(strat), mNewDir(newDir), mModule(mod), mKey(MakeKey()), mContinue(NULL)
{
}

/// \brief run the decorated module if one has been given
/// \param ctx - context for the run
/// \param cnt - continuer after the run
void DirectionModuleDecorator::Run(Context* ctx, Continuer* cnt)
{
	mContinue = cnt;
	if(mModule)
	{
		mModule->Run(ctx, this);
	}
	else
	{
		Continue(ctx, ERR_NONE);
	}
}

/// \brief continue the run process and interface with the
///         strategy so the next strategy pick is influenced
/// \param ctx - the context for the run
/// \param error - any error that occurred in the run
void DirectionModuleDecorator::Continue(Context* ctx, ErrorCode e)
{
	if(mStrategy)
	{
		mStrategy->UpdateDir(mNewDir);
	}

	if(mContinue)
	{
		mContinue->Continue(ctx, ERR_NONE);
	}
}

}
