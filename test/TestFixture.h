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
#include "cross/Sequence/GenesisContext.h"
#include "cross/Sequence/Junction.h"
#include "cross/Service/Service.h"

class SpecialChar : public Cross::Service
{
public:
    static const DataContext::Key& Type();

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
    struct Param
    {
        const char c;
        std::string* appender;

        Param() : c(' '), appender(NULL) {}
        Param(const char letter, std::string* str) : c(letter), appender(str) {}
    };

    AppendChar(Cross::Context* cxt, Cross::Continuer* cnt=NULL, Param* p=NULL);
    virtual ~AppendChar() {}
};

class AdjustSpecialChar : public Cross::Module
{
public:
    struct Param
    {
        char c;

        Param(char letter=' ') : c(letter) {}
    };

    AdjustSpecialChar(Cross::Context* cxt, Cross::Continuer* cnt=NULL, Param* p=NULL);
    virtual ~AdjustSpecialChar();

private:
    SpecialChar* mCharService;
};

class LapCountJunction : public Cross::Junction
{
public:
    LapCountJunction(int numLaps, Cross::Context* ctx = NULL);
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
    ~ModuleTest() {}

    void SetUp();
    void TearDown();

    std::string mTestString;
    Cross::Context* mCtx;

    AppendChar::Param mParamA;
    Cross::ModuleWrapper<AppendChar, AppendChar::Param> mA;

    AppendChar::Param mParamB;
    Cross::ModuleWrapper<AppendChar, AppendChar::Param> mB;

    AppendChar::Param mParamC;
    Cross::ModuleWrapper<AppendChar, AppendChar::Param> mC;

    AppendChar::Param mParamD;
    Cross::ModuleWrapper<AppendChar, AppendChar::Param> mD;

    AdjustSpecialChar::Param mParamAdj;
    Cross::ModuleWrapper<AdjustSpecialChar, AdjustSpecialChar::Param> mAdj;

    Cross::ErrorCode mTestError;
};

#endif /* TESTFIXTURE_H_ */
