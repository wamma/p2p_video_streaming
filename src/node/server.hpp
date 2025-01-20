#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <iostream>

class Server
{
  private:
    boost::asio::io_context &_io_context;
    boost::asio::ip::tcp::acceptor _acceptor;

    void acceptConnection();

  public:
    Server(boost::asio::io_context &io_context, int port);
    void start();
};

#endif