//
// Created by glosimarsun on 2020/9/28.
//
#ifndef PIXUI_IXMLHTTPREQUEST_H
#define PIXUI_IXMLHTTPREQUEST_H
#define XML_HTTP_REQUEST_EXPORT_API extern "C" __declspec(dllexport)
namespace xmlhttprequest
{

	class XMLHttpRequest;
	typedef void(*AbortCallBack)(XMLHttpRequest *owner, int code, const char* reason);  //
	typedef void(*ErrorCallBack)(XMLHttpRequest *owner, int code, const char* reason);
	typedef void(*LoadStartCallBack)(XMLHttpRequest *owner);
	typedef void(*LoadCallBack)(XMLHttpRequest *owner);
	typedef void(*LoadEndCallBack)(XMLHttpRequest *owner);
	typedef void(*ProgressCallBack)(XMLHttpRequest *owner, int total, int patial);
	typedef void(*TimeoutCallBack)(XMLHttpRequest *owner);
	typedef void(*ReadyStateChangeCallBack)(XMLHttpRequest *owner, const char * ErrorMess);

	//创建托管层对象委托
	typedef void(*CreateManagedXhrDelegate)(XMLHttpRequest* ptr);
	typedef void(*SendDelegate)(XMLHttpRequest* ptr, const char * data, int len);

	struct XHRCallbacks
	{
		AbortCallBack acb;
		ErrorCallBack ecb;
		LoadStartCallBack lscb;
		LoadCallBack lcb;
		LoadEndCallBack lecb;
		TimeoutCallBack tocb;
		ReadyStateChangeCallBack rscb;
		ProgressCallBack pcb;
	};

	struct RequestMessage
	{
		const char * method;
		const char * password;
		const char * user;
		const char * url;

		bool async;

		int methodLen;
		int urlLen;
		int userLen;
		int passwordLen;
	};
	class XMLHttpRequest
	{
	public:

		static XMLHttpRequest* CreateXMLHttpRequest(XHRCallbacks cb);
		XMLHttpRequest();
		XMLHttpRequest(XHRCallbacks cb);
		virtual~XMLHttpRequest();

		// Param async, user, password are optional
		virtual int Open(RequestMessage requestMsg);

		virtual void Send(const char * data, int len);
		virtual void GetResponse(const char * res, int len);
		virtual int GetHttpStatus();
		virtual char * GetAllResponseHeader();
		virtual char * GetResponseHeader(const char * headerName, int len);
		virtual void Abort();
		virtual void SetReuqestHeader(const char * headerName, int nameLen,
			const char * headerValue, int valueLen);
		virtual void CheckWhiteList(const char * url, int len);

		void * pri_data;  //user private data , originally return from all callback to identify this object

		//callback
		AbortCallBack abortCallback;

		//C#层设置的委托
		static  CreateManagedXhrDelegate createManagedXhrDelegate;
		static  SendDelegate sendDelegate;
		static void Log(const char* msg);
	};

	//导出接口
	XML_HTTP_REQUEST_EXPORT_API void SetCreateManagedXhrDelegate(CreateManagedXhrDelegate delegate);
	XML_HTTP_REQUEST_EXPORT_API void SetSendDelegate(SendDelegate delegate);
	XML_HTTP_REQUEST_EXPORT_API void AbortCallBackToUnmanaged(XMLHttpRequest* ptr, int code, const char* reason);


	//由C#层触发调用C++层构造函数进行测试
	XML_HTTP_REQUEST_EXPORT_API void CreateXHRTest();


} // namespace xmlhttprequest

#endif //PIXUI_IXMLHTTPREQUEST_H
