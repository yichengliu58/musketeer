#include "net/NetWorker.h"

using namespace musketeer;
using namespace std;

bool NetWorker::CheckAndSet(const InetAddr& localAddr)
{
    return listener.BindLocalAddr(localAddr);
}

void NetWorker::InitThread()
{
    workerThread.Start(true, index, [this](){ this->listener.Listen();});
}