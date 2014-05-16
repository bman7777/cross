/****************************************************************/
/// \class cross::Service.cpp
/// \ingroup Test
/// \date Apr 6, 2014
/// \brief Test various aspects of registering/using services
/****************************************************************/

#include <boost/bind.hpp>
#include "test/TestFixture.h"
#include "cross/Sequence/SequenceIterator.h"
#include "cross/Sequence/SeqStream.h"

/// \brief General test to confirm a service can be globally accessible
TEST_F(ModuleTest, GlobalService)
{
    using namespace Cross;

    SpecialChar specialChar(&mCtx, '+');
    mCtx.RegisterService(typeid(SpecialChar), &specialChar);

    SeqStream a;
    a>>mA>>mB>>mC;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(&mCtx, &complete);

    EXPECT_EQ("a+b+c+", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief General test to confirm a service can be globally accessible
TEST_F(ModuleTest, LocalizedService)
{
    using namespace Cross;

    SpecialChar specialChar(&mCtx, '+');
    mCtx.RegisterService(typeid(SpecialChar), &specialChar);

    SeqStream a;
    a>>mA>>mB>>mC;

    SeqStream b;
    b>>mAdj>>mA>>mB>>mC;

    SeqStream c;
    c>>mA>>mB>>mC;

    a>>SeqStream::Push>>b>>SeqStream::Pop>>c;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(&mCtx, &complete);

    EXPECT_EQ("a+b+c+a-b-c-a+b+c+", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

