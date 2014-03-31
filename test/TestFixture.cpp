/*
 * TestFixture.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: brian
 */

#include "test/TestFixture.h"

LapCountJunction::LapCountJunction(int numLaps, Cross::Context* ctx) :
	Cross::Junction(NULL, ctx), mNumLaps(numLaps), mCurrLap(0)
{
}

void LapCountJunction::Run(Cross::Context* ctx, Cross::Continuer* cnt)
{
	if(mCurrLap < mNumLaps)
	{
		mCurrLap++;
		Junction::Run(ctx, cnt);
	}
	else
	{
		// this will stop us from looping forever
		Connect()->ClearConnections();

		cnt->Continue(ctx, Cross::ERR_NONE);
	}
}


