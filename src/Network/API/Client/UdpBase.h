#ifndef PV264_PROJECT_UDPBASE_H
#define PV264_PROJECT_UDPBASE_H

#ifndef BUFFER_LEN
#define BUFFER_LEN 256
#endif // BUFFER_LEN

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <thread>

struct UdpBase {
  using ErrorCode = const boost::system::error_code;
  using udp = boost::asio::ip::udp;

  UdpBase()
      : m_work(io_service), m_socket(io_service, udp::v4()),
        m_dispatcher(&UdpBase::dispatch, this) {}

  void stop() {
    io_service.stop();
    m_dispatcher.join();
  }

  void dispatch() {
    try {
      io_service.run();
    } catch (const std::exception &ex) {
      std::cerr << ex.what() << std::endl;
      std::exit(1);
    }
  }

protected:
  boost::asio::io_service io_service;
  boost::asio::io_service::work m_work;
  udp::socket m_socket;
  std::thread m_dispatcher;
  boost::array<char, BUFFER_LEN> m_buffer;
};

#endif // PV264_PROJECT_UDPBASE_H
