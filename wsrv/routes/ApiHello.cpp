#include "./ApiHello.h"

void routes::ApiHello::handleHello(uWS::HttpResponse<false>* res, uWS::HttpRequest* req)
{
	res->writeStatus("200 OK")
		->writeHeader("Content-Type", "application/json")
		->end("{\"message\": \"Hello, World!\"}");
}