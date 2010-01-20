#include <v8.h>
#include <ev.h>

extern "C" {
#include "sha.h"
#include "md4.h"
#include "md5.h"
}

#include "lib/sha/shamodule.c"
#include "lib/sha/sha256module.c"
#include "lib/sha/sha512module.c"

#include "lib/md6/md6.h"
#include "lib/md6/md6_compress.c"
#include "lib/md6/md6_mode.c"

#include <iostream>
#include <stdio.h>
using namespace v8;

// make digest from php
static void
make_digest_ex(unsigned char *md5str, unsigned char *digest, int len)
{
  static const char hexits[17] = "0123456789abcdef";
  int i;

  for (i = 0; i < len; i++) {
    md5str[i * 2] = hexits[digest[i] >> 4];
    md5str[(i * 2) + 1] = hexits[digest[i] &  0x0F];
  }
  md5str[len * 2] = '\0';
}

Handle<Value>
sha(const Arguments& args)
{
  HandleScope scope;	
  String::Utf8Value data(args[0]->ToString());
  SHA_CTX ctx;
  unsigned char digest[20];
  unsigned char hexdigest[40];

  SHA_Init(&ctx);
  SHA_Update(&ctx, (unsigned char*)*data, data.length());
  SHA_Final(digest, &ctx);

  make_digest_ex(hexdigest, digest, 20);
	     
  return String::New((char*)hexdigest,40);
}

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

  make_digest_ex(hexdigest, digest, 20);
	     
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

  make_digest_ex(hexdigest, digest, 32);
	     
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
  
  make_digest_ex(hexdigest, digest, 64);
	     
  return String::New((char*)hexdigest,128);
}

Handle<Value>
md4(const Arguments& args)
{
  HandleScope scope;
  
  String::Utf8Value data(args[0]->ToString());
  MD4_CTX mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];

  /* make an hash */
  MD4Init(&mdContext);
  MD4Update(&mdContext, (unsigned char*)*data, data.length());
  MD4Final(digest, &mdContext);
  
  make_digest_ex(hexdigest, digest, 16);
  
  return String::New((char*)hexdigest,32);
}

Handle<Value>
md5(const Arguments& args)
{
  HandleScope scope;
  
  String::Utf8Value data(args[0]->ToString());
  MD5_CTX mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];

  /* make an hash */
  MD5Init(&mdContext);
  MD5Update(&mdContext, (unsigned char*)*data, data.length());
  MD5Final(digest, &mdContext);
  
  make_digest_ex(hexdigest, digest, 16);
  
  return String::New((char*)hexdigest,32);
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

  int half_len=len/2;
  if (len%2!=0) half_len++;
  
  make_digest_ex(hexdigest, digest, half_len);
	     
  return String::New((char*)hexdigest,len);
}

Handle<Value> get_md5_file(char * path)
{
  FILE *inFile = fopen (path, "rb");
  MD5_CTX mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];
  int bytes;
  unsigned char data[1024];

  if (inFile == NULL) {
    std::string s="Cannot read ";
    s+=path;
    return ThrowException(Exception::Error(String::New(s.c_str())));
  }

  MD5Init (&mdContext);
  while ((bytes = fread (data, 1, 1024, inFile)) != 0)
    MD5Update (&mdContext, data, bytes);
  MD5Final (digest, &mdContext);
  make_digest_ex(hexdigest, digest, 16);
  fclose (inFile);
  return String::New((char*)hexdigest,32);
}

void md5_file_callback(int revents, void *args) {
  Persistent<Object> *data =
    reinterpret_cast<Persistent<Object>*>(args);
  
  String::Utf8Value path((*data)->Get(String::New("path")));
  v8::Handle<v8::Function> callback = v8::Handle<v8::Function>::Cast((*data)->Get(String::New("callback")));
  Handle<Object> recv = Handle<Object>::Cast((*data)->Get(String::New("recv")));
  v8::Handle<v8::Value> outArgs[] = {get_md5_file(*path)};
  callback->Call(recv, 1, outArgs);
  data->Dispose();
}

Handle<Value>
md5_file(const Arguments& args)
{
  HandleScope scope;
  
  String::Utf8Value path(args[0]->ToString());
  if (args[1]->IsFunction()) {
	v8::Local<v8::Object> arguments = v8::Object::New();
	arguments->Set(String::New("path"),args[0]->ToString());
	arguments->Set(String::New("callback"),args[1]);
	arguments->Set(String::New("recv"),args.This());
	Persistent<Object> *data = new Persistent<Object>();
    *data = Persistent<Object>::New(arguments);
    
    ev_once(0, EV_TIMEOUT, 0, md5_file_callback, (void*)data);
    
  	return v8::Boolean::New(true);
  } else {
  	return get_md5_file(*path);
  }
}

extern "C" void init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("md4"), FunctionTemplate::New(md4)->GetFunction());
  target->Set(String::New("md5"), FunctionTemplate::New(md5)->GetFunction());
  target->Set(String::New("md6"), FunctionTemplate::New(md6)->GetFunction());
  target->Set(String::New("sha"), FunctionTemplate::New(sha)->GetFunction());
  target->Set(String::New("sha1"), FunctionTemplate::New(sha1)->GetFunction());
  target->Set(String::New("sha256"), FunctionTemplate::New(sha256)->GetFunction());
  target->Set(String::New("sha512"), FunctionTemplate::New(sha512)->GetFunction());
  
  target->Set(String::New("md5_file"), FunctionTemplate::New(md5_file)->GetFunction());
}
