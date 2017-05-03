#include "UdpServer.h"
#include <boost/bind.hpp>
#include <iostream> //potom prec
#include <functional>
#include <cmath>

void UdpServer::listen() {
    m_socket.async_receive_from(boost::asio::buffer(m_buffer),
                               m_pending,
                               boost::bind(&UdpServer::handleRequest,
                                           this,
                                           boost::asio::placeholders::error,
                                           boost::asio::placeholders::bytes_transferred));
}

void UdpServer::handleRequest(const boost::system::error_code& error, size_t transferred) {
    if (transferred > BUFFER_LEN) {
        listen();
        return;
    }
    if (error) {
        if (error == boost::asio::error::eof) {
            for (auto &i : m_clients) {
                if (i && endptEq(m_pending, i->m_endpt)) {
                    abandonClient(i->m_index);
                    return;
                }
            }
        }
        std::cerr << "vyplo ta\n";
        std::exit(1);
    }

    std::cout << "recvd " << transferred << std::endl; //debugovacie vypisy
    for (size_t i = 0; i < transferred; ++i) {
        std::cout << m_buffer[i];
    }
    std::cout << std::endl << "from " << m_pending.address() << std::endl;

    parseInput(transferred);
    listen();
}

void UdpServer::respond(const udp::endpoint &cl, const std::string &response) {
    std::cout << "sending to " << cl.address() << ":" << cl.port() << '\n';
    m_socket.async_send_to(boost::asio::buffer(response),
                          cl,
                          boost::bind(&UdpServer::responseHandler,
                                      this,
                                      boost::asio::placeholders::error,
                                      boost::asio::placeholders::bytes_transferred));
}

void UdpServer::respondAll(const std::string &response) {
    for (auto &i : m_clients) {
        if (i)
            respond(i->m_endpt, response);
    }
}

void UdpServer::init() {
    listen();
    //dispatch();
}

void UdpServer::responseHandler(const boost::system::error_code &err, size_t trans) {
	if ( err ) {
		std::cerr << "Client error: " << err.message() << "bytes transfered: " << trans  << ", exiting\n";
		std::exit( 1 );
	}
}

void UdpServer::emplaceClient(udp::endpoint endpt, size_t trans) {
    if (m_clientNr >= MAX_PLAYERCOUNT) {
        respond(endpt, {"full\n"});
        return;
    }

    //poslat mu jeho index a indexy vsetkych aj s menami + vsetkym ostatnym jeho meno a index
    std::string newName(&m_buffer[2], &m_buffer[trans]);
    unsigned short viable_index = MAX_PLAYERCOUNT - 1;
    for (unsigned i = 0; i < MAX_PLAYERCOUNT; ++i) {
        if (!m_clients[i] && viable_index == MAX_PLAYERCOUNT - 1)
            viable_index = i;
        if (m_clients[i] && endptEq(m_clients[i]->m_endpt, endpt)) {
            respond(endpt, {"you've already logged in\n"});
            return;
        }
    }

    for (auto &i : m_clients) {
        if (i && i->m_name == newName) {
            respond(endpt, "A player with that name is already present\n");
            return;
        }
    }
    m_clients[viable_index] = std::make_unique<Client>(std::move(endpt), std::move(newName), viable_index);
    std::cout << "new guy's name: " << m_clients[viable_index]->m_name << std::endl;
    ++m_clientNr;
    std::cout << "port: " << m_clients[viable_index]->m_endpt.port() << '\n';
    respond(m_clients[viable_index]->m_endpt, {std::string("you got a new index: ") +
                                              std::to_string(viable_index) +
                                              "\n"});
}

void UdpServer::abandonClient(unsigned short client_index) {
    m_clients[client_index] = nullptr;
    --m_clientNr;
    std::cout << "client " << client_index << " has disconnected\n";
}

void UdpServer::parseInput(size_t length) {
    enum class state {
        init,
        new_pl,
        ind
    };

    unsigned short index = 0;
    size_t index_start = 0;
    state currSt = state::init;
    for (size_t i = 0; i < length; ++i) {
        switch (currSt) {
        case state::init : {
            if (std::isdigit(m_buffer[i])) {
                index_start = i;
                currSt = state::ind;
            } else if (m_buffer[i] == 'i') {
                currSt = state::new_pl;
            } else {
                return;
            }
            break;
        }
        case state::new_pl : {
            if (m_buffer[i] == '?' && length > 2)
                emplaceClient(m_pending, length);
            return;
        }
        case state::ind : {
            if (std::isdigit(m_buffer[i]))
                continue;
            if (m_buffer[i] == '_') {
                index = indexFromBuffer(index_start, i - 1);
                if (!m_clients[index] || !endptEq(m_pending, m_clients[index]->m_endpt))
                    return;
                m_clients[index]->swapBuffers(m_buffer);
                m_clients[index]->setNewData(true);
                m_clients[index]->data()[length] = '\0'; // <<< mozno nebude treba, este zistit ako sa bude spravat
                std::cout << "client " << index << " sent ";
                for (size_t j = 0; j < length; ++j) {
                    std::cout << m_clients[index]->data()[j];
                }
                std::cout << std::endl << "port: " << m_clients[index]->m_endpt.port() << '\n';
                respond(m_clients[index]->m_endpt, "jaaaaaaaaj ty kkt");
            }
            return;
        }
        }
    }
}

size_t UdpServer::indexFromBuffer(int start, int end) {
    unsigned pow = 0;
    size_t res = 0;

    for (int i = end; i >= start; --i) {
        res += (m_buffer[i] - '0') * std::pow(10, pow);
        ++pow;
    }
    return res;
}

bool UdpServer::endptEq(const udp::endpoint &a, const udp::endpoint &b) const {
    return a.address() == b.address();
}

const boost::array<char, 128> &UdpServer::Client::data() const {
    return m_buffer; // rozmyslet ako s tread-safety
}

boost::array<char, 128> &UdpServer::Client::data() {
    return m_buffer; // rozmyslet ako s tread-safety
}

bool UdpServer::Client::newData() const {
    std::unique_lock<std::mutex> lk(m_lk);
    bool res = m_newData;
    lk.unlock();
    //m_alarm.notify_all();
    return res;
}

void UdpServer::Client::setNewData(bool val) {
    std::unique_lock<std::mutex> lk(m_lk);
    m_newData = val;
    lk.unlock();
    m_alarm.notify_all();
}

void UdpServer::Client::swapBuffers(boost::array<char, BUFFER_LEN> &other) {
    std::unique_lock<std::mutex> lk(m_lk);
    std::swap(m_buffer, other);
    lk.unlock();
    m_alarm.notify_all();
}
