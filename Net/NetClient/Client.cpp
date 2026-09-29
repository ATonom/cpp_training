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

class CustomClient : public net::IClient<EMessageType>
{
public:

};


int main()
{
    CustomClient client;
    client.connect("127.0.0.1", 60000);

    bool bQuit = false;
    while (!bQuit)
    {
        if (client.isConnected())
        {
            if (!client.incoming().empty())
            {

            }
        }
        else
        {
            std::cout << "Server dawn\n";
            bQuit = true;
        }
    }

    return 0;
}