/*
 * Copyright (c) 2022 XXIV
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __EASYCURL_H__
#define __EASYCURL_H__

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EASY_CURL_STRERROR(NUM) curl_easy_strerror((NUM))

typedef struct {
	int status_code;
	int error_code;
	size_t content_length;
	char* content;
} easy_curl_response;

typedef struct easy_curl easy_curl;
struct easy_curl {
	CURL* _curl;
	easy_curl_response* (*get)(easy_curl*, char*);
};

easy_curl* easy_curl_init();
void easy_curl_clean(easy_curl* self);
void easy_curl_response_clean(easy_curl_response* self);

#ifdef __cplusplus
}
#endif

size_t _write_function(char *data, size_t size, size_t nmemb, void* self) {
	easy_curl_response* ecurl_res = (easy_curl_response*) self;
	char* ecurl_res_content = (char*) malloc((size * nmemb + 1) * sizeof(char));
	if (ecurl_res_content == NULL)
	{
		return 0;
	}
	ecurl_res->content = ecurl_res_content; 
    strncpy(ecurl_res->content, data, (size * nmemb));
    ecurl_res->content_length = size * nmemb;
    return size * nmemb;
}

easy_curl_response* _get(easy_curl* self, char* url)
{
	easy_curl_response* ecurl_res = (easy_curl_response*) malloc(sizeof(easy_curl_response));
	if (ecurl_res == NULL)
	{
		return NULL;
	}
	int stcode;
	curl_easy_setopt(self->_curl, CURLOPT_URL, url);
	curl_easy_setopt(self->_curl, CURLOPT_HTTPGET, 1l);
	curl_easy_setopt(self->_curl, CURLOPT_WRITEFUNCTION, _write_function);
    curl_easy_setopt(self->_curl, CURLOPT_WRITEDATA, (void*) ecurl_res);
	ecurl_res->error_code = curl_easy_perform(self->_curl);
	curl_easy_getinfo(self->_curl, CURLINFO_RESPONSE_CODE, &(ecurl_res->status_code));
	curl_easy_reset(self->_curl);
	return ecurl_res;
}

void easy_curl_clean(easy_curl* self)
{
	if (self != NULL)
	{
		if (self->_curl != NULL)
		{
			curl_easy_cleanup(self->_curl);
		}
		free(self);
	}
}

void easy_curl_response_clean(easy_curl_response* self)
{
	if (self != NULL)
	{
		if (self->content != NULL)
		{
			free(self->content);
		}
		free(self);
	}
}

easy_curl* easy_curl_init()
{
	easy_curl* self = (easy_curl*) malloc(sizeof(easy_curl));
	if (self == NULL)
	{
		return NULL;
	}

	CURL* curl = curl_easy_init();
	if (curl == NULL)
	{
		free(self);
		return NULL;
	}

	self->get = &_get;
	self->_curl = curl;
}


#endif // __EASYCURL_H__