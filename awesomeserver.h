#pragma once

class AwesomeServer
{
public:
    AwesomeServer(int port);

    bool listen();

protected:
    int port;
};
