#include <iostream>

#include "json.hpp"
#include "httplib.h"

using namespace std;

int main()
{
    httplib::Server svr;
    svr.listen("127.0.0.1", 7777);
    return 0;
}
