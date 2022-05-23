# easycurl.h

libcurl wrapper to make it more readable and easy to use. It's not like libcurl is hard but, sometimes you wanna get the job done in the fastest way possible.

### Example

```c
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
```

### License

```
Copyright (c) 2022 XXIV

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```