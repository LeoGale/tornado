#include <sys/epoll.h>//epoll
#include <unistd.h>//close
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include <assert.h>

void report()
{
	printf("Erm..............\n");
}

struct EventHandler
{
	typedef void(*EvCb)();
	int fd;
	int events;
	EvCb cb;

};

void update(int epfd, int opt, void* handler)
{
	EventHandler* evHandler = static_cast<EventHandler*>(handler);	
	int fd = evHandler->fd;
	struct epoll_event event;
	bzero(&event, sizeof event);
	event.events = evHandler->events;
	event.data.ptr = evHandler;
	
	assert(fd > 0);

	if(epoll_ctl(epfd, opt, fd, &event) < 0)
	{
		int  aErrorCode = errno;
                printf("Erorr epoll_ctl, %s\n", strerror(aErrorCode));
	}
}


void evloop(int epfd, std::vector<struct epoll_event> & events)
{
	int numFds = epoll_wait(epfd, &*events.begin(), events.size(), 1000);

	if(numFds < 0)
	{
		return;
	}

}

int main()
{
	int epollfd = epoll_create1(EPOLL_CLOEXEC);
	if(epollfd < 0)
	{
		int  aErrorCode = errno;
		printf("Erorr epoll_create1, %s\n", strerror(aErrorCode));
		return 0;
	}

	EventHandler evHandler;
	evHandler.fd = 1;
	evHandler.events = EPOLLIN | EPOLLOUT;
	evHandler.cb = report;

	update(epollfd, EPOLL_CTL_ADD, &evHandler);

	std::vector<struct epoll_event> evlist;
	evlist.resize(100);

	evloop(epfd, evlist);

	for(int i = 0 ; i < numFds; i++)
	{
		EventHandler* evHandle = static_cast<EventHandler*>(events[i].data.ptr);
		int reevents = events[i].events;
	}

	if(close(epollfd) < 0)
	{
		int  aErrorCode = errno;
		printf("Erorr closing file, %s\n", strerror(aErrorCode));
	}


	return epollfd;


}
