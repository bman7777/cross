/****************************************************************/
/// \class Cross::DirectionModuleDecorator
/// \ingroup Sequence
/// \date Feb 1, 2014
/// \brief A module that can force a direction change in a flow
///         in a specific way.  This depends heavily on
///         directional strategies that ultimately determine
///         flow.
/****************************************************************/

#ifndef UPDATEDIRSEQNODE_H_
#define UPDATEDIRSEQNODE_H_

#include "cross/Context/Continuer.h"
#include "cross/Context/IModuleWrapper.h"

namespace Cross
{
class AutoDirectionStrategy;

class DirectionModuleDecorator : public IModuleWrapper, public Continuer
{
public:
    DirectionModuleDecorator(AutoDirectionStrategy* strat, Direction newDir, IModuleWrapper* mod);
    virtual ~DirectionModuleDecorator() {}

protected:
    virtual void Run(Context* ctx, Continuer* cnt);
    virtual IModuleWrapper::Key GetKey() const { return mKey; }
    virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE);

private:
    AutoDirectionStrategy* mStrategy;
    Direction mNewDir;
    IModuleWrapper* mModule;
    IModuleWrapper::Key mKey;
    Continuer* mContinue;
};
}


#endif /* UPDATEDIRSEQNODE_H_ */
