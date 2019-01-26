/* 
 * File:   HttpClient.hpp
 * Author: ubuntu
 *
 * Created on January 24, 2019, 10:46 PM
 */

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include <string>

class HttpClient 
{
    public:
        HttpClient(const std::string &domainNameOrIP,
                   unsigned short int port,
                   const std::string &username,
                   const std::string &password);
        
    private:
        const std::string m_domainNameOrIP;
        const unsigned short int m_port;
        const std::string m_username;
        const std::string m_password;
};



#endif /* HTTPCLIENT_HPP */

