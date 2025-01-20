#include <boost/asio.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}
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

// OpenCV: 간단한 이미지 로드 및 표시
void testOpenCV()
{
    cv::Mat image = cv::imread("./assets/hyungjup_출입증사진.jpg");
    if (image.empty())
    {
        std::cerr << "OpenCV error: Failed to load jpg file" << std::endl;
        return;
    }
    cv::imshow("OpenCV Test", image);
    cv::waitKey(0); // 키 입력 대시
    std::cout << "OpenCV: Image displayed successfully" << std::endl;
}

// FFmpeg: 간단한 비디오 파일 정보 출력
void testFFmpeg(const char *filename)
{
    AVFormatContext *formatContext = avformat_alloc_context();
    if (!formatContext)
    {
        std::cerr << "FFmpeg error: Could not allocate format context" << std::endl;
        return;
    }

    if (avformat_open_input(&formatContext, filename, nullptr, nullptr) != 0)
    {
        std::cerr << "FFmpeg error: Could not open file" << std::endl;
        avformat_free_context(formatContext);
        return;
    }

    std::cout << "FFmpeg: File information for " << filename << std::endl;
    av_dump_format(formatContext, 0, filename, 0);
    avformat_close_input(&formatContext);
    avformat_free_context(formatContext);
}

// int main(int argc, char *argv[])
// {
//     std::cout << "Starting the P2P Video Streaming Test..." << std::endl;

//     // 1. Boost.Asio 테스트
//     testBoostAsio();

//     // 2. OpenCV 테스트
//     testOpenCV();

//     // 3. FFmpeg 테스트
//     if (argc > 1)
//     {
//         testFFmpeg(argv[1]);
//     }
//     else
//     {
//         std::cerr << "Usage: ./p2p-streaming <video-file>" << std::endl;
//     }
// }