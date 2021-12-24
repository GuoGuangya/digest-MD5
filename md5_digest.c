//
// Created by BeanGuohui on 2021/12/21.
//

#include "md5_digest.h"
#include <stdio.h>
#include <string.h>
#include "md5.h"

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
#include <malloc.h>

#if 0
struct md5_digest_t
{
	char pUserName[64];
	char pRealm[64];
	char pPassWord[64];
	char pMethods[64];
	char pRequestUri[64];
	char pNonce[64];
};

md5_digest_t* md5_digest_create(const char* pUserName, const char* pPassWord)
{
	if (NULL == pUserName || NULL == pPassWord)
	{
		printf("param should not be nullptr!\n");
		return NULL;
	}
	if (strlen(pUserName) > 64 || strlen(pPassWord) > 64)
	{
		printf("string length is too longer!");
		return NULL;
	}

	md5_digest_t* pRet = calloc(1, sizeof(md5_digest_t));
	if (NULL == pRet)
	{
		printf("malloc space for md5 digest failed!\n");
		return NULL;
	}

	strcpy(pRet->pUserName, pUserName);
	strcpy(pRet->pPassWord, pPassWord);
	return pRet;
}

void md5_digest_destroy(md5_digest_t** pDigest)
{
	if (NULL != pDigest && NULL != *pDigest)
	{
		free(*pDigest);
		*pDigest = NULL;
	}
}

void md5_digest_update_realm()
{

}

void md5_digest_update_methods()
{

}

void md5_digest_update_request_uri()
{

}

void md5_digest_update_request_nonce()
{

}
#endif

//    hs1 := md5hash(username + ":" + realm + ":" + password)
//    hs2 := md5hash(method + ":" + requestUri)
//    response := md5hash(hs1 + ":" + nonce + ":" + hs2)

char* md5_digest_get_response(const char* pUserName, const char* pPassWord, const char* pRealm, const char* pMethods,
		const char* pRequestUri, const char* pNonce)
{
	 char pCache1[128] = { 0 };
	 char pCache2[128] = { 0 };
	 char pCache3[128] = { 0 };

	 char phs1[128] = { 0 };
	 char phs2[128] = { 0 };
	 char *phs3 = calloc(128, sizeof(char));

	sprintf(pCache1, "%s:%s:%s", pUserName, pRealm, pPassWord);
	sprintf(pCache2, "%s:%s", pMethods, pRequestUri);

	MD5_CTX stCtx1;
	MD5_Init(&stCtx1);
	MD5_Update(&stCtx1, pCache1, strlen(pCache1));
	memset(pCache1, 0, sizeof(pCache1));
	MD5_Final((unsigned  char *)pCache1, &stCtx1);
	for (int i = 0; i < 16; i++)
	{
		sprintf(phs1, "%s%02x", phs1, pCache1[i]);
	}


	MD5_CTX stCtx2;
	MD5_Init(&stCtx2);
	MD5_Update(&stCtx2, pCache2, strlen(pCache2));
	memset(pCache2, 0, sizeof(pCache2));
	MD5_Final(pCache2, &stCtx2);
	for (int i = 0; i < 16; i++)
	{
		sprintf(phs2, "%s%02x", phs2, pCache2[i]);
	}

	sprintf(pCache3, "%s:%s:%s", phs1, pNonce, phs2);
	MD5_CTX hs3;
	MD5_Init(&hs3);
	MD5_Update(&hs3, pCache3, strlen(pCache3));
	memset(pCache3, 0, sizeof(pCache3));
	MD5_Final(pCache3, &hs3);

	for (int i = 0; i < 16; i++)
	{
		sprintf(phs3, "%s%02x", phs3, pCache3[i]);
	}
	return phs3;
}
