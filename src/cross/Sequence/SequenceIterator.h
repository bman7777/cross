/****************************************************************/
/// \class Cross::SequenceIterator
/// \ingroup Sequence
/// \date Jan 6, 2014
/// \brief Iterate through sequence nodes and run each one in
///         turn.  When the end of the node sequence has been
///         reached call the continuer.
/****************************************************************/

#ifndef SEQUENCEITERATOR_H_
#define SEQUENCEITERATOR_H_

#include <boost/container/list.hpp>
#include "cross/Context/Continuer.h"
#include "cross/Context/FlowDefine.h"

namespace Cross
{

class SeqNode;
class IDirectionStrategy;

class SequenceIterator : public Continuer
{
public:
    SequenceIterator(SeqNode* root, IDirectionStrategy* strat = NULL);
    virtual ~SequenceIterator();

    void Run(Context* ctx, Continuer* cnt = NULL);

protected:
    virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE);

private:
    SeqNode* mCurrentProgress;
    IDirectionStrategy* mDirectionStrategy;
    bool mOwnsDirectionStrategy;
    bool mIsRunning;
    Continuer* mCompletedContinuer;
    Context* mContext;

    typedef boost::container::list<Context> ContextTrackList;
    ContextTrackList mContextTracker;
};

}

#endif /* SEQUENCEITERATOR_H_ */
