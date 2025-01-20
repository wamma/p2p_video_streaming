#include "server.hpp"

Server::Server(boost::asio::io_context &io_context, int port)
    : _io_context(io_context), _acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
}

void Server::start()
{
    acceptConnection();
}

void Server::acceptConnection()
{
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(_io_context);
    _acceptor.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec)
        {
            std::cout << "Client connected: " << socket->remote_endpoint() << std::endl;

            // 간단한 메시지 전송
            std::string message = "Hello from Server!";
            boost::asio::async_write(*socket, boost::asio::buffer(message),
                                     [socket](boost::system::error_code ec, std::size_t /*length*/) {
                                         if (!ec)
                                         {
                                             std::cout << "Message sent to client." << std::endl;
                                         }
                                         else
                                         {
                                             std::cerr << "Error sending message: " << ec.message() << std::endl;
                                         }
                                     });
        }
        else
        {
            std::cerr << "Error accepting connection: " << ec.message() << std::endl;
        }
        acceptConnection(); // 다음 연결 대기
    });
}
