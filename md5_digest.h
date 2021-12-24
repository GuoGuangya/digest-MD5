//
// Created by BeanGuohui on 2021/12/21.
//

#ifndef UNTITLED2_MD5_DIGEST_H
#define UNTITLED2_MD5_DIGEST_H
//typedef struct md5_digest_t md5_digest_t;
char* md5_digest_get_response(const char* pUserName, const char* pPassWord, const char* realm, const char* pMethods,
		const char* requestUri, const char* nonce);
#endif //UNTITLED2_MD5_DIGEST_H
