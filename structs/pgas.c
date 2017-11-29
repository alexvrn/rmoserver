#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "common.h"

#define TEST_HOST_PU	"localhost"
#define TEST_PORT_PU	"2777"

extern unsigned char stream_data[STREAM_DATA_SIZE];

int
pgas_client(void) {
	CURL *curl;
	CURLcode res;

	static const char *postthis = "test msg";

	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL,
			"http://" TEST_HOST_PU ":" TEST_PORT_PU);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(postthis));
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
			curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}

	return res;
}

int
pgas_url_request_handler(void* arg, void* conn,
		const char* url, const char* method, const char* version,
		const char* request_data, size_t request_data_size) {
	int ret = -1;
	int i = 0;
	unsigned int status = 200;

	printf("### ### ### ### ###\n");

	printf("HTTPD: %6s %s %lu %s\n",
		method, version, request_data_size, url);

	if(url_response_handler) {
		// show default test page on "GET /" request 
		if(strcmp("/", url) == 0 && strcmp("GET", method) == 0) {
			ret = url_response_handler(
				conn, (char*)arg, strlen((char*)arg), status);
			goto exit;
		}
		for(i=0; i<PGAS_CMD_MAX; i++) {
			//printf("%d: %s %s\n", i, pgas_cmd[i].appointment, pgas_cmd[i].http_url);
			if(	strcmp(pgas_cmd[i].http_url, url) == 0 &&
				strcmp(pgas_cmd[i].http_method, method) == 0
				) {
				printf("CMD: %s\n", pgas_cmd[i].appointment);
				if(i == 0) {
					printf("PGAS SHUTDOWN...\n");
					exit(0);
				}
				//request stream
				stream_in.data = (unsigned char*)(request_data);
				stream_in.size = request_data_size;
				stream_in.pos = 0;
				//response stream
				stream_out.pos = 0;
				pgas_cmd[i].handler(url, &stream_in, &stream_out);
				printf("REQUEST DATA : %p %lu byte\n",
					stream_in.data, stream_in.size);
				printf("RESPONSE DATA: %p %lu byte\n",
					stream_out.data, stream_out.pos);
				print_hex_word(stream_out.data, stream_out.pos);
				ret = url_response_handler(conn,
					(char*)stream_out.data, stream_out.pos,
					status);
				break;
			}
		}
		if(i == PGAS_CMD_MAX) {
			printf("CMD: NOT FOUND\n");
			ret = url_response_handler(conn,
				(char*)stream_out.data, 0,
				404);
		}
	}

exit:
	return ret;
}

