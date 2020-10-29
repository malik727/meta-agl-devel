/*
 * adcpf common header
 *
 * @copyright Copyright (c) 2016-2019 TOYOTA MOTOR CORPORATION.
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

#ifndef _AGLDD_H_
#define _AGLDD_H_
#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#if !defined(__cplusplus)
#include <stdbool.h>
#endif	/* !defined(__cplusplus) */
#endif /* __KERNEL__ */

#ifndef __KERNEL__
#define __LINUX_ARM_ARCH__ 7
#define BITS_PER_LONG 32

#define	__AGLDD_TYPEDEF_I64
typedef long long		i64;	/* 8-byte signed integer */

#define	__AGLDD_TYPEDEF_U64
typedef unsigned long long	u64;	/* 8-byte unsigned integer */

#define	__AGLDD_TYPEDEF_U32
typedef unsigned long		u32;	/* 4-byte unsigned integer */

#define	__AGLDD_TYPEDEF_U16
typedef unsigned short		u16;	/* 2-byte unsigned integer */

#define	__AGLDD_TYPEDEF_I16
typedef short			i16;	/* 2-byte signed integer */

#define	__AGLDD_TYPEDEF_U8
typedef unsigned char		u8;	/* 1-byte unsigned integer */

#define	__AGLDD_TYPEDEF_I8
typedef char			i8;	/* 1-byte signed integer */
#endif

#define	__AGLDD_TYPEDEF_INT8
typedef signed char		INT8;

#define	__AGLDD_TYPEDEF_INT16
typedef signed short		INT16;

#define	__AGLDD_TYPEDEF_INT32
typedef signed int		INT32;

#define	__AGLDD_TYPEDEF_INT64
typedef signed long long	INT64;

#define	__AGLDD_TYPEDEF_UINT8
typedef unsigned char		UINT8;

#define	__AGLDD_TYPEDEF_UINT16
typedef unsigned short		UINT16;

#define	__AGLDD_TYPEDEF_UINT32
typedef unsigned int		UINT32;

#define	__AGLDD_TYPEDEF_UINT64
typedef unsigned long long	UINT64;

#ifndef __KERNEL__
#if !defined    __WIN_TYPEDEF_BOOL
#define __AGLDD_TYPEDEF_BOOL
typedef UINT32                  BOOL;
#endif
#endif

#ifndef TRUE
#define TRUE			true
#endif
#ifndef FALSE
#define FALSE			false
#endif

#endif/* _AGLDD_H_ */
