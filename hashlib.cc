#include <v8.h>
//#include "lib/md5/md5.cpp"
//#include "lib/md5/arc4.h"
#include "lib/md5/md5.c"

#include <iostream>
#include <string>
using namespace v8;


Handle<Value>
md5(const Arguments& args)
{
  HandleScope scope;	
  
  String::Utf8Value data(args[0]->ToString());

  md5_state_t mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];
  int i, j;

  /* make an hash */
  md5_init(&mdContext);
  md5_append(&mdContext,(unsigned char*) *data,data.length());
  md5_finish(&mdContext, digest);

  /* Make hex version of the digest */
  for(i=j=0; i<16; i++) {
    char c;
    c = (digest[i] >> 4) & 0xf;
    c = (c>9) ? c+'a'-10 : c + '0';
    hexdigest[j++] = c;
    c = (digest[i] & 0xf);
    c = (c>9) ? c+'a'-10 : c + '0';
    hexdigest[j++] = c;
  }
  
  return String::New((char*)hexdigest,32);
}


extern "C" void init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("md5"), FunctionTemplate::New(md5)->GetFunction());
}
