/****************************************************************/
/// \class Cross::SeqStream
/// \ingroup Sequence
/// \date Feb 24, 2014
/// \brief The construction of a sequence can be made using
///         modules, junction, and other sequences.  This is the
///         user's entry point for construction with a very
///         readable interface for forward/backward directions
///         that is customarily used in the world of streams.
/****************************************************************/

#ifndef SEQSTREAM_H_
#define SEQSTREAM_H_

#include <stack>
#include "cross/Context/Context.h"
#include "cross/Sequence/Junction.h"

namespace Cross
{

class IModuleWrapper;
class SeqNode;
class Sequence;

class SeqStream
{
public:
    explicit SeqStream(Context* ctx = NULL);
    explicit SeqStream(SeqNode* node, Context* ctx = NULL);
    explicit SeqStream(IModuleWrapper* module, Context* ctx = NULL);
    SeqStream(const SeqStream& other);
    SeqStream& operator=(const SeqStream& other);

    virtual ~SeqStream();

    SeqNode* GetCurrent() const { return mCurrentNode; }
    SeqNode* GetHead() const { return mHead; }

    typedef int Command;
    static const Command Push = 0x9054;
    static const Command Pop = 0x909;
    SeqStream& operator>>(Command type);
    SeqStream& operator<<(Command type);

    SeqStream& operator<<(IModuleWrapper& module);
    SeqStream& operator>>(IModuleWrapper& module);

    SeqStream& operator<<(Junction& junction);
    SeqStream& operator>>(Junction& junction);

    SeqStream& operator<<(SeqStream& stream);
    SeqStream& operator>>(SeqStream& stream);

protected:
    SeqStream& operator<<(SeqNode& node);
    SeqStream& operator>>(SeqNode& node);

private:
    SeqNode* mCurrentNode;
    SeqNode* mHead;
    Context* mContext;

    typedef std::list<SeqNode*> NodeTrackList;
    NodeTrackList mNodeTracker;

    typedef std::stack<Sequence*> SeqStack;
    SeqStack mStack;
};

}

#endif /* SEQSTREAM_H_ */
