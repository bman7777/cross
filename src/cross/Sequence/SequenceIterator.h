/*
 * SequenceIterator.h
 *
 *  Created on: Jan 6, 2014
 *      Author: brian
 */

#ifndef SEQUENCEITERATOR_H_
#define SEQUENCEITERATOR_H_

#include "cross/Context/Continuer.h"
#include "cross/Context/FlowDefine.h"

namespace Cross
{

class SeqNode;
class IDirectionStrategy;

class SequenceIterator : public Continuer
{
public:
	SequenceIterator(SeqNode* root, IDirectionStrategy* strat = NULL);
	virtual ~SequenceIterator();

	void Run(Context* ctx, Continuer* cnt = NULL);

protected:
	virtual void Continue(Context* ctx, ErrorCode e = ERR_NONE);

private:
	SeqNode* mCurrentProgress;
	IDirectionStrategy* mDirectionStrategy;
	bool mOwnsDirectionStrategy;
	bool mIsRunning;
	Continuer* mCompletedContinuer;
	Context* mContext;
};

}

#endif /* SEQUENCEITERATOR_H_ */
