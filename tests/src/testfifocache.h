#ifndef TESTFIFOCACHE_H
#define TESTFIFOCACHE_H

#include <QtTest>

class TestFIFOCache : public QObject
{
    Q_OBJECT
public:
    TestFIFOCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTFIFOCACHE_H
