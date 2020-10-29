/*
 * @copyright Copyright (c) 2017-2019 TOYOTA MOTOR CORPORATION.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _AGL_TYPES_OBSOLUTED_H_
#define _AGL_TYPES_OBSOLUTED_H_

#include <sys/mman.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <linux/types.h>
#include <stdio.h>

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <errno.h>

typedef u_int64_t		_Uint64t;
typedef int64_t			_Int64t;
typedef u_int32_t		_Uint32t;
typedef int32_t			_Int32t;
typedef u_int16_t		_Uint16t;
typedef int16_t			_Int16t;
typedef u_int8_t		_Uint8t;
typedef int8_t			_Int8t;

typedef _Int8t					_int8;
typedef _Uint8t					_uint8;
typedef _Int16t					_int16;
typedef _Uint16t				_uint16;
typedef _Int32t					_int32;
typedef _Uint32t				_uint32;
typedef _Int64t					_int64;
typedef _Uint64t				_uint64;


#ifdef AGL_PosixBasedOS001LEGACY_USED
#define AGL_PROTECTION_NO_CACHE        0x00000800
#define AGL_MAP_NON_INIT       0x00004000
#define AGL_MAP_PHYSICAL           0x00010000
#define AGL_NON_FD             (-1)
#define AGL_MAP_DEV_FAILED ((unsigned long)MAP_FAILED)
#endif /*AGL_PosixBasedOS001LEGACY_USED*/

#define	EOK	0

#ifdef AGL_PosixBasedOS001LEGACY_USED
#define agl_io_in32(_x) *(volatile unsigned long *)(_x)
#define agl_io_out32(_x, _y) {*(volatile unsigned long *)((void*)(_x)) = (_y);}
#endif /*AGL_PosixBasedOS001LEGACY_USED*/



#define	__AGLDD_TYPEDEF_I64
typedef int64_t		i64;	/* 8-byte signed integer */

#define	__AGLDD_TYPEDEF_U64
typedef uint64_t	u64;	/* 8-byte unsigned integer */

#define	__AGLDD_TYPEDEF_U32
typedef uint32_t		u32;	/* 4-byte unsigned integer */

#define	__AGLDD_TYPEDEF_U16
typedef uint16_t		u16;	/* 2-byte unsigned integer */

#define	__AGLDD_TYPEDEF_I16
typedef int16_t			i16;	/* 2-byte signed integer */

#define	__AGLDD_TYPEDEF_U8
typedef uint8_t		u8;	/* 1-byte unsigned integer */

#define	__AGLDD_TYPEDEF_I8
typedef int8_t			i8;	/* 1-byte signed integer */

#define	__AGLDD_TYPEDEF_INT8
typedef int8_t		INT8;

#define	__AGLDD_TYPEDEF_INT16
typedef int16_t		INT16;

#define	__AGLDD_TYPEDEF_INT32
typedef int32_t		INT32;

#define	__AGLDD_TYPEDEF_INT64
typedef int64_t	INT64;

#define	__AGLDD_TYPEDEF_UINT8
typedef uint8_t		UINT8;

#define	__AGLDD_TYPEDEF_UINT16
typedef uint16_t		UINT16;

#define	__AGLDD_TYPEDEF_UINT32
typedef uint32_t		UINT32;

#define	__AGLDD_TYPEDEF_UINT64
typedef uint64_t	UINT64;

#ifndef __KERNEL__
#if !defined    __WIN_TYPEDEF_BOOL
#define __AGLDD_TYPEDEF_BOOL
typedef uint32_t                  BOOL;
#endif
#endif

#ifndef TRUE
#define TRUE			1
#endif
#ifndef FALSE
#define FALSE			0
#endif

// AGL ASSERT MACRO
#ifdef AGL_ASSERT_ON
#define AGL_ASSERT_NOT_TESTED() \
do {fprintf(stderr, "[%s][%s][%s:%d]AGL_ASSERT_NOT_TESTED.\n",  \
    program_invocation_short_name, __func__, __FILE__, __LINE__);} while(0)
#else
#define AGL_ASSERT_NOT_TESTED() \
do {} while(0)
#endif
#endif /* _AGL_TYPES_OBSOLUTED_H_ */
