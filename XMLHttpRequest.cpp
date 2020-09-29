#include "XMLHttpRequest.h"
#include "DllInterface.h"
using namespace xmlhttprequest;

//静态变量要在头部定义
CreateManagedXhrDelegate XMLHttpRequest::createManagedXhrDelegate;
SendDelegate XMLHttpRequest::sendDelegate;

XMLHttpRequest * xmlhttprequest::XMLHttpRequest::CreateXMLHttpRequest(XHRCallbacks cb)
{
	return nullptr;
}

xmlhttprequest::XMLHttpRequest::XMLHttpRequest()
{
	XMLHttpRequest::abortCallback = [](XMLHttpRequest *owner, int code, const char* reason)->void
	{
		XMLHttpRequest::Log("abort call back");
		XMLHttpRequest::Log(reason);
		char buffer[20];
		_itoa_s(code, buffer, 10);
		XMLHttpRequest::Log(buffer);
	};
	if (XMLHttpRequest::createManagedXhrDelegate != NULL)
	{
		XMLHttpRequest::createManagedXhrDelegate(this);
	}
}

xmlhttprequest::XMLHttpRequest::XMLHttpRequest(XHRCallbacks cb)
{
}

xmlhttprequest::XMLHttpRequest::~XMLHttpRequest()
{
}

int xmlhttprequest::XMLHttpRequest::Open(RequestMessage requestMsg)
{
	return 0;
}

void xmlhttprequest::XMLHttpRequest::Send(const char * data, int len)
{
	if (XMLHttpRequest::sendDelegate != NULL)
	{
		XMLHttpRequest::sendDelegate(this, data, len);
	}
}

void xmlhttprequest::XMLHttpRequest::GetResponse(const char * res, int len)
{
}

int xmlhttprequest::XMLHttpRequest::GetHttpStatus()
{
	return 0;
}

char * xmlhttprequest::XMLHttpRequest::GetAllResponseHeader()
{
	return nullptr;
}

char * xmlhttprequest::XMLHttpRequest::GetResponseHeader(const char * headerName, int len)
{
	return nullptr;
}

void xmlhttprequest::XMLHttpRequest::Abort()
{
}

void xmlhttprequest::XMLHttpRequest::SetReuqestHeader(const char * headerName, int nameLen, const char * headerValue, int valueLen)
{
}

void xmlhttprequest::XMLHttpRequest::CheckWhiteList(const char * url, int len)
{
}

void xmlhttprequest::XMLHttpRequest::Log(const char * msg)
{
	Debug::Log(msg, strlen(msg));
}

void xmlhttprequest::SetCreateManagedXhrDelegate(CreateManagedXhrDelegate delegate)
{
	XMLHttpRequest::Log("call SetCreateManagedXhrDelegate");
	XMLHttpRequest::createManagedXhrDelegate = delegate;
}

void xmlhttprequest::SetSendDelegate(SendDelegate delegate)
{
	XMLHttpRequest::Log("call SetSendDelegate");
	XMLHttpRequest::sendDelegate = delegate;
}

void xmlhttprequest::AbortCallBackToUnmanaged(XMLHttpRequest * ptr, int code, const char * reason)
{
	if (ptr != nullptr)
	{
		ptr->abortCallback(ptr, code, reason);
	}
}

void xmlhttprequest::CreateXHRTest()
{
	XMLHttpRequest* request = new XMLHttpRequest();
	const char* data = "test send data";
	request->Send(data, strlen(data));
}
