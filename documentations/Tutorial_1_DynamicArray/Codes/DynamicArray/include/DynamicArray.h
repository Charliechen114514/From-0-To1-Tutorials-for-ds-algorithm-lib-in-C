#pragma once
#include <stdint.h>
#include "DynamicArrayDefines.h"
typedef void*   HoldType;

/*
    Define a Array Plain Buffer
*/
typedef struct __CCDynamic_Array CCDynamic_Array;
typedef uint32_t(*property_hook_check_func_ptr)(CCDynamic_Array*);

typedef struct __CCDynamic_Array{
    /* we use pointers points to a usable array */
    HoldType*   array;
    uint32_t    element_size;   // using in elementary check
    uint32_t    current_size;   // using in the current_size_hook
    uint32_t    total_size;     // using in marking the total size
    uint32_t    max_allowed_size; // using in marking the max allowed allocate
    /* checking hook, using for the check of required */
    property_hook_check_func_ptr overlimited_check_hook;
    /* checking if we allowed more blocks */
    /* one should return 0 if no longer accept allocated */
    /* else returns the blocks size*/
    property_hook_check_func_ptr allocate_indicator;
}CCDynamic_Array;

/* this will call the default*/
/* user should provide a memory array */
/* if it has been static and cannot be modified */
// pass MALLOC_PURE_FROM_HEAP for pure malloc in heap
void CCDynamic_Array_dynamic_init(
    CCDynamic_Array*    blank_array,
    void*               reserved_pool,      // < provide an mallocable pool
    uint32_t            element_sz          // < provide the element size
);

void CCDynamic_Array_static_init(
    CCDynamic_Array*    blank_array,
    void*               reserved_pool,              // provide a pool that static exsit
    uint32_t            element_sz,                 // < provide the element size
    uint32_t            max_allowed_sz
);

uint8_t CCDynamic_Array_pushback(
    CCDynamic_Array*    blank_array,
    void*               data_itself,
    uint32_t            element_sz
);

uint8_t CCDynamic_Array_pop(
    CCDynamic_Array*    blank_array
);

typedef enum {
    DynamicArray_HOOK_OVERLIMIT_CHECK,
    DynamicArray_HOOK_ALLOCATE_CHECK
}DynamicArray_HOOKPropertyFlag;
void _CCDynamic_Array_register_hooks(
    CCDynamic_Array*                blank_array,
    property_hook_check_func_ptr    user_hook,
    DynamicArray_HOOKPropertyFlag   flags
);
