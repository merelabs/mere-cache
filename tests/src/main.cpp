#include "testlrucache.h"
#include "testtlrucache.h"

int main(int argc, char** argv)
{
    int status = 0;
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
