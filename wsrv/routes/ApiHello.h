#pragma once

/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
#include <App.h> // this is the file 'uWebSockets/src/App.h' 

namespace routes
{
	class ApiHello
	{
	public:
		static void handleHello(uWS::HttpResponse<false>* res, uWS::HttpRequest* req);
	};
}
