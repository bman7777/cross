/****************************************************************/
/// \class Cross::SeqConnect
/// \ingroup Sequence
/// \date Mar 23, 2014
/// \brief This helper owns connection between nodes that allow
///         a network of nodes to be created as a sequence.
///         Connections ultimately contain modules, junctions,
///         and other sequences.
/****************************************************************/

#ifndef SEQCONNECT_H_
#define SEQCONNECT_H_

#include <utility>
#include <vector>
#include "cross/Context/FlowDefine.h"

namespace Cross
{

class Context;
class IModuleWrapper;
class SeqNode;
class SeqStream;

class SeqConnect
{
public:
    explicit SeqConnect(Context* ctx) : mContext(ctx) {}
    virtual ~SeqConnect() {}

    typedef std::pair<SeqNode*, Direction> SeqPair;
    typedef std::vector<SeqPair> Connection;

    Connection::iterator GetConnectionBegin() { return mConnect.begin(); }
    Connection::iterator GetConnectionEnd() { return mConnect.end(); }

    SeqPair* FindConnection(IModuleWrapper* module);
    SeqPair* FindConnection(SeqNode* node);

    void ClearConnections() { mConnect.clear(); }

    virtual SeqNode* AddConnection(SeqNode* n, Direction d);
    virtual SeqNode* AddConnection(IModuleWrapper* m, Direction d);
    virtual SeqNode* AddConnection(SeqStream* s, Direction d);

private:
    Connection mConnect;
    Context* mContext;
};

}

#endif /* SEQCONNECT_H_ */
