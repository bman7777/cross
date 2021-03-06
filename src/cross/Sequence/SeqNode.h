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

class SeqNode : public SeqConnect
{
public:
    explicit SeqNode(Context* ctx, IModuleWrapper* module = NULL);
    SeqNode(Context* ctx, SeqNode* node);
    virtual ~SeqNode() {}

    virtual void Run(Context* ctx, Continuer* cnt);
    virtual bool operator==(IModuleWrapper* mod) const;

protected:
    IModuleWrapper* GetModule() const { return mModule; }

private:
    // do not support SeqNode copying
    SeqNode(const SeqNode& other);
    SeqNode& operator=(const SeqNode& other);

    IModuleWrapper* mModule;
};

}

#endif /* SEQNODE_H_ */
