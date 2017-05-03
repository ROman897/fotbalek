#ifndef UDPSERVER
#define UDPSERVER

#ifndef MAX_PLAYERCOUNT
#define MAX_PLAYERCOUNT 6
#endif // MAX_PLAYERCOUNT

#ifndef PORT_NUMBER
#define PORT_NUMBER 13000
#endif // PORT_NUMBER

#include "../Client/UdpBase.h"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <memory>
#include <mutex>
#include <condition_variable>

class UdpServer : UdpBase {
    using udp = boost::asio::ip::udp;

    struct Client {
        Client(udp::endpoint &&endpt, std::string &&name, unsigned short index) :
            m_endpt(endpt),
            m_name(name),
            m_index(index) {}
        const udp::endpoint m_endpt;
        const std::string m_name;
        const unsigned short m_index;

        const boost::array<char, BUFFER_LEN> &data() const;
        boost::array<char, BUFFER_LEN> &data();
        bool newData() const;
        void setNewData(bool val);
        void swapBuffers(boost::array<char, BUFFER_LEN> &other);
    private:
        boost::array<char, BUFFER_LEN> m_buffer;
        bool m_newData = false;
        mutable std::mutex m_lk; //???
        std::condition_variable m_alarm;
    };

    udp::endpoint m_pending;
    std::vector<std::unique_ptr<Client>> m_clients;
    unsigned short m_clientNr = 0;
    std::mutex m_lk;
    std::condition_variable m_alarm;

    void listen();
    void handleRequest(const boost::system::error_code& error, size_t transferred);
    void respond(const udp::endpoint &cl, const std::string &response);
    void respondAll(const std::string &response);
    void emplaceClient(udp::endpoint endpt, size_t trans);
    void responseHandler(const boost::system::error_code & err, size_t trans);
    void abandonClient(unsigned short client_index);
    void parseInput(size_t length);
    size_t indexFromBuffer(int start, int end);
    bool endptEq(const udp::endpoint &a, const udp::endpoint &b) const;

public:
    UdpServer() {
        m_clients.resize(MAX_PLAYERCOUNT);
        m_socket.bind(udp::endpoint(udp::v4(), PORT_NUMBER));
    }
    ~UdpServer() {
        stop();
    }

    void init();
};

#endif // UDPSERVER
