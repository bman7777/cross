/*
 * TestFixture.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: brian
 */

#include "test/TestFixture.h"
#include "cross/Sequence/Sequence.h"

/// \brief define the specialchar service that will be used
///         to test various forms of service specialization
const Cross::Service::Key SpecialChar::KEY = Cross::Service::MakeKey();

/// \brief getter for the specialchar service that will
///         prevent the need for static casting from service
///         base class
/// \param context - context to get service from
SpecialChar* SpecialChar::Get(Cross::Context* ctx)
{
    return static_cast<SpecialChar*>(Cross::Service::Get(KEY, ctx));
}

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

/// \brief constructor for test module that simply adds a new
///         service that all future modules will read from
///         and use to dynamically select a character to be
///         added.
/// \param ctx - context for the module
/// \param cnt - continuer to use when done
/// \param serial - data that was passed as the module
///         was created so that specific data can be used when
///         he module is run
AdjustSpecialChar::AdjustSpecialChar(Cross::Context* ctx, Cross::Continuer* cnt, Cross::Serial* s) :
    Cross::Module(ctx, cnt), mCharService(NULL)
{
    char c;
    if(s && s->GetData<char>(CHAR, c))
    {
        mCharService = new SpecialChar(ctx, c);
        ctx->RegisterService(SpecialChar::KEY, mCharService);
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

/// \brief constructor for the ModuleTest fixture that will be
///         used across all tests.  These variables should be
///         treated as "shared."
ModuleTest::ModuleTest() : mA(&mParamA), mB(&mParamB), mC(&mParamC), mD(&mParamD),
    mAdj(&mParamAdj), mCtx(NULL), mTestError(Cross::ERR_UNKNOWN)
{
    mParamA.AddData<std::string>(AppendChar::APPENDER, &mTestString);
    mParamA.AddData(AppendChar::CHAR, 'a');

    mParamB.AddData<std::string>(AppendChar::APPENDER, &mTestString);
    mParamB.AddData(AppendChar::CHAR, 'b');

    mParamC.AddData<std::string>(AppendChar::APPENDER, &mTestString);
    mParamC.AddData(AppendChar::CHAR, 'c');

    mParamD.AddData<std::string>(AppendChar::APPENDER, &mTestString);
    mParamD.AddData(AppendChar::CHAR, 'd');

    mParamAdj.AddData(AdjustSpecialChar::CHAR, '-');
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
    mCtx = Cross::GenesisContext::Get();
}

/// \brief after every test is run, this will be called
void ModuleTest::TearDown()
{
    // nothing for now
}

