#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>

#include <boost/asio.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

// Boost.Asio: 간단한 TCP 연결 테스트
void testBoostAsio()
{
    try
    {
        boost::asio::io_context ioContext;

        // DNS 해석
        boost::asio::ip::tcp::resolver resolver(ioContext);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("www.google.com", "80");
        std::cout << "Boost.Asio: Resolved www.google.com" << std::endl;

        // TCP 소켓 생성 및 연결
        boost::asio::ip::tcp::socket socket(ioContext);
        boost::asio::connect(socket, endpoints);
        std::cout << "Boost.Asio: Connected to www.google.com" << std::endl;

        // 서버에 HTTP GET 요청 보내기
        std::string request = "GET / HTTP/1.1\r\nHost: www.google.com\r\nConnection: close\r\n\r\n";
        boost::asio::write(socket, boost::asio::buffer(request));

        // 서버 응답 읽기
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");

        // 응답 출력
        std::istream responseStream(&response);
        std::string httpResponse;
        std::getline(responseStream, httpResponse);
        std::cout << "Server Response: " << httpResponse << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Boost.Asio error: " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    std::cout << "Starting the P2P Video Streaming Test..." << std::endl;

    // 1. Boost.Asio 테스트
    testBoostAsio();

    // // 2. OpenCV 테스트
    // testOpenCV();

    // // 3. FFmpeg 테스트
    // if (argc > 1)
    // {
    //     testFFmpeg(argv[1]);
    // }
    // else
    // {
    //     std::cerr << "Usage: ./p2p-streaming <video-file>" << std::endl;
    // }
}