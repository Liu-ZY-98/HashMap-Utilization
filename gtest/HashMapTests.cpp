// HashMapTests.cpp
//
// ICS 45C Fall 2018
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided one test already,
// though I've commented it out, because it won't compile until you've implemented
// three things: the HashMap constructor, the HashMap destructor, and HashMap's
// size() member function.

#include <gtest/gtest.h>
#include "HashMap.hpp"



TEST(TestHashMap, sizeOfNewlyCreatedHashMapIsZero)
{
   HashMap empty;
   ASSERT_EQ(0, empty.size());
}

namespace
{
    int oneValueHashFunction(const std::string& s)
    {
        return 5;
    }
}
TEST(TestHashMap, sizeIsOneAfterAddingOneElement)
{
    HashMap empty;
    empty.add("aaa","bbb");
    ASSERT_EQ(1, empty.size());
    ASSERT_EQ(10, empty.bucketCount());
}

TEST(TestHashMap, testMaxBucket)
{
    HashMap hm(oneValueHashFunction);
    hm.add("a","b");
    hm.add("c","d");
    hm.add("e","f");
    ASSERT_EQ(0.3, hm.loadFactor());
    ASSERT_EQ(3, hm.maxBucketSize());
}

TEST(TestHashMap, testAddAndRemoveAndContains)
{
    HashMap hm;
    hm.add("a","b");
    hm.add("a","d");
    hm.add("e","f");
    ASSERT_EQ(2, hm.size());
    hm.remove("a");
    ASSERT_EQ(1, hm.size());
    ASSERT_EQ(false, hm.contains("a"));
    ASSERT_EQ(true, hm.contains("e"));
}

TEST(TestHashMap, testValue)
{
    HashMap hm;
    hm.add("a","b");
    ASSERT_EQ("b", hm.value("a"));
    hm.remove("a");
    ASSERT_EQ("", hm.value("a"));
}

TEST(TestHashMap, testLoadFactor)
{
    HashMap hm;
    hm.add("a","b");
    hm.add("b","b");
    hm.add("c","b");
    hm.add("d","b");
    hm.add("e","b");
    hm.add("f","b");
    hm.add("g","b");
    hm.add("h","b");
    ASSERT_EQ(0.8, hm.loadFactor());
    ASSERT_EQ(10, hm.bucketCount());
    ASSERT_EQ(true, hm.contains("a"));
    hm.add("i","b");
    ASSERT_EQ(9, hm.size());
    ASSERT_EQ(21, hm.bucketCount());
    ASSERT_EQ(true, hm.contains("a"));
    ASSERT_EQ(true, hm.contains("i"));
}

