#ifndef TESTLRUCACHE_H
#define TESTLRUCACHE_H

#include <QtTest>

class TestLRUCache : public QObject
{
    Q_OBJECT
public:
    TestLRUCache(){};
    ~TestLRUCache(){};


private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTLRUCACHE_H
