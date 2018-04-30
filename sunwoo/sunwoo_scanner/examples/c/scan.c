/*
Group: Security119
University: Chonname University
Name: sunwoo Lee

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <getopt.h>
#include <signal.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>


#include <jansson.h>


#include "VtFile.h"
#include "VtResponse.h"

static bool keep_running = true;

void print_usage(const char *prog_name) {
  printf("%s < --apikey YOUR_API_KEY >   [ --filescan FILE1 ] [ --filescan FILE2 ]\n", prog_name);
  printf("  --apikey <API_KEY>         Your virus total API key. This arg 1st\n");
  printf("  --filescan <FILE>          File to scan, may specify this multiple times\n");
  printf("  --report <SHA/MD5>          Get a Report on a resource\n");
}


// Example data structure that can be passed to callback function
struct CallbackData {
  int counter;
};



void sighand_callback(int sig)
{
  printf("signal caught %d\n", sig);
  keep_running = false;
}


void progress_callback(struct VtFile *file, void *data)
{
  int64_t dltotal = 0;
  int64_t dlnow = 0;
  int64_t ul_total = 0;
  int64_t ul_now = 0;
  VtFile_getProgress(file, &dltotal, &dlnow, &ul_total, &ul_now);

  printf("progress_callback %lld/%lld\n", (long long) ul_now, (long long) ul_total);
  if (!keep_running)
    VtFile_cancelOperation(file);
}

#define RESP_BUF_SIZE 255

int scan_file(struct VtFile *scan, const char *path)
{
  int ret;
  struct stat stat_buf;

  ret = stat(path, &stat_buf);

  if (ret)
    return ret;

  if (stat_buf.st_size < (64*1024*1024) ) {
    ret = VtFile_scan(scan, path, NULL);
  } else {
    ret = VtFile_scanBigFile(scan, path);
    printf(" VtFile_scanBigFile ret =%d \n", ret);
  }


  return ret;
}


//start main
int main(int argc, char * const *argv) {
  int c;
  int ret = 0;
  struct VtFile *file_scan;
  struct VtResponse *response;
  
  char *str = NULL;
  char *api_key = NULL;
  char *out = NULL;
  
  int response_code;
  //struct CallbackData cb_data = { .counter = 0 };
  char buf[RESP_BUF_SIZE+1] = { 0, };

 	 if (argc < 2) {
              print_usage(argv[0]);
       	  return 0;
 	 }
 
	 signal(SIGHUP, sighand_callback);
 	 signal(SIGTERM, sighand_callback);

	  file_scan = VtFile_new();
 	 VtFile_setProgressCallback(file_scan, progress_callback, NULL);

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"filescan",  required_argument,    0,  'f' },
      {"report",  required_argument,    0,  'i' },
      {"apikey",  required_argument,     0,  'a'},
      //{"out",  required_argument,     0,  'o'},
      {0,         0,                 0,  0 }
    };

    c = getopt_long_only(argc, argv, "",
                         long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
    case 'a':
      api_key = strdup(optarg);
      printf(" apikey: %s \n", optarg);
      VtFile_setApiKey(file_scan, optarg);
      break;

    case 'f':
       if(!api_key){
        printf("Must set --apikey first\n");
        exit(1);
      }

      ret = scan_file(file_scan, optarg);
      // PRINT("Filescan ret=%d\n", ret);
      if (ret) {
        printf("Error: %d \n", ret);
      } else {
        response = VtFile_getResponse(file_scan);
        str = VtResponse_toJSONstr(response, VT_JSON_FLAG_INDENT);
        if (str) {
          printf("Response:\n%s\n", str);
          free(str);
        }
        VtResponse_put(&response);
      }
      break;
    case 'i':
      if (!api_key) {
        printf("Must set --apikey first\n");
        exit(1);
      }
      ret = VtFile_report(file_scan, optarg);
     // PRINT("rescan ret=%d\n", ret);
      if (ret) {
        printf("Error: %d \n", ret);
      } else {
        response = VtFile_getResponse(file_scan);
        str = VtResponse_toJSONstr(response, VT_JSON_FLAG_INDENT);
        if (str) {
          printf("Response:\n%s\n", str);
          free(str);
        }

        VtResponse_getVerboseMsg(response, buf, RESP_BUF_SIZE);
        printf("Msg: %s\n", buf);

        ret = VtResponse_getResponseCode(response, &response_code);
        if (!ret) {
          printf("response code: %d\n", response_code);
        }


        VtResponse_put(&response);
      }
      break;
     default:
	 printf("?? getopt returned character code 0%o ??\n", c);
    }
  } // end while

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    printf("\n");
  }
//c//leanup:
  //PRINT("Cleanup\n");
  VtFile_put(&file_scan);

  if (api_key)
    free(api_key);

  if (out)
    free(out);

  return 0;
}
