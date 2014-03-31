/*
 * IDirectionStrategy.h
 *
 *  Created on: Feb 1, 2014
 *      Author: brian
 */

#ifndef IDIRECTIONSTRATEGY_H_
#define IDIRECTIONSTRATEGY_H_

namespace Cross
{

class SeqConnect;
class SeqNode;

class IDirectionStrategy
{
public:
	virtual ~IDirectionStrategy() {}

	virtual SeqNode* GetNextNode(SeqConnect* current, ErrorCode e) = 0;
};

}


#endif /* IDIRECTIONSTRATEGY_H_ */
