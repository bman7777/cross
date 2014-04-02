/*
 * Junction.h
 *
 *  Created on: Feb 8, 2014
 *      Author: brian
 */

#ifndef JUNCTION_H_
#define JUNCTION_H_

#include "cross/Sequence/GenesisContext.h"
#include "cross/Sequence/SeqNode.h"

namespace Cross
{
class IDirectionStrategy;
class Sequence;

class Junction : public SeqNode
{
public:
	Junction(IDirectionStrategy* strat = NULL, Context* ctx = GenesisContext::Get());
	virtual ~Junction();

	virtual SeqStream operator<<(IModuleWrapper& module);
	virtual SeqStream operator>>(IModuleWrapper& module);

	virtual SeqStream operator<<(SeqNode& node);
	virtual SeqStream operator>>(SeqNode& node);

	virtual SeqStream operator<<(Sequence& seq);
	virtual SeqStream operator>>(Sequence& seq);

	virtual SeqStream operator<<(SeqStream& stream);
	virtual SeqStream operator>>(SeqStream& stream);

protected:
	virtual void Run(Context* ctx, Continuer* cnt);

private:
	IDirectionStrategy* mStrategy;
	bool mOwnsDirectionStrategy;
	SeqNode* mRoot;
	Context* mContext;
};

}

#endif /* JUNCTION_H_ */