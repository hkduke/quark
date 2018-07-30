/*
 * a prototype to test the usage of epoll/poll.
 *
 * */
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>

#include <sys.h>
#include <misc.h>


using quark::os::Error;
using quark::os::Thread;

namespace localsock {
    typedef int sock_fd;
    
    struct address_port {
        address_port(const char *addr, const char *port) : addr_(addr),
            port_(port), port_str_(nullptr){ }
        address_port(const char *addr, short int port) : addr_(addr) {
            port_str_ = (char *)malloc(64);
            snprintf(port_str_, 64, "%hd", port);
            port_ = (const char*)port_str_;
        }
        ~address_port() {
            if (port_str_ != nullptr) {
                free(port_str_);
            }
        }
        
        const char *addr_;
        const char *port_;
        char *port_str_;
    };



    enum {
        RET_FAILED  = -1,
        RET_OK      =  0,
    };

    int set_async(sock_fd s, bool async) {
        int flags = fcntl(s, F_GETFL);
        if (flags < 0) {
            goto ERR;
        }
        flags = async ? 
            flags | O_NONBLOCK : flags & (~O_NONBLOCK);
        if (fcntl(s, F_SETFL, flags) < 0 ) {
            goto ERR;
        }
        return RET_OK;
    ERR:
        QuarkFatal("set_async", errno);
        return RET_FAILED;
    }
    
    struct addrinfo* _get_socket_material(address_port *ap) {
        struct addrinfo hint;
        struct addrinfo *res = NULL;
        int ret;
        hint.ai_family = AF_UNSPEC;
        hint.ai_socktype = SOCK_STREAM;

        ret = ::getaddrinfo(ap->addr_, ap->port_, &hint, &res);
        if (ret != 0 ) {
            return nullptr;
        }
        
        return res;
    }

}


class Poller : public Thread<Poller>::dthread {
    public:
        void WorkLoop(Poller* p) {
                   
        }
};
