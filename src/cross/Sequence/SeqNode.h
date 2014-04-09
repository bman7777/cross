/****************************************************************/
/// \class Cross::SeqNode
/// \ingroup Sequence
/// \date Jan 31, 2014
/// \brief Nodes makes up a network that is known as a sequence.
///         When nodes contain modules, they are wrappers for
///         running the module process.
/****************************************************************/

#ifndef SEQNODE_H_
#define SEQNODE_H_

#include <stddef.h>
#include "cross/Sequence/SeqConnect.h"

namespace Cross
{

class Context;
class Continuer;
class IModuleWrapper;
class SequenceFactory;

class SeqNode : protected SeqConnect
{
public:
    virtual void Run(Context* ctx, Continuer* cnt);
    virtual bool operator==(IModuleWrapper* mod) const;
    SeqConnect* Connect() { return this; }

protected:
    explicit SeqNode(Context* ctx, IModuleWrapper* module = NULL);
    explicit SeqNode(Context* ctx, SeqNode* node);
    virtual ~SeqNode() {}

    IModuleWrapper* GetModule() const { return mModule; }

private:
    IModuleWrapper* mModule;

    friend class SequenceFactory;
};

}

#endif /* SEQNODE_H_ */
