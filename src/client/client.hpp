#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <boost/asio.hpp>
#include <iostream>

class Client
{
  private:
    boost::asio::io_context &_io_context;
    boost::asio::ip::tcp::socket _socket;
    std::array<char, 1024> _buffer;

  public:
    Client(boost::asio::io_context &io_context, const std::string &host, int port);
    void start();
};

#endif