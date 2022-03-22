#ifndef LZF_H
#define LZF_H

/* API version (major * 256 + minor)
 * major API version gets bumped on incompatible changes.
 * minor API version gets bumped on compatible changes.
 * 1.5 => 1.6: add LZF_MAX_COMPRESSED_SIZE
 */
#define LZF_VERSION 0x0106

/*
 * Compress in_len bytes stored at the memory block starting at
 * in_data and write the result to out_data, up to a maximum length
 * of out_len bytes.
 *
 * If the output buffer is not large enough or any error occurs return 0,
 * otherwise return the number of bytes used, which might be considerably
 * more than in_len (but less than 1 + 104% of the original size), so it
 * makes sense to always use out_len == in_len - 1), to ensure _some_
 * compression, and store the data uncompressed otherwise (with a flag, of
 * course.
 *
 * lzf_compress might use different algorithms on different systems and
 * even different runs, thus might result in different compressed strings
 * depending on the phase of the moon or similar factors. However, all
 * these strings are architecture-independent and will result in the
 * original data when decompressed using lzf_decompress.
 *
 * The buffers must not be overlapping.
 *
 * If the option LZF_STATE_ARG is enabled, an extra argument must be
 * supplied which is not reflected in this header file. Refer to lzfP.h
 * and lzf_c.c.
 *
 */
unsigned int lzf_compress (const void *const in_data, unsigned int in_len, void *out_data, unsigned int out_len);

/*
 * The maximum out_len that needs to be allocated to make sure
 * any input data can be compressed without overflowing the output
 * buffer, i.e. maximum out_len = LZF_MAX_COMPRESSED_SIZE (in_len).
 * This is useful if you don't want to bother with the case of
 * incompressible data and just want to provide a buffer that is
 * guaranteeed to be big enough.
 * This macro can be used at preprocessing time.
 */
#define LZF_MAX_COMPRESSED_SIZE(n) ((((n) * 33) >> 5 ) + 1)

/*
 * Decompress data compressed with some version of the lzf_compress
 * function and stored at location in_data and length in_len. The result
 * will be stored at out_data up to a maximum of out_len characters.
 *
 * If the output buffer is not large enough to hold the decompressed
 * data, a 0 is returned and errno is set to E2BIG. Otherwise the number
 * of decompressed bytes (i.e. the original length of the data) is
 * returned.
 *
 * If an error in the compressed data is detected, a zero is returned and
 * errno is set to EINVAL.
 *
 * This function is very fast, about as fast as a copying loop.
 */
unsigned int lzf_decompress (const void *const in_data, unsigned int in_len, void *out_data, unsigned int out_len);

#endif
