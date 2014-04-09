/*
 * TestFixture.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: brian
 */

#include "test/TestFixture.h"
#include "cross/Sequence/Sequence.h"

const Cross::Service::Key SpecialChar::KEY = Cross::Service::MakeKey();

/// \brief constructor for test module that simply appends a
///         character to the string in the serial
/// \param ctx - context for the module
/// \param cnt - continuer to use when done
/// \param serial - data that was passed as the module
///         was created so that specific data can be used when
///         he module is run
AppendChar::AppendChar(Cross::Context* ctx, Cross::Continuer* cnt, Cross::Serial* s) :
    Cross::Module(ctx, cnt)
{
    char c;
    std::string* str;

    if(s &&
       s->GetData<char>(CHAR, c) &&
       s->GetData<std::string>(APPENDER, str))
    {
        *str += c;

        SpecialChar* specChar = SpecialChar::Get(ctx);
        if(specChar)
        {
            *str += specChar->GetExtraChar();
        }
    }

    if(cnt)
    {
        cnt->Continue(ctx);
    }
}

/// \brief some of the tests rely on doing things a few times
///         and the lap count junction will containue to run
///         the prescribed amount of times
/// \param numLaps - how many laps to run
/// \param ctx - context to use
LapCountJunction::LapCountJunction(int numLaps, Cross::Context* ctx) :
	Cross::Junction(NULL, ctx), mNumLaps(numLaps), mCurrLap(0)
{
}

/// \brief run the start of a new lap
/// \param ctx - context to use for running
/// \param cnt - continuer to use when all laps are done
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


