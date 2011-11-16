/**
 * FAST nodejs(http://github.com/ry/node/) library for making hashes
 *
 * @package hashlib
 * @link http://github.com/brainfucker/hashlib
 * @autor Oleg Illarionov <oleg@emby.ru>
 * @version 1.0
 */

#include <iostream>

#include <v8.h>
#include <fcntl.h>
#include <node_buffer.h>

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

class file_data {
  public:
	int fd;
	int byte;
	MD5_CTX mdContext;
	void* environment;
};


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

// extracts the data from POSition of arguments. Respects Buffers
#define get_data(POS, DATA, LENGTH) \
  String::Utf8Value mdata_##POS (args[POS]->ToString()); \
  Local<Object> buffer_obj_##POS; \
  if (node::Buffer::HasInstance(args[POS])) { \
    Local<Object> buffer_obj_##POS = args[POS]->ToObject(); \
    LENGTH = node::Buffer::Length(buffer_obj_##POS); \
    DATA = (unsigned char *)node::Buffer::Data(buffer_obj_##POS); \
  } else { \
    LENGTH = (size_t)mdata_##POS.length(); \
    DATA = (unsigned char *)*mdata_##POS; \
  }



Handle<Value>
sha(const Arguments& args)
{
  HandleScope scope;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  SHA_CTX ctx;
  unsigned char digest[20];
  unsigned char hexdigest[40];

  SHA_Init(&ctx);
  SHA_Update(&ctx, data, length);
  SHA_Final(digest, &ctx);

  make_digest_ex(hexdigest, digest, 20);

  return scope.Close(String::New((char*)hexdigest,40));
}

Handle<Value>
sha1(const Arguments& args)
{
  HandleScope scope;
  using namespace sha1module;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  unsigned char digest[40];
  unsigned char hexdigest[40];
  SHAobject *sha;
  sha=new SHAobject;
  sha_init(sha);
  sha_update(sha, data, length);
  sha_final(digest, sha);

  make_digest_ex(hexdigest, digest, 20);

  return scope.Close(String::New((char*)hexdigest,40));
}

Handle<Value>
hmac_sha1(const Arguments& args)
{
	HandleScope scope;
 	using namespace sha1module;

	unsigned char *data, *key_input;
	size_t data_length, keylen;
	get_data(0, data, data_length);
	get_data(1, key_input, keylen);

	unsigned char digest[40];
	unsigned char hexdigest[40];
	unsigned int i;

	const void *key = key_input;

	char ipad[64], opad[64];

	if(keylen > 64)
	{
		char optkeybuf[20];
		SHAobject *keyhash;
		keyhash = new SHAobject;
		sha_init(keyhash);
		sha_update(keyhash, key_input, keylen);
		sha_final((unsigned char*) optkeybuf, keyhash);
		keylen = 20;
		key = optkeybuf;
	}

	memcpy(ipad, key, keylen);
	memcpy(opad, key, keylen);
	memset(ipad+keylen, 0, 64 - keylen);
	memset(opad+keylen, 0, 64 - keylen);

	for (i = 0; i < 64; i++)
	{
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	SHAobject *context;
	context = new SHAobject;
	sha_init(context);
	sha_update(context, (unsigned char*) ipad, 64);
	sha_update(context, data, data_length);
	sha_final(digest, context);

	sha_init(context);
	sha_update(context, (unsigned char*) opad, 64);
	sha_update(context, digest, 20);
	sha_final(digest, context);

	make_digest_ex(hexdigest, digest, 20);
	return scope.Close(String::New((char*)hexdigest,40));
}

Handle<Value>
hmac_md5(const Arguments& args)
{
	HandleScope scope;
	unsigned char *data, *key_input;
	size_t data_length, keylen;
	get_data(0, data, data_length);
	get_data(1, key_input, keylen);

	unsigned char digest[16];
	unsigned char hexdigest[32];
	unsigned int i;
	const void *key = (unsigned char*) key_input;

	char ipad[64], opad[64];

	if (keylen > 64)
	{
		char optkeybuf[20];
		MD5_CTX keyhash;

		MD5Init(&keyhash);
		MD5Update(&keyhash, (unsigned char*) key, keylen);
		MD5Final((unsigned char*) optkeybuf, &keyhash);

		keylen = 20;
		key = optkeybuf;
	}

	memcpy(ipad, key, keylen);
	memcpy(opad, key, keylen);
	memset(ipad+keylen, 0, 64 - keylen);
	memset(opad+keylen, 0, 64 - keylen);

	for (i = 0; i < 64; i++)
	{
		ipad[i] ^= 0x36;
		opad[i] ^= 0x5c;
	}

	MD5_CTX context;

	MD5Init(&context);
	MD5Update(&context, (unsigned char*) ipad, 64);
	MD5Update(&context, data, data_length);
	MD5Final(digest, &context);

	MD5Init(&context);
	MD5Update(&context, (unsigned char*) opad, 64);
	MD5Update(&context, digest, 16);
	MD5Final(digest, &context);

	make_digest_ex(hexdigest, digest, 16);
	return scope.Close(String::New((char*)hexdigest,32));
}



Handle<Value>
sha256(const Arguments& args)
{
  HandleScope scope;
  using namespace sha256module;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  unsigned char digest[64];
  unsigned char hexdigest[64];
  SHAobject *sha;
  sha=new SHAobject;
  sha_init(sha);
  sha_update(sha, data, length);
  sha_final(digest, sha);

  make_digest_ex(hexdigest, digest, 32);

  return scope.Close(String::New((char*)hexdigest,64));
}

Handle<Value>
sha512(const Arguments& args)
{
  HandleScope scope;
  using namespace sha512module;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  unsigned char digest[128];
  unsigned char hexdigest[128];
  SHAobject *sha;
  sha  = new SHAobject;
  sha512_init(sha);
  sha512_update(sha, data, length);
  sha512_final(digest, sha);

  make_digest_ex(hexdigest, digest, 64);

  return scope.Close(String::New((char*)hexdigest,128));
}

Handle<Value>
md4(const Arguments& args)
{
  HandleScope scope;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  MD4_CTX mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];

  /* make an hash */
  MD4Init(&mdContext);
  MD4Update(&mdContext, data, length);
  MD4Final(digest, &mdContext);

  make_digest_ex(hexdigest, digest, 16);

  return scope.Close(String::New((char*)hexdigest,32));
}

Handle<Value>
md5(const Arguments& args)
{
  HandleScope scope;
  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  MD5_CTX mdContext;
  unsigned char digest[16];
  unsigned char hexdigest[32];

  /* make an hash */
  MD5Init(&mdContext);
  MD5Update(&mdContext, data, length);
  MD5Final(digest, &mdContext);

  make_digest_ex(hexdigest, digest, 16);

  return scope.Close(String::New((char*)hexdigest,32));
}

Handle<Value>
md6(const Arguments& args)
{
  HandleScope scope;

  size_t length;
  unsigned char *data;
  get_data(0, data, length);

  int len(32);
  if (!args[1]->IsUndefined()) {
    len=args[1]->ToInteger()->Value();
  }
  unsigned char digest[len];
  unsigned char hexdigest[len];
  md6_hash(len*8, data, length, digest);

  int half_len=len/2;
  if (len%2!=0) half_len++;

  make_digest_ex(hexdigest, digest, half_len);

  return scope.Close(String::New((char*)hexdigest,len));
}

extern "C" void init (Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::New("md4"), FunctionTemplate::New(md4)->GetFunction());
  target->Set(String::New("md5"), FunctionTemplate::New(md5)->GetFunction());
  target->Set(String::New("md6"), FunctionTemplate::New(md6)->GetFunction());
  target->Set(String::New("sha"), FunctionTemplate::New(sha)->GetFunction());
  target->Set(String::New("sha1"), FunctionTemplate::New(sha1)->GetFunction());
  target->Set(String::New("hmac_sha1"), FunctionTemplate::New(hmac_sha1)->GetFunction());
  target->Set(String::New("hmac_md5"), FunctionTemplate::New(hmac_md5)->GetFunction());
  target->Set(String::New("sha256"), FunctionTemplate::New(sha256)->GetFunction());
  target->Set(String::New("sha512"), FunctionTemplate::New(sha512)->GetFunction());
}
