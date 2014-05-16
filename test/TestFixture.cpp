/*
 * TestFixture.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: brian
 */

#include "test/TestFixture.h"
#include "cross/Sequence/Sequence.h"
#include "cross/Service/Allocation.h"

/// \brief getter for the specialchar service that will
///         prevent the need for static casting from service
///         base class
/// \param context - context to get service from
SpecialChar* SpecialChar::Get(Cross::Context* ctx)
{
    return static_cast<SpecialChar*>(Cross::Service::Get(typeid(SpecialChar), ctx));
}

/// \brief constructor for test module that simply appends a
///         character to the string in the param
/// \param ctx - context for the module
/// \param cnt - continuer to use when done
/// \param param - data that was passed as the module
///         was created so that specific data can be used when
///         he module is run
AppendChar::AppendChar(Cross::Context* ctx, Cross::Continuer* cnt, Param* p) :
    Cross::Module(ctx)
{
    if(p && p->appender)
    {
        *(p->appender) += p->c;

        SpecialChar* specChar = SpecialChar::Get(ctx);
        if(specChar)
        {
            *(p->appender) += specChar->GetExtraChar();
        }
    }

    if(cnt)
    {
        cnt->Continue(ctx);
    }
}

/// \brief constructor for test module that simply adds a new
///         service that all future modules will read from
///         and use to dynamically select a character to be
///         added.
/// \param ctx - context for the module
/// \param cnt - continuer to use when done
/// \param param - data that was passed as the module
///         was created so that specific data can be used when
///         he module is run
AdjustSpecialChar::AdjustSpecialChar(Cross::Context* ctx, Cross::Continuer* cnt, Param* p) :
    Cross::Module(ctx), mCharService(NULL)
{
    if(p)
    {
        mCharService = new SpecialChar(ctx, p->c);
        ctx->RegisterService(typeid(SpecialChar), mCharService);
    }

    if(cnt)
    {
        cnt->Continue(ctx);
    }
}

/// \brief destructor for adjustspecialchar module that will
///         clean up our local allocation for the service
AdjustSpecialChar::~AdjustSpecialChar()
{
    if(mCharService)
    {
        delete mCharService;
    }
}

/// \brief some of the tests rely on doing things a few times
///         and the lap count junction will continue to run
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

/// \brief constructor for the ModuleTest fixture that will be
///         used across all tests.  These variables should be
///         treated as "shared."
ModuleTest::ModuleTest() :
    mCtx(Cross::GenesisContext::Get()),
    mParamA('a', &mTestString), mA(&mParamA),
    mParamB('b', &mTestString), mB(&mParamB),
    mParamC('c', &mTestString), mC(&mParamC),
    mParamD('d', &mTestString), mD(&mParamD),
    mParamAdj('-'), mAdj(&mParamAdj),
    mTestError(Cross::ERR_UNKNOWN)
{
}

/// \brief this exists as a continuer callback that can be used
///         to store the error if one occurs.  This will be
///         checked against at the end of every test
void ModuleTest::ErrorStorage(Cross::ErrorCode e)
{
    mTestError = e;
}

/// \brief before every test is run, this will be called.
void ModuleTest::SetUp()
{
    mTestError = Cross::ERR_UNKNOWN;
}

/// \brief after every test is run, this will be called
void ModuleTest::TearDown()
{
}

