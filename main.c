#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "md5.h"
#include "md5_digest.h"

//rtsp://admin:hik12345@192.168.6.241

//RTSP/1.0 401 Unauthorized
//CSeq: 3
//WWW-Authenticate: Digest realm="IP Camera(D1486)", nonce="25a94a716ee6d7e74d6edda0e6f15dd6", stale="FALSE"
//Date:  Wed, Dec 01 2021 23:32:53 GMT
//
//DESCRIBE rtsp://192.168.6.241:554 RTSP/1.0
//CSeq: 4
//Authorization: Digest username="admin", realm="IP Camera(D1486)", nonce="25a94a716ee6d7e74d6edda0e6f15dd6", uri="rtsp://192.168.6.241:554", response="8f6cfcbc6264024772272d700b381f92"
//User-Agent: LibVLC/3.0.16 (LIVE555 Streaming Media v2016.11.28)
//Accept: application/sdp

//extern void MD5_Init(MD5_CTX *ctx);
//extern void MD5_Update(MD5_CTX *ctx, const void *data, unsigned long size);
//extern void MD5_Final(unsigned char *result, MD5_CTX *ctx);
int main()
{
	char* pRet = md5_digest_get_response("admin", "hik12345", "IP Camera(D1486)", "DESCRIBE",
	"rtsp://192.168.6.241:554", "25a94a716ee6d7e74d6edda0e6f15dd6");
	printf("md5_digest_get_response: %s\n", pRet);
	free(pRet);
	pRet = NULL;
	return 0;
#if 0
	////    hs1 := md5hash(username + ":" + realm + ":" + password)
	////    hs2 := md5hash(method + ":" + requestUri)
	////    response := md5hash(hs1 + ":" + nonce + ":" + hs2)
	const char* nonce = "25a94a716ee6d7e74d6edda0e6f15dd6";
	const char* buf1 = "admin:IP Camera(D1486):hik12345";
	const char* buf2 = "DESCRIBE:rtsp://192.168.6.241:554";
	unsigned char buf3[1024] = { 0 };

	unsigned char ret1[1024] = { 0 };
	unsigned char ret2[1024] = { 0 };
	unsigned char ret3[1024] = { 0 };

	MD5_CTX hs1;
	MD5_Init(&hs1);
	MD5_Update(&hs1, buf1, strlen(buf1));
	MD5_Final(ret1, &hs1);
	for(int i = 0; i < 16; i ++)
	{
		printf("%02x", ret1[i]);
	}
	printf("\n");

	MD5_CTX hs2;
	MD5_Init(&hs2);
	MD5_Update(&hs2, buf2, strlen(buf2));
	MD5_Final(ret2, &hs2);
	for(int i = 0; i < 16; i ++)
	{
		printf("%02x", ret2[i]);
	}
	printf("\n");

	sprintf(buf3, "%s:%s:%s", ret1, nonce, ret2);
	MD5_CTX hs3;
	MD5_Init(&hs3);
	MD5_Update(&hs3, buf3, strlen(buf3));
	MD5_Final(ret3, &hs3);

	for(int i = 0; i < 16; i ++)
	{
		printf("%02x", ret3[i]);
	}
	printf("\n");
	//f7130dffc92f85197a849247f40ae9ca
	//78c3934eb5bd0465e0de511eba9c5719
	unsigned char buf4[1024] = {0};
	unsigned char ret4[1024] = {0};
	sprintf(buf4, "f7130dffc92f85197a849247f40ae9ca:%s:78c3934eb5bd0465e0de511eba9c5719", nonce);
	MD5_CTX hs4;
	MD5_Init(&hs4);
	MD5_Update(&hs4, buf4, strlen(buf4));
	MD5_Final(ret4, &hs4);

	for(int i = 0; i < 16; i ++)
	{
		printf("%02x", ret4[i]);
	}
	printf("\n");


	printf("8f6cfcbc6264024772272d700b381f92");
#endif
	return 0;
}
