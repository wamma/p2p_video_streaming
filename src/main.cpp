#include "client/client.hpp"
#include "node/server.hpp"
#include <thread>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " server [<port>]\n" << " " << argv[0] << " client <host> <port>\n";
        return 1;
    }

    std::string mode = argv[1];
    boost::asio::io_context io_context;

    if (mode == "server")
    {
        int port = 12345;
        if (argc >= 3)
            port = std::atoi(argv[2]);

        Server server(io_context, port);
        server.start();

        std::cout << "Server is running on port " << port << std::endl;
        io_context.run();
    }
    else if (mode == "client")
    {
        if (argc < 4)
        {
            std::cerr << "Usage " << argv[0] << " client <host> <port>\n";
            return 1;
        }
        std::string host = argv[2];
        int port = std::atoi(argv[3]);

        Client client(io_context, host, port);
        std::cout << "Connecting to " << host << ":" << port << std::endl;
        client.start();

        // 주의: Client::start() 내부에서 io_context.run()이 호출되므로,
        // 여기서 별도로 io_context.run()을 호출할 필요는 없습니다.
    }
    else
    {
        std::cerr << "Invalid mode." << std::endl;
        return 1;
    }

    return 0;
}