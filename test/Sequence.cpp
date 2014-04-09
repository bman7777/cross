/*
 * Sequence.cpp
 *
 *  Created on: Dec 17, 2013
 *      Author: brian
 */

#include <boost/bind.hpp>
#include "test/TestFixture.h"
#include "cross/Sequence/AutoDirectionStrategy.h"
#include "cross/Sequence/DirectionModuleDecorator.h"
#include "cross/Sequence/Junction.h"
#include "cross/Sequence/PriorityDirectionStrategy.h"
#include "cross/Sequence/SequenceIterator.h"
#include "cross/Sequence/SeqStream.h"

/// \brief General test to confirm that forward directional paths run and in proper order
///         (a) -> (b) -> (c)
TEST_F(ModuleTest, ForwardSimpleTree)
{
    using namespace Cross;

    SeqStream a;
    a>>mA>>mB>>mC;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("abc", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief General test to confirm that backward directional paths run and in proper order
///         (a) <- (b) <- (c)
TEST_F(ModuleTest, BackwardSimpleTree)
{
    using namespace Cross;

    SeqStream c;
    c<<mC<<mB<<mA;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));
    AutoDirectionStrategy dir(DIR_BACKWARD);
    SequenceIterator iter(c.GetHead(), &dir);
    iter.Run(mCtx, &complete);

    EXPECT_EQ("cba", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief General test to confirm that a tiny tree runs as expected
///         (a)
TEST_F(ModuleTest, MinimalTree)
{
    using namespace Cross;

    SeqStream a(&mA);

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("a", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief General test to confirm that multi directional paths run and in proper order
///         (a) <-> (b) <-> (c)
TEST_F(ModuleTest, DynamicTree)
{
    using namespace Cross;

    AutoDirectionStrategy dir(DIR_FORWARD);
    DirectionModuleDecorator updateDirAndC(&dir, DIR_BACKWARD, &mC);

    SeqStream a;
    a>>mA>>mB>>updateDirAndC<<mB<<mA;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead(), &dir);
    iter.Run(mCtx, &complete);

    EXPECT_EQ("abcba", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief Test to confirm that a cyclical tree functions properly
/*  (a)
     |  ^
     v   \
    (b)->(c)
*/
TEST_F(ModuleTest, CycleTree)
{
    using namespace Cross;

    LapCountJunction lap(3);
    SeqStream a;

    a>>lap>>mA>>mB>>mC>>lap;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("abcabcabc", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief General test to confirm that forking paths allow a dynamic decision
/*   (a)
      |
     (b)
    / | \
  (b)(c)(d)
*/
TEST_F(ModuleTest, ForkTree)
{
    using namespace Cross;

    SeqStream a;

    PriorityDirectionStrategy priorityDir;
    priorityDir.AddNextHighestPriority(&mD, DIR_FORWARD);

    Junction decision(&priorityDir);

    a>>mA>>mB<<mC>>mB>>decision;
        decision>>mB;
        decision>>mD>>mA>>mD;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(a.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("abcbdad", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief Test to confirm that multiple trees can be connected together
/*  (a)
     |
    (a)
     |
    (a)  ---> (b) - (b) - (b)   --->  (c)
                                       |
                                      (c)
                                       |
                                      (c)
*/
TEST_F(ModuleTest, TreeOfTrees)
{
    using namespace Cross;

    SeqStream aSeq;
    aSeq>>SeqStream::Push>>mA>>mA>>mA;

    SeqStream bSeq;
    bSeq>>SeqStream::Push>>mB>>mB>>mB;

    SeqStream cSeq;
    cSeq>>SeqStream::Push>>mC>>mC>>mC;

    SeqStream all = aSeq>>bSeq>>cSeq;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(all.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("aaabbbccc", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief build up a stream with smaller streams constructed out of order
TEST_F(ModuleTest, UnorderedInsertion)
{
    using namespace Cross;

    SeqStream streamFirst;
    SeqStream streamLast;
    SeqStream streamMiddle;

    streamFirst>>mA>>mA;
    streamLast>>mC>>mC;
    streamMiddle>>mB>>mB;

    streamFirst>>streamMiddle>>streamLast;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(streamFirst.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("aabbcc", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/// \brief build up smaller sequences that are appended together as one large stream
TEST_F(ModuleTest, IsolatedFlows)
{
    using namespace Cross;

    SeqStream s;
    LapCountJunction lapFirst(2);
    LapCountJunction lapSecond(3);

    s>>SeqStream::Push>>lapFirst>>mA>>mB>>lapFirst>>SeqStream::Pop>>SeqStream::Push>>lapSecond>>mC>>mA>>lapSecond;

    CallbackContinuer complete(boost::bind(&ModuleTest::ErrorStorage, this, _1));

    SequenceIterator iter(s.GetHead());
    iter.Run(mCtx, &complete);

    EXPECT_EQ("ababcacaca", mTestString);
    EXPECT_EQ(ERR_NONE, mTestError);
}

/*
        a
      /   \
     b     c
          /  \
         d    e

ways to connect:
 - branching paths
 - a tree full of the same kind of module (A-A-A)
 - paths are connected cyclically
 - paths that have single direction connections
 - paths that have dual direction connections
 - add to the tree while traversing it
 - a decision point surrounded by multiple

ways to traverse:
 - given a root node keep flowing backwards/forwards to the end
 - use transition points automatically or manually
 - run the tree more than one time
 - simultaneously run different parts of the tree
 */
