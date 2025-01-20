#include "client/client.hpp"
#include "node/server.hpp"
#include <thread>

int main()
{
    const int port = 8080;

    // 서버 실행
    std::thread serverThread([port]() {
        boost::asio::io_context io_context;
        Server server(io_context, port);
        server.start();
        io_context.run();
    });

    // 클라이언트 실행
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 서버 대기
    boost::asio::io_context io_context;
    Client client(io_context, "127.0.0.1", port);
    client.start();

    serverThread.join(); // 서버 스레드 정리
    return 0;
}