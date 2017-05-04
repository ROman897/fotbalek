#ifndef PV264_PROJECT_UDPBASE_H
#define PV264_PROJECT_UDPBASE_H

#ifndef BUFFER_LEN
#define BUFFER_LEN 128
#endif // BUFFER_LEN

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <thread>

struct UdpBase {
    UdpBase() : m_work( io_service ), m_socket( io_service, boost::asio::ip::udp::v4()), m_dispatcher( &UdpBase::dispatch, this )
	{ }

    void stop() {
        io_service.stop();
        m_dispatcher.join();
	}

	void dispatch() {
		try {
			io_service.run();
		}
		catch ( const std::exception& ex ) {
			std::cerr << ex.what() << "\n";
			std::exit( 1 );
		}
	}

protected:
	boost::asio::io_service io_service;
	boost::asio::io_service::work m_work;
	boost::asio::ip::udp::socket m_socket;
    std::thread m_dispatcher;
    boost::array<char, BUFFER_LEN> m_buffer;
};

#endif //PV264_PROJECT_UDPBASE_H