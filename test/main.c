#include <stdio.h>
#include "easycurl.h"
 
int main(void)
{
  easy_curl* http;
  easy_curl_response* res;
  
  http = easy_curl_init();
  if (!http)
  {
    fprintf(stderr, "can't initialize easy_curl\n");
    return -1;
  }
  res = http->get(http, "http://example.com/");
  if (!res)
  {
    easy_curl_clean(http);
    fprintf(stderr, "can't initialize easy_curl_response\n");
    return -1;
  }
  if (res->error_code != 0)
  {
    fprintf(stderr, "%s\n", EASY_CURL_STRERROR(res->error_code));
    return -1;
  }
  printf("Content: %s\n", res->content);
  printf("Length: %d\n", res->content_length);
  printf("Status Code: %d\n", res->status_code);
  easy_curl_response_clean(res);
  easy_curl_clean(http);
  return 0;
}