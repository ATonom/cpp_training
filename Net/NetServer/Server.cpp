#include <ostream>

#include <net.h>

using namespace rav;

enum class EMessageType : uint32_t
{
    ServerAccept,
    ServerDeny,
    ServerPing,
    MessageAll,
    ServerMessage
};

class CustomServer : public net::IServer<EMessageType>
{
public:
    CustomServer(uint16_t port) : net::IServer<EMessageType>(port) {}

    bool onClientConnect(TShared_Ptr<net::TConnection<EMessageType>> client) override
    { 
        return true; 
    }
};

int main()
{
    CustomServer server(60000);
    server.start();

    while (1)
    {
        server.update(-1, true);
    }

    return 0;
}