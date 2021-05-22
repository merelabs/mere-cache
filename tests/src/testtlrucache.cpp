#include "testtlrucache.h"
#include "mere/cache/tlrucache.h"

void TestTLRUCache::initTestCase()
{
}

void TestTLRUCache::cleanupTestCase()
{
}

void TestTLRUCache::testset()
{
    Mere::Cache::TLRUCache cache(2);
    cache.set("a", "first character");

    QVERIFY(cache.get("a").compare("first character") == 0);
    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);
}

void TestTLRUCache::testevict()
{
    Mere::Cache::TLRUCache cache(2);
    cache.set("a", "first character");

    bool set;
    QVERIFY(cache.get("a", &set).compare("first character") == 0);
    QVERIFY(set);

    cache.set("b", "second character");
    cache.set("c", "third character");

    QVERIFY(cache.get("a", &set).compare("") == 0);
    QVERIFY(!set);
}
