#include <v8.h>

#include "lib/md5/md5.c"

#include "lib/sha/shamodule.c"
#include "lib/sha/sha256module.c"
#include "lib/sha/sha512module.c"

#include "lib/md6/md6.h"
#include "lib/md6/md6_compress.c"
#include "lib/md6/md6_mode.c"

//

#include <iostream>
using namespace v8;

Handle<Value>
sha1(const Arguments& args)
{
  HandleScope scope;	
  using namespace sha1module;
  String::Utf8Value data(args[0]->ToString());
  unsigned char digest[40];
  unsigned char hexdigest[40];
  SHAobject *sha;
  sha=new SHAobject;
  sha_init(sha);
  sha_update(sha, (unsigned char*) *data, data.length());
  sha_final(digest, sha);
  char chr;
  int i, j;
  for(i=j=0; i<20; i++) {
    chr = (digest[i] >> 4) & 0xf;
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
    chr = (digest[i] & 0xf);
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
  }
	     
  return String::New((char*)hexdigest,40);
}


Handle<Value>
sha256(const Arguments& args)
{
  HandleScope scope;	
  using namespace sha256module;
  String::Utf8Value data(args[0]->ToString());
  unsigned char digest[64];
  unsigned char hexdigest[64];
  SHAobject *sha;
  sha=new SHAobject;
  sha_init(sha);
  sha_update(sha, (unsigned char*) *data, data.length());
  sha_final(digest, sha);
  char chr;
  int i, j;
  for(i=j=0; i<32; i++) {
    chr = (digest[i] >> 4) & 0xf;
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
    chr = (digest[i] & 0xf);
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
  }
	     
  return String::New((char*)hexdigest,64);
}

Handle<Value>
sha512(const Arguments& args)
{
  HandleScope scope;	
  using namespace sha512module;
  String::Utf8Value data(args[0]->ToString());
  unsigned char digest[128];
  unsigned char hexdigest[128];
  SHAobject *sha;
  sha=new SHAobject;
  sha512_init(sha);
  sha512_update(sha, (unsigned char*) *data, data.length());
  sha512_final(digest, sha);
  char chr;
  int i, j;
  for(i=j=0; i<64; i++) {
    chr = (digest[i] >> 4) & 0xf;
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
    chr = (digest[i] & 0xf);
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
  }
	     
  return String::New((char*)hexdigest,128);
}


Handle<Value>
md6(const Arguments& args)
{
  HandleScope scope;	
  
  String::Utf8Value data(args[0]->ToString());
  
  int len(32);
  if (!args[1]->IsUndefined()) {
    len=args[1]->ToInteger()->Value();
  }
  unsigned char digest[len];
  unsigned char hexdigest[len];
  md6_hash(len*8, (unsigned char*) *data, data.length(), digest);
  char chr;
  int i, j;
  int half_len=len/2;
  if (len%2!=0) half_len++;
  
  for(i=j=0; i<half_len; i++) {
    chr = (digest[i] >> 4) & 0xf;
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
    chr = (digest[i] & 0xf);
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
  }
	     
  return String::New((char*)hexdigest,len);
}


Handle<Value>
md5(const Arguments& args)
{
  HandleScope scope;
  
  String::Utf8Value data(args[0]->ToString());
  md5_state_t mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];

  /* make an hash */
  md5_init(&mdContext);
  md5_append(&mdContext,(unsigned char*)*data,data.length());
  md5_finish(&mdContext, digest);
  
  int i, j;
  for(i=j=0; i<16; i++) {
  	char chr;
    chr = (digest[i] >> 4) & 0xf;
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
    chr = (digest[i] & 0xf);
    chr = (chr>9) ? chr+'a'-10 : chr + '0';
    hexdigest[j++] = chr;
  }
  
  return String::New((char*)hexdigest,32);
}

extern "C" void init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("md5"), FunctionTemplate::New(md5)->GetFunction());
  target->Set(String::New("md6"), FunctionTemplate::New(md6)->GetFunction());
  target->Set(String::New("sha"), FunctionTemplate::New(sha1)->GetFunction());
  target->Set(String::New("sha1"), FunctionTemplate::New(sha1)->GetFunction());
  target->Set(String::New("sha256"), FunctionTemplate::New(sha256)->GetFunction());
  target->Set(String::New("sha512"), FunctionTemplate::New(sha512)->GetFunction());
}
