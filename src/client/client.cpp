#include "client.hpp"

Client::Client(boost::asio::io_context &io_context, const std::string &host, int port)
    : _io_context(io_context), _socket(io_context)
{
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::connect(_socket, resolver.resolve(host, std::to_string(port)));
}

void Client::start()
{
    _socket.async_read_some(boost::asio::buffer(_buffer), [this](boost::system::error_code ec, std::size_t length) {
        if (!ec)
        {
            std::cout << "Message from server: " << std::string(_buffer.data(), length) << std::endl;
        }
        else
        {
            std::cerr << "Error reading from server: " << ec.message() << std::endl;
        }
    });

    try
    {
        _io_context.run(); // 안전하게 실행
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in io_context: " << e.what() << std::endl;
    }
}
