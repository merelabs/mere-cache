#ifndef TESTLIFOCACHE_H
#define TESTLIFOCACHE_H

#include <QtTest>

class TestLIFOCache : public QObject
{
    Q_OBJECT
public:
    TestLIFOCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTLIFOCACHE_H
