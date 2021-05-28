#include "testlifocache.h"
#include "mere/cache/lifocache.hpp"

void TestLIFOCache::initTestCase()
{
}

void TestLIFOCache::cleanupTestCase()
{
}

void TestLIFOCache::testset()
{
    Mere::Cache::LIFOCache<std::string, std::string> cache(2);
    cache.set("a", "first character");

    QVERIFY(cache.get("a").compare("first character") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);
}

void TestLIFOCache::testevict()
{
    Mere::Cache::LIFOCache<std::string, std::string> cache(2);
    cache.set("a", "A");
    cache.set("b", "B");

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);

    cache.set("c", "C");
    QVERIFY(cache.get("b", &set).compare("") == 0);
    QVERIFY(!set);
}
