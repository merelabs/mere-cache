#include "testfifocache.h"
#include "testlifocache.h"
#include "testlrucache.h"
#include "testlfucache.h"
#include "testtlrucache.h"
#include "testmrucache.h"
#include "testmfucache.h"
#include "testarccache.h"

int main(int argc, char** argv)
{
    int status = 0;
    {
        TestFIFOCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TestLIFOCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TestLRUCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
//    {
//        TestTLRUCache test;
//        status |= QTest::qExec(&test, argc, argv);
//    }
    {
        TestLFUCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TestMRUCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TestMFUCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    {
        TestARCCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    return status;
}
