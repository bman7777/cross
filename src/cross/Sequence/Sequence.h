/*
 * Sequence.h
 *
 *  Created on: Jan 5, 2014
 *      Author: brian
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "cross/Sequence/SeqNode.h"

namespace Cross
{

class IModuleWrapper;
class SeqStream;

class Sequence : public SeqNode
{
public:
	virtual void Run(Context* ctx, Continuer* cnt);
	virtual bool operator==(IModuleWrapper* mod) const;
	void InterConnect() { mIntraConnect = false; }
	void IntraConnect() { mIntraConnect = true; }

protected:
	explicit Sequence(Context* ctx);

	virtual SeqNode* AddConnection(SeqNode* n, Direction d);
	virtual SeqNode* AddConnection(IModuleWrapper* m, Direction d);
	virtual SeqNode* AddConnection(SeqStream* s, Direction d);

private:
	SeqNode* mRoot;
	Context* mContext;
	bool mIntraConnect;

	friend class SequenceFactory;
};

}

#endif /* SEQUENCE_H_ */
