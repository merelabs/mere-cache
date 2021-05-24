#include "testlrucache.h"
#include "testtlrucache.h"
#include "testfifocache.h"
#include "testlifocache.h"

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
    {
        TestTLRUCache test;
        status |= QTest::qExec(&test, argc, argv);
    }
    return status;
}
