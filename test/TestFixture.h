/*
 * TestFixture.h
 *
 *  Created on: Dec 17, 2013
 *      Author: brian
 */

#ifndef TESTFIXTURE_H_
#define TESTFIXTURE_H_

#include <gtest/gtest.h>
#include "cross/Context/Context.h"
#include "cross/Context/Continuer.h"
#include "cross/Context/FlowDefine.h"
#include "cross/Context/Module.h"
#include "cross/Context/ModuleWrapper.h"
#include "cross/Context/Serial.h"
#include "cross/Sequence/GenesisContext.h"
#include "cross/Sequence/Junction.h"
#include "cross/Service/Service.h"

class SpecialChar : public Cross::Service
{
public:
    static const Cross::Service::Key KEY;

    SpecialChar(Cross::Context* ctx, char c) : mContext(ctx), mChar(c) {}
    virtual ~SpecialChar() {}

    char GetExtraChar() const { return mChar; }

    static SpecialChar* Get(Cross::Context* ctx)
    {
        return static_cast<SpecialChar*>(Cross::Service::Get(KEY, ctx));
    }

private:
    Cross::Context* mContext;
    char mChar;
};

class AppendChar : public Cross::Module
{
public:
	static const Cross::Serial::Key APPENDER = 0xd00d;
	static const Cross::Serial::Key CHAR = 0xd11d;

	AppendChar(Cross::Context* cxt, Cross::Continuer* cnt=NULL, Cross::Serial* s=NULL);

    virtual ~AppendChar() {}
};

class LapCountJunction : public Cross::Junction
{
public:
	LapCountJunction(int numLaps, Cross::Context* ctx = Cross::GenesisContext::Get());
	virtual ~LapCountJunction() {}

	void Run(Cross::Context* ctx, Cross::Continuer* cnt);

private:
	int mNumLaps;
	int mCurrLap;
};

class ModuleTest : public ::testing::Test
{
public:
	void ErrorStorage(Cross::ErrorCode e)
	{
		mTestError = e;
	}

protected:

	ModuleTest() : mA(&mParamA), mB(&mParamB), mC(&mParamC), mD(&mParamD), mCtx(NULL), mTestError(Cross::ERR_UNKNOWN)
	{
		mParamA.AddData<std::string>(AppendChar::APPENDER, &mTestString);
		mParamA.AddData(AppendChar::CHAR, 'a');

		mParamB.AddData<std::string>(AppendChar::APPENDER, &mTestString);
		mParamB.AddData(AppendChar::CHAR, 'b');

		mParamC.AddData<std::string>(AppendChar::APPENDER, &mTestString);
		mParamC.AddData(AppendChar::CHAR, 'c');

		mParamD.AddData<std::string>(AppendChar::APPENDER, &mTestString);
		mParamD.AddData(AppendChar::CHAR, 'd');
	}

	void SetUp()
	{
	    mTestError = Cross::ERR_UNKNOWN;
	    mCtx = new Cross::Context(Cross::GenesisContext::Get());
	}

	void TearDown()
	{
	    delete mCtx;
	}

	std::string mTestString;
	Cross::Context* mCtx;

	Cross::Serial mParamA;
	Cross::ModuleWrapper<AppendChar> mA;

	Cross::Serial mParamB;
	Cross::ModuleWrapper<AppendChar> mB;

	Cross::Serial mParamC;
	Cross::ModuleWrapper<AppendChar> mC;

	Cross::Serial mParamD;
	Cross::ModuleWrapper<AppendChar> mD;

	Cross::ErrorCode mTestError;
};

#endif /* TESTFIXTURE_H_ */
