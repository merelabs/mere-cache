#include "testlrucache.h"
#include "mere/cache/lrucache.h"

void TestLRUCache::initTestCase()
{
}

void TestLRUCache::cleanupTestCase()
{
}

void TestLRUCache::testset()
{
    Mere::Cache::LRUCache<std::string, std::string> cache(2);
    cache.set("a", "first character");

    QVERIFY(cache.get("a").compare("first character") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);
}

void TestLRUCache::testevict()
{
    Mere::Cache::LRUCache<std::string, std::string> cache(2);
    cache.set("a", "first character");

    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);

    cache.set("b", "second character");
    cache.set("c", "third character");

    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);
}
