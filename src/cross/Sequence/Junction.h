/****************************************************************/
/// \class Cross::Junction
/// \ingroup Sequence
/// \date Feb 8, 2014
/// \brief A junction is a point in a sequence that contains
///         several routes to new sequences.  The chosen route
///         will rely on direction strategies.  A junction is
///         definable by a user, and can be streamed from like
///         a standard sequence stream.
/****************************************************************/

#ifndef JUNCTION_H_
#define JUNCTION_H_

#include <boost/container/list.hpp>
#include "cross/Sequence/SeqNode.h"

namespace Cross
{
class IDirectionStrategy;
class Sequence;

class Junction : public SeqNode
{
public:
    Junction(IDirectionStrategy* strat = NULL, Context* ctx = NULL);
    virtual ~Junction();

    virtual SeqStream& operator<<(IModuleWrapper& module);
    virtual SeqStream& operator>>(IModuleWrapper& module);

    virtual SeqStream& operator<<(SeqNode& node);
    virtual SeqStream& operator>>(SeqNode& node);

    virtual SeqStream& operator<<(Sequence& seq);
    virtual SeqStream& operator>>(Sequence& seq);

    virtual SeqStream& operator<<(SeqStream& stream);
    virtual SeqStream& operator>>(SeqStream& stream);

protected:
    virtual void Run(Context* ctx, Continuer* cnt);

private:
    bool mOwnsDirectionStrategy;
    IDirectionStrategy* mStrategy;
    SeqNode* mRoot;

    typedef boost::container::list<SeqStream> StreamTrackList;
    StreamTrackList mStreamTracker;
};

}

#endif /* JUNCTION_H_ */
