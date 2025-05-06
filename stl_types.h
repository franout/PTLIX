#ifndef __STL_TYPES_H__
#define __STL_TYPES_H__


#include "typedefs.h"


#define STL_TRUE 						1u
#define STL_FALSE 						0u

#define SLT_NULL						0x00000000UL

typedef int STL_SIGNATURE_T;

typedef enum {
	STL_ERROR_NONE=0,
	STL_ERROR_NOT_IMPLEMENTED=2,
	STL_ERROR_TASK_ALLOCATION=10,

	STL_ERROR_RELOCATION=20,

	STL_ERROR_SIG_MISMATCH=30,


	STL_ERROR_INDEX=40,


	STL_ERROR_SBST=50,


	STL_CPU_OUT_OF_BOUNDS=60,
	STL_INDEX_OUT_OF_BOUNDS=70,

	SLT_NO_RT_ROUTINE=80,
	SLT_NO_BT_ROUTINE=90
} STL_ERROR_T;


typedef char STL_BOOL;

typedef uint16_t STL_SIZE_T;
typedef uint32_t SLT_INT32U_T;

typedef uint32_t STL_ADDR_T;



typedef STL_SIGNATURE_T (*STL_FUNCT_PTR_T)(void);


#endif /* __STL_TYPES_H__*/
