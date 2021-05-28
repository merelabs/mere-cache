#ifndef TESTTLRUCACHE_H
#define TESTTLRUCACHE_H

#include <QtTest>

class TestTLRUCache : public QObject
{
    Q_OBJECT
public:
    TestTLRUCache(){};
    ~TestTLRUCache(){};


private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTTLRUCACHE_H
