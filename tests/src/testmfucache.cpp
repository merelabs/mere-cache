#include "testmfucache.h"
#include "mere/cache/mfucache.hpp"

void TestMFUCache::initTestCase()
{
}

void TestMFUCache::cleanupTestCase()
{
}

void TestMFUCache::testset()
{
    Mere::Cache::MFUCache<std::string, std::string> cache(2);
    cache.set("a", "A");
    QVERIFY(cache.get("a").compare("A") == 0);

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);
}

void TestMFUCache::testevict()
{
    Mere::Cache::MFUCache<std::string, std::string> cache(2);
    cache.set("a", "A");
    cache.set("b", "B");

    cache.get("a");
    cache.get("a");
    cache.get("b");

    cache.set("c", "C");

    bool set;
    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);

    QVERIFY(cache.get("b", &set).compare("B") == 0);
    QVERIFY(set);
}
