#ifndef TESTMFUCACHE_H
#define TESTMFUCACHE_H

#include <QtTest>

class TestMFUCache : public QObject
{
    Q_OBJECT
public:
    TestMFUCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTMFUCACHE_H
