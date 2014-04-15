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

    static SpecialChar* Get(Cross::Context* ctx);

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

class AdjustSpecialChar : public Cross::Module
{
public:
    static const Cross::Serial::Key CHAR = 0xd11d;

    AdjustSpecialChar(Cross::Context* cxt, Cross::Continuer* cnt=NULL, Cross::Serial* s=NULL);
    virtual ~AdjustSpecialChar();

private:
    SpecialChar* mCharService;
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
    void ErrorStorage(Cross::ErrorCode e);

protected:
    ModuleTest();

    void SetUp();
    void TearDown();

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

    Cross::Serial mParamAdj;
    Cross::ModuleWrapper<AdjustSpecialChar> mAdj;

    Cross::ErrorCode mTestError;
};

#endif /* TESTFIXTURE_H_ */
