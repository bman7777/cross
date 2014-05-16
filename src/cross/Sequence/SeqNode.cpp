/****************************************************************/
/// \class Cross::SeqNode
/// \ingroup Sequence
/// \date Jan 31, 2014
/// \brief Nodes makes up a network that is known as a sequence.
///         When nodes contain modules, they are wrappers for
///         running the module process.
/****************************************************************/

#ifndef SEQNODE_CPP_
#define SEQNODE_CPP_

#include "cross/Context/Continuer.h"
#include "cross/Context/IModuleWrapper.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{

/// \brief construct a SeqNode using a module to initialize
/// \param ctx - a context to use for all service needs
/// \param module - the node is a wrapper for this module
///         located in the flow
SeqNode::SeqNode(Context* ctx, IModuleWrapper* module) :
    SeqConnect(ctx), mModule(module)
{
}

/// \brief construct a SeqNode using another SeqNode to
///         initialize
/// \param ctx - a context to use for all service needs
/// \param node - the node is a wrapper for a different
///         node located in the flow
SeqNode::SeqNode(Context* ctx, SeqNode* node) :
    SeqConnect(ctx), mModule(node->GetModule())
{
}

/// \brief run this node from some iterator/runner
///         which should be running its internal
///         module or just continuing if none exists
/// \param ctx - the context that is being run with
/// \param cnt - the continuer to use when running is
///         complete
void SeqNode::Run(Context* ctx, Continuer* cnt)
{
    if(mModule)
    {
        mModule->Run(ctx, cnt);
    }
    else
    {
        cnt->Continue(ctx, ERR_NONE);
    }
}

/// \brief if someone requests the equality state
///         with a module, use our internal module
///         to check validity
/// \param mod - module to check against
/// \return T: if equal; F: if not equal
bool SeqNode::operator==(IModuleWrapper* mod) const
{
    return mod == mModule;
}

}

#endif /* SEQNODE_CPP_ */
