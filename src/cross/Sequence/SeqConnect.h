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
    typedef std::pair<SeqNode*, Direction> SeqPair;
    typedef std::vector<SeqPair> Connection;

    Connection::iterator GetConnectionBegin() { return mConnect.begin(); }
    Connection::iterator GetConnectionEnd() { return mConnect.end(); }

    SeqPair* FindConnection(IModuleWrapper* module);
    SeqPair* FindConnection(SeqNode* node);

    void ClearConnections() { mConnect.clear(); }

    virtual bool AddConnection(SeqNode*& out, SeqNode* in, Direction d);
    virtual bool AddConnection(SeqNode*& out, IModuleWrapper* m, Direction d);
    virtual bool AddConnection(SeqNode*& out, SeqStream* s, Direction d);

protected:
    explicit SeqConnect(Context* ctx);
    virtual ~SeqConnect() {}

    Context* GetContext() const { return mContext; }

private:
    Connection mConnect;
    Context* mContext;
};

}

#endif /* SEQCONNECT_H_ */
