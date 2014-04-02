/*
 * SeqNode.h
 *
 *  Created on: Jan 31, 2014
 *      Author: brian
 */

#ifndef SEQNODE_H_
#define SEQNODE_H_

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
