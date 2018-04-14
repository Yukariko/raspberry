#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <iostream>
#include <sstream>

using namespace web;
using namespace web::http;
using namespace web::http::client;

pplx::task<void> HTTPStreamingAsync()
{
    http_client client(U("http://yukariko.ga/log"));
    
    json::value post;
    post[U("signal_id")] = json::value::number(1);
    post[U("value")] = json::value::string(U("on"));

    return client.request(methods::POST, U(""), post).then([](http_response response)
    {
        response.extract_string(true).then([](std::string body) {
                std::cout << body << std::endl;
        }).wait();
    });
}

int main()
{
    HTTPStreamingAsync().wait();

    return 0;
}
