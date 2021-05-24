#include "testfifocache.h"
#include "mere/cache/fifocache.h"

void TestFIFOCache::initTestCase()
{
}

void TestFIFOCache::cleanupTestCase()
{
}

void TestFIFOCache::testset()
{
    Mere::Cache::FIFOCache cache(2);
    cache.set("a", "first character");

    QVERIFY(cache.get("a").compare("first character") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);
}

void TestFIFOCache::testevict()
{
    Mere::Cache::FIFOCache cache(2);
    cache.set("a", "A");
    cache.set("b", "B");

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);

    cache.set("c", "C");
    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);
}
