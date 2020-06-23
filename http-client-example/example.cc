#include <cpprest/http_client.h>
#include "pplx/pplxtasks.h"
#include <list>
#include <memory>

using namespace std;
int main(int argc, char *argv[]) {

    web::http::client::http_client_config config;
    config.set_validate_certificates(false);
    string demoUri = "https://www.api-football.com/demo/v2";
    web::http::client::http_client client(demoUri,config);
    unsigned short englishPremierLeagueId=524;
    
    //typically one would need to add an api key to all requests, below is one way to do so. However in our case
    // neither key presence nor key validity is checked in football-api's demo environment, so intercepting the request
    //to add the api key header is for demonstration purposes only..
    auto request_interceptor =
            [](web::http::http_request request, std::shared_ptr<web::http::http_pipeline_stage> next_stage) -> pplx::task<web::http::http_response>
            {       request.headers().add("X-RapidAPI-Key","fake-key-not-checked-in-demo-environemt");
                    return next_stage->propagate(request);
            };
    client.add_handler(request_interceptor);

    web::http::uri_builder builder(U("fixtures/league/"+ std::to_string(englishPremierLeagueId)));

    auto request = client.request(web::http::methods::GET, builder.to_string()).then([](web::http::http_response response) {
        if(web::http::status_codes::OK==response.status_code()) {
            return response.extract_json();
        }
        throw std::runtime_error("received a non-200 status code: "+std::to_string(response.status_code()));
    }).then([](web::json::value body){
        std::cout << body << std::endl;
        std::cout << body["api"]["fixtures"][0]["homeTeam"]["team_name"] <<std::endl;
    });

    try{
        request.wait();
    }catch (const std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
}
