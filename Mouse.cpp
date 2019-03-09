#include "Mouse.hpp"
#include <stdexcept>
#include <poll.h>

extern "C"
{
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
}

bool MouseEvent::lmb()
{
    return data[0] & 0x1;
}

bool MouseEvent::rmb()
{
    return data[0] & 0x2;
}

char MouseEvent::xrel()
{
    return data[1];
}

char MouseEvent::yrel()
{
    return data[2];
}

int fd = open("/dev/input/mice", O_RDONLY);
//int fd = open("/dev/input/event4", O_RDONLY);
bool PollMouseEvent(MouseEvent &e)
{
	if(fd < 0)
		throw std::runtime_error(std::string("open: ") + strerror(errno));
    struct pollfd query = {fd, POLLIN, 0};
    if(poll(&query, 1, 0) > 0)
    {
        if(read(fd, &e, 3) != 3)
            throw std::runtime_error(std::string("read: ") + strerror(errno));
        return true;
    }
    return false;
}