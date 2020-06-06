/*
 * File:   HttpClient.hpp
 * Author: ubuntu
 *
 * Created on January 24, 2019, 10:46 PM
 */

#ifndef HTTPCLIENT_HPP
#define HTTPCLIENT_HPP

#include "Device.hpp"
#include "curl/curl.h"
#include "jsoncpp/json/json.h"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class HttpClient {
public:
    HttpClient(
            const std::string& hostName,
            const std::string& port,
            const std::string& username,
            const std::string& password);

    enum CallType { GET_DEVICES, REFRESH_STATE };

    void queryAPI(const std::string& deviceType, CallType callType);
    void printDevices() const;
    std::vector<std::shared_ptr<Device>> getGetvices();
    void setTimeout(unsigned long timeout);
    void setRunningUnitTest(bool runningUnitTest);

private:
    const std::string m_hostName;
    const std::string m_port;
    const std::string m_username;
    const std::string m_password;
    unsigned long m_timeout;
    bool m_runningUnitTest;
    std::vector<std::shared_ptr<Device>> m_devices;

    std::string m_refreshStateLast;

    // separate buffer for queryAPI of type "GET_DEVICES"
    std::string m_buffer4GetDevices;
    static size_t writerCallback4DevicesQuery(char* data, size_t size, size_t nmemb, void* p);
    size_t writerCallback4DevicesQuery_impl(char* data, size_t size, size_t nmemb);

    // separate buffer for queryAPI of type "REFRESH_STATE"
    std::string m_buffer4RefreshStates;
    static size_t writerCallback4RefreshQuery(char* data, size_t size, size_t nmemb, void* p);
    size_t writerCallback4RefreshQuery_impl(char* data, size_t size, size_t nmemb);

    void addDevices(const std::string& deviceType);
    void addTemperatureSensors(const Json::Value& root);
    void handleRefreshState(const std::string& deviceType);
    void refreshTemperatureSensors(const Json::Value& root);
    void handleCurlError(char* errbuf, CURLcode& res);

    friend class HttpClientTest;
};

#endif /* HTTPCLIENT_HPP */
