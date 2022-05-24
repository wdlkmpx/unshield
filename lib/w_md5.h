/*
 ***  Modified to be header-only ***
 * 
 * This is an OpenSSL-compatible implementation of the RSA Data Security, Inc.
 * MD5 Message-Digest Algorithm (RFC 1321).
 *
 * Homepage:
 * http://openwall.info/wiki/people/solar/software/public-domain-source-code/md5
 *
 * Author:
 * Alexander Peslyak, better known as Solar Designer <solar at openwall.com>
 *
 * This software was written by Alexander Peslyak in 2001.  No copyright is
 * claimed, and the software is hereby placed in the public domain.
 * In case this attempt to disclaim copyright and place the software in the
 * public domain is deemed null and void, then the software is
 * Copyright (c) 2001 Alexander Peslyak and it is hereby released to the
 * general public under the following terms:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * There's ABSOLUTELY NO WARRANTY, express or implied.
 *
 */

#ifndef _SD_MD5_H_
#define _SD_MD5_H_

#include <string.h>

/* Any 32-bit or wider unsigned integer data type will do */
#define MD5_u32plus unsigned int

typedef struct 
{
	MD5_u32plus lo, hi;
	MD5_u32plus a, b, c, d;
	unsigned char buffer[64];
	MD5_u32plus block[16];
} sd_MD5_CTX;

#ifndef SD_MD5_NO_COMPAT_MACRO
#  define MD5_Init   sd_MD5_Init
#  define MD5_Update sd_MD5_Update
#  define MD5_Final  sd_MD5_Final
#  define MD5_CTX    sd_MD5_CTX
#endif

static void sd_MD5_Init   (sd_MD5_CTX *ctx);
static void sd_MD5_Update (sd_MD5_CTX *ctx, const void *data, unsigned long size);
static void sd_MD5_Final  (unsigned char *result, sd_MD5_CTX *ctx);

// ==============================================================================

/*
 * The basic MD5 functions.
 *
 * F and G are optimized compared to their RFC 1321 definitions for
 * architectures that lack an AND-NOT instruction, just like in Colin Plumb's
 * implementation.
 */
#define sdmd5_F(x, y, z)	((z) ^ ((x) & ((y) ^ (z))))
#define sdmd5_G(x, y, z)	((y) ^ ((z) & ((x) ^ (y))))
#define sdmd5_H(x, y, z)	(((x) ^ (y)) ^ (z))
#define sdmd5_H2(x, y, z)	((x) ^ ((y) ^ (z)))
#define sdmd5_I(x, y, z)	((y) ^ ((x) | ~(z)))

/*
 * The MD5 transformation for all four rounds.
 */
#define sdmd5_STEP(f, a, b, c, d, x, t, s) \
	(a) += f((b), (c), (d)) + (x) + (t); \
	(a) = (((a) << (s)) | (((a) & 0xffffffff) >> (32 - (s)))); \
	(a) += (b);

#define sdmd5_SET(n) \
	(ctx->block[(n)] = \
	(MD5_u32plus)ptr[(n) * 4] | \
	((MD5_u32plus)ptr[(n) * 4 + 1] << 8) | \
	((MD5_u32plus)ptr[(n) * 4 + 2] << 16) | \
	((MD5_u32plus)ptr[(n) * 4 + 3] << 24))

#define sdmd5_GET(n) \
	(ctx->block[(n)])

/*
 * This processes one or more 64-byte data blocks, but does NOT update the bit
 * counters.  There are no alignment requirements.
 */
static const void *sdmd5_body(sd_MD5_CTX *ctx, const void *data, unsigned long size)
{
	const unsigned char *ptr;
	MD5_u32plus a, b, c, d;
	MD5_u32plus saved_a, saved_b, saved_c, saved_d;

	ptr = (const unsigned char *)data;

	a = ctx->a;
	b = ctx->b;
	c = ctx->c;
	d = ctx->d;

	do {
		saved_a = a;
		saved_b = b;
		saved_c = c;
		saved_d = d;

/* Round 1 */
		sdmd5_STEP (sdmd5_F, a, b, c, d, sdmd5_SET(0), 0xd76aa478, 7)
		sdmd5_STEP (sdmd5_F, d, a, b, c, sdmd5_SET(1), 0xe8c7b756, 12)
		sdmd5_STEP (sdmd5_F, c, d, a, b, sdmd5_SET(2), 0x242070db, 17)
		sdmd5_STEP (sdmd5_F, b, c, d, a, sdmd5_SET(3), 0xc1bdceee, 22)
		sdmd5_STEP (sdmd5_F, a, b, c, d, sdmd5_SET(4), 0xf57c0faf, 7)
		sdmd5_STEP (sdmd5_F, d, a, b, c, sdmd5_SET(5), 0x4787c62a, 12)
		sdmd5_STEP (sdmd5_F, c, d, a, b, sdmd5_SET(6), 0xa8304613, 17)
		sdmd5_STEP (sdmd5_F, b, c, d, a, sdmd5_SET(7), 0xfd469501, 22)
		sdmd5_STEP (sdmd5_F, a, b, c, d, sdmd5_SET(8), 0x698098d8, 7)
		sdmd5_STEP (sdmd5_F, d, a, b, c, sdmd5_SET(9), 0x8b44f7af, 12)
		sdmd5_STEP (sdmd5_F, c, d, a, b, sdmd5_SET(10), 0xffff5bb1, 17)
		sdmd5_STEP (sdmd5_F, b, c, d, a, sdmd5_SET(11), 0x895cd7be, 22)
		sdmd5_STEP (sdmd5_F, a, b, c, d, sdmd5_SET(12), 0x6b901122, 7)
		sdmd5_STEP (sdmd5_F, d, a, b, c, sdmd5_SET(13), 0xfd987193, 12)
		sdmd5_STEP (sdmd5_F, c, d, a, b, sdmd5_SET(14), 0xa679438e, 17)
		sdmd5_STEP (sdmd5_F, b, c, d, a, sdmd5_SET(15), 0x49b40821, 22)

/* Round 2 */
		sdmd5_STEP (sdmd5_G, a, b, c, d, sdmd5_GET(1), 0xf61e2562, 5)
		sdmd5_STEP (sdmd5_G, d, a, b, c, sdmd5_GET(6), 0xc040b340, 9)
		sdmd5_STEP (sdmd5_G, c, d, a, b, sdmd5_GET(11), 0x265e5a51, 14)
		sdmd5_STEP (sdmd5_G, b, c, d, a, sdmd5_GET(0), 0xe9b6c7aa, 20)
		sdmd5_STEP (sdmd5_G, a, b, c, d, sdmd5_GET(5), 0xd62f105d, 5)
		sdmd5_STEP (sdmd5_G, d, a, b, c, sdmd5_GET(10), 0x02441453, 9)
		sdmd5_STEP (sdmd5_G, c, d, a, b, sdmd5_GET(15), 0xd8a1e681, 14)
		sdmd5_STEP (sdmd5_G, b, c, d, a, sdmd5_GET(4), 0xe7d3fbc8, 20)
		sdmd5_STEP (sdmd5_G, a, b, c, d, sdmd5_GET(9), 0x21e1cde6, 5)
		sdmd5_STEP (sdmd5_G, d, a, b, c, sdmd5_GET(14), 0xc33707d6, 9)
		sdmd5_STEP (sdmd5_G, c, d, a, b, sdmd5_GET(3), 0xf4d50d87, 14)
		sdmd5_STEP (sdmd5_G, b, c, d, a, sdmd5_GET(8), 0x455a14ed, 20)
		sdmd5_STEP (sdmd5_G, a, b, c, d, sdmd5_GET(13), 0xa9e3e905, 5)
		sdmd5_STEP (sdmd5_G, d, a, b, c, sdmd5_GET(2), 0xfcefa3f8, 9)
		sdmd5_STEP (sdmd5_G, c, d, a, b, sdmd5_GET(7), 0x676f02d9, 14)
		sdmd5_STEP (sdmd5_G, b, c, d, a, sdmd5_GET(12), 0x8d2a4c8a, 20)

/* Round 3 */
		sdmd5_STEP (sdmd5_H,  a, b, c, d, sdmd5_GET(5), 0xfffa3942, 4)
		sdmd5_STEP (sdmd5_H2, d, a, b, c, sdmd5_GET(8), 0x8771f681, 11)
		sdmd5_STEP (sdmd5_H,  c, d, a, b, sdmd5_GET(11), 0x6d9d6122, 16)
		sdmd5_STEP (sdmd5_H2, b, c, d, a, sdmd5_GET(14), 0xfde5380c, 23)
		sdmd5_STEP (sdmd5_H,  a, b, c, d, sdmd5_GET(1), 0xa4beea44, 4)
		sdmd5_STEP (sdmd5_H2, d, a, b, c, sdmd5_GET(4), 0x4bdecfa9, 11)
		sdmd5_STEP (sdmd5_H,  c, d, a, b, sdmd5_GET(7), 0xf6bb4b60, 16)
		sdmd5_STEP (sdmd5_H2, b, c, d, a, sdmd5_GET(10), 0xbebfbc70, 23)
		sdmd5_STEP (sdmd5_H,  a, b, c, d, sdmd5_GET(13), 0x289b7ec6, 4)
		sdmd5_STEP (sdmd5_H2, d, a, b, c, sdmd5_GET(0), 0xeaa127fa, 11)
		sdmd5_STEP (sdmd5_H,  c, d, a, b, sdmd5_GET(3), 0xd4ef3085, 16)
		sdmd5_STEP (sdmd5_H2, b, c, d, a, sdmd5_GET(6), 0x04881d05, 23)
		sdmd5_STEP (sdmd5_H,  a, b, c, d, sdmd5_GET(9), 0xd9d4d039, 4)
		sdmd5_STEP (sdmd5_H2, d, a, b, c, sdmd5_GET(12), 0xe6db99e5, 11)
		sdmd5_STEP (sdmd5_H,  c, d, a, b, sdmd5_GET(15), 0x1fa27cf8, 16)
		sdmd5_STEP (sdmd5_H2, b, c, d, a, sdmd5_GET(2), 0xc4ac5665, 23)

/* Round 4 */
		sdmd5_STEP (sdmd5_I, a, b, c, d, sdmd5_GET(0), 0xf4292244, 6)
		sdmd5_STEP (sdmd5_I, d, a, b, c, sdmd5_GET(7), 0x432aff97, 10)
		sdmd5_STEP (sdmd5_I, c, d, a, b, sdmd5_GET(14), 0xab9423a7, 15)
		sdmd5_STEP (sdmd5_I, b, c, d, a, sdmd5_GET(5), 0xfc93a039, 21)
		sdmd5_STEP (sdmd5_I, a, b, c, d, sdmd5_GET(12), 0x655b59c3, 6)
		sdmd5_STEP (sdmd5_I, d, a, b, c, sdmd5_GET(3), 0x8f0ccc92, 10)
		sdmd5_STEP (sdmd5_I, c, d, a, b, sdmd5_GET(10), 0xffeff47d, 15)
		sdmd5_STEP (sdmd5_I, b, c, d, a, sdmd5_GET(1), 0x85845dd1, 21)
		sdmd5_STEP (sdmd5_I, a, b, c, d, sdmd5_GET(8), 0x6fa87e4f, 6)
		sdmd5_STEP (sdmd5_I, d, a, b, c, sdmd5_GET(15), 0xfe2ce6e0, 10)
		sdmd5_STEP (sdmd5_I, c, d, a, b, sdmd5_GET(6), 0xa3014314, 15)
		sdmd5_STEP (sdmd5_I, b, c, d, a, sdmd5_GET(13), 0x4e0811a1, 21)
		sdmd5_STEP (sdmd5_I, a, b, c, d, sdmd5_GET(4), 0xf7537e82, 6)
		sdmd5_STEP (sdmd5_I, d, a, b, c, sdmd5_GET(11), 0xbd3af235, 10)
		sdmd5_STEP (sdmd5_I, c, d, a, b, sdmd5_GET(2), 0x2ad7d2bb, 15)
		sdmd5_STEP (sdmd5_I, b, c, d, a, sdmd5_GET(9), 0xeb86d391, 21)

		a += saved_a;
		b += saved_b;
		c += saved_c;
		d += saved_d;

		ptr += 64;
	} while (size -= 64);

	ctx->a = a;
	ctx->b = b;
	ctx->c = c;
	ctx->d = d;

	return ptr;
}

static void sd_MD5_Init(sd_MD5_CTX *ctx)
{
	ctx->a = 0x67452301;
	ctx->b = 0xefcdab89;
	ctx->c = 0x98badcfe;
	ctx->d = 0x10325476;

	ctx->lo = 0;
	ctx->hi = 0;
}

static void sd_MD5_Update(sd_MD5_CTX *ctx, const void *data, unsigned long size)
{
	MD5_u32plus saved_lo;
	unsigned long used, available;

	saved_lo = ctx->lo;
	if ((ctx->lo = (saved_lo + size) & 0x1fffffff) < saved_lo)
		ctx->hi++;
	ctx->hi += size >> 29;

	used = saved_lo & 0x3f;

	if (used) {
		available = 64 - used;

		if (size < available) {
			memcpy(&ctx->buffer[used], data, size);
			return;
		}

		memcpy(&ctx->buffer[used], data, available);
		data = (const unsigned char *)data + available;
		size -= available;
		sdmd5_body(ctx, ctx->buffer, 64);
	}

	if (size >= 64) {
		data = sdmd5_body(ctx, data, size & ~(unsigned long)0x3f);
		size &= 0x3f;
	}

	memcpy(ctx->buffer, data, size);
}

#define sdmd5_OUT(dst, src) \
	(dst)[0] = (unsigned char)(src); \
	(dst)[1] = (unsigned char)((src) >> 8); \
	(dst)[2] = (unsigned char)((src) >> 16); \
	(dst)[3] = (unsigned char)((src) >> 24);

static void sd_MD5_Final(unsigned char *result, sd_MD5_CTX *ctx)
{
	unsigned long used, available;

	used = ctx->lo & 0x3f;

	ctx->buffer[used++] = 0x80;

	available = 64 - used;

	if (available < 8) {
		memset(&ctx->buffer[used], 0, available);
		sdmd5_body(ctx, ctx->buffer, 64);
		used = 0;
		available = 64;
	}

	memset(&ctx->buffer[used], 0, available - 8);

	ctx->lo <<= 3;
	sdmd5_OUT(&ctx->buffer[56], ctx->lo)
	sdmd5_OUT(&ctx->buffer[60], ctx->hi)

	sdmd5_body(ctx, ctx->buffer, 64);

	sdmd5_OUT(&result[0], ctx->a)
	sdmd5_OUT(&result[4], ctx->b)
	sdmd5_OUT(&result[8], ctx->c)
	sdmd5_OUT(&result[12], ctx->d)

	memset(ctx, 0, sizeof(*ctx));
}


#endif /* _SD_MD5_H_ */
