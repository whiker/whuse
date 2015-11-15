#include <iostream>
#include <stdint.h>
#include <string.h>

#include <uuid/uuid.h>

using namespace std;


#define TEA_ITER_NUM 32
#define TEA_ENDELTA  0x9E3779B9
#define TEA_DEDELTA  0xC6EF3720

void tea_encrypt(const uint32_t *src, const uint32_t *key, uint32_t *dst)
{
	register uint32_t s1=src[0], s2=src[1];
	register uint32_t a=key[0], b=key[1], c=key[2], d=key[3];
	register uint32_t sum=0, delta=TEA_ENDELTA;
	
	for (register int i = TEA_ITER_NUM; --i >= 0; )
	{
		sum += delta;
		s1 += ((s2<<4) + a) ^ (s2 + sum) ^ ((s2>>5) + b);
		s2 += ((s1<<4) + c) ^ (s1 + sum) ^ ((s1>>5) + d);
	}
	
	dst[0] = s1;
	dst[1] = s2;
}

void tea_decrypt(const uint32_t *src, const uint32_t *key, uint32_t *dst)
{
	register uint32_t s1=src[0], s2=src[1];
	register uint32_t a=key[0], b=key[1], c=key[2], d=key[3];
	register uint32_t sum=TEA_DEDELTA, delta=TEA_ENDELTA;
	
	for (register int i = TEA_ITER_NUM; --i >= 0; )
	{
		s2 -= ((s1<<4) + c) ^ (s1 + sum) ^ ((s1>>5) + d);
		s1 -= ((s2<<4) + a) ^ (s2 + sum) ^ ((s2>>5) + b);
		sum -= delta;
	}
	
	dst[0] = s1;
	dst[1] = s2;
}

void tea_encrypt_n(const void *src, const void *key, void *dst, int n)
{
	const uint32_t *src_ = (const uint32_t*) src;
	uint32_t *dst_ = (uint32_t*) dst;
	
	for (int i = n; --i >= 0; )
	{
		tea_encrypt(src_, (const uint32_t*) key, dst_);
		src_ += 2;
		dst_ += 2;
	}
}

void tea_decrypt_n(const void *src, const void *key, void *dst, int n)
{
	const uint32_t *src_ = (const uint32_t*) src;
	uint32_t *dst_ = (uint32_t*) dst;
	
	for (int i = n; --i >= 0; )
	{
		tea_decrypt(src_, (const uint32_t*) key, dst_);
		src_ += 2;
		dst_ += 2;
	}
}


int main()
{
	cout << sizeof(uuid_t) << endl;
	uuid_t uuid;
	char a[40];
	
	memset(a, 'a', 40);
	uuid_generate(uuid);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	const char *key_str = "1234567812345678";
	char key[16];
	strncpy(key, key_str, 16);
	
	tea_encrypt_n(&uuid, key, &uuid, 2);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	tea_decrypt_n(&uuid, key, &uuid, 2);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	memset(a, 'a', 40);
	uuid_generate(uuid);
	uuid_unparse(uuid, a);
	cout << strlen(a) << "  " << a << endl;
	
	return 0;
}