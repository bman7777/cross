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

DirectionModuleDecorator::DirectionModuleDecorator(AutoDirectionStrategy* strat, Direction newDir, IModuleWrapper* mod) :
	mStrategy(strat), mNewDir(newDir), mModule(mod), mContinue(NULL), mKey(MakeFlowKey()), mContext(NULL)
{
}

void DirectionModuleDecorator::Run(Context* ctx, Continuer* cnt)
{
	mContext = ctx;
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
