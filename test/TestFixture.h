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
#include "cross/Sequence/Sequence.h"

class AppendChar : public Cross::Module
{
public:
	static const Cross::Serial::Key APPENDER = 0xd00d;
	static const Cross::Serial::Key CHAR = 0xd11d;

	AppendChar(Cross::Context* cxt, Cross::Continuer* cnt=NULL, Cross::Serial* s=NULL) :
		Cross::Module(cxt, cnt)
	{
		char c;
		std::string* str;

		if(s &&
		   s->GetData<char>(CHAR, c) &&
		   s->GetData<std::string>(APPENDER, str))
		{
			*str += c;
		}

		if(cnt)
		{
			cnt->Continue(cxt);
		}
	}

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

static Cross::ErrorCode sTestError = Cross::ERR_NONE;

class ModuleTest : public ::testing::Test, public Cross::Continuer
{
protected:
	static void ErrorStorage(Cross::ErrorCode e)
	{
		sTestError = e;
	}

	virtual void Continue(Cross::Context* ctx, Cross::ErrorCode e = Cross::ERR_NONE)
	{
		sTestError = e;
	}

	ModuleTest() : mA(&mParamA), mB(&mParamB), mC(&mParamC), mD(&mParamD)
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

	std::string mTestString;
	Cross::Context mCtx;

	Cross::Serial mParamA;
	Cross::ModuleWrapper<AppendChar> mA;

	Cross::Serial mParamB;
	Cross::ModuleWrapper<AppendChar> mB;

	Cross::Serial mParamC;
	Cross::ModuleWrapper<AppendChar> mC;

	Cross::Serial mParamD;
	Cross::ModuleWrapper<AppendChar> mD;
};

#endif /* TESTFIXTURE_H_ */
