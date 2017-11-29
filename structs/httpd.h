#ifndef HTTPD_H
#define HTTPD_H

typedef int (*URL_REQUEST_HANDLER)(
	void* arg,
	void* connection,
	const char* url,
	const char* method,
	const char* version,
	const char* request_data,
	size_t request_data_size);

typedef int (*URL_RESPONSE_HANDLER)(
	void * connection,
	char * resp,
	size_t resp_len,
	unsigned int status);

httpd*	httpd_start(int port,
			URL_REQUEST_HANDLER request_handler,
			URL_RESPONSE_HANDLER* response_handler,
			void* arg);
int	httpd_stop	(httpd* daemon);

#endif
