#include "testlrucache.h"
#include "mere/cache/lrucache.hpp"

void TestLRUCache::initTestCase()
{
}

void TestLRUCache::cleanupTestCase()
{
}

void TestLRUCache::testset()
{
    Mere::Cache::LRUCache<std::string, std::string> cache(2);
    cache.set("a", "A");

    QVERIFY(cache.get("a").compare("A") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);
}

void TestLRUCache::testevict()
{
    Mere::Cache::LRUCache<std::string, std::string> cache(2);
    cache.set("a", "A");

    bool set;
    QVERIFY(cache.get("a", &set).compare("A") == 0);
    QVERIFY(set);

    cache.set("b", "B");
    cache.set("c", "C");

    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);
}
