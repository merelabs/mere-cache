#ifndef TESTMRUCACHE_H
#define TESTMRUCACHE_H

#include <QtTest>

class TestMRUCache : public QObject
{
    Q_OBJECT
public:
    TestMRUCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTMRUCACHE_H
