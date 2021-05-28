#ifndef TESTLFUCACHE_H
#define TESTLFUCACHE_H

#include <QtTest>

class TestLFUCache : public QObject
{
    Q_OBJECT
public:
    TestLFUCache(){};

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testset();
    void testevict();
};

#endif // TESTLFUCACHE_H
