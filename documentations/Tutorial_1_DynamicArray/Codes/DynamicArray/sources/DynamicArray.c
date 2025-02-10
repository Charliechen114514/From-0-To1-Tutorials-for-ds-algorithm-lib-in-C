#include "DynamicArray.h"

static uint32_t __default_overflow_hook(CCDynamic_Array* array){
    // when it reachs the limit, we need to allocate
    return array->current_size >= array->total_size;
}

static uint32_t __default_allocate_indicator_hook(CCDynamic_Array* array){
    if(array->current_size >= array->total_size){
        // then we need to make new allocate 
        return MALLOC_SZ_MORE * array->current_size;
    }else if(array->current_size < MALLOC_SZ_LESS * array->total_size){
        return MALLOC_SZ_LESS * array->total_size;
    }
    // hold the static
    return array->total_size;
}

static uint32_t __default_static_allocator_indicator_hook(CCDynamic_Array* array){
    if(array->current_size >= array->total_size){
        // then we need to make new allocate 
        return MALLOC_SZ_MORE * array->current_size > array->max_allowed_size ?
            array->max_allowed_size : MALLOC_SZ_MORE * array->current_size;
    }else if(array->current_size < MALLOC_SZ_LESS * array->total_size){
        return MALLOC_SZ_LESS * array->total_size;
    }
    // hold the static
    return array->total_size;    
}

/* this will call the default*/
/* user should provide a memory array */
/* if it has been static and cannot be modified */
// pass MALLOC_PURE_FROM_HEAP for pure malloc in heap
void CCDynamic_Array_dynamic_init(
    CCDynamic_Array*    blank_array,
    void*               reserved_pool,
    uint32_t            element_sz      // < provide the element size
){
    blank_array->current_size = 0;
    blank_array->element_size = element_sz;
    blank_array->overlimited_check_hook = __default_overflow_hook;
    blank_array->allocate_indicator = __default_allocate_indicator_hook;
    blank_array->array = reserved_pool;
    blank_array->max_allowed_size = UINT32_MAX;
}

void CCDynamic_Array_static_init(
    CCDynamic_Array*    blank_array,
    void*               reserved_pool,              // provide a pool that static exsit
    uint32_t            element_sz,                 // < provide the element size
    uint32_t            max_allowed_sz
)
{
    blank_array->array = reserved_pool;
    blank_array->current_size = 0;
    blank_array->overlimited_check_hook = __default_overflow_hook;
    blank_array->allocate_indicator = __default_static_allocator_indicator_hook;
    blank_array->max_allowed_size = max_allowed_sz;
    blank_array->element_size = element_sz;
}

void _CCDynamic_Array_register_hooks(
    CCDynamic_Array*                blank_array,
    property_hook_check_func_ptr    user_hook,
    DynamicArray_HOOKPropertyFlag   flags
){
    switch (flags)
    {
    case DynamicArray_HOOK_OVERLIMIT_CHECK:
        blank_array->overlimited_check_hook = user_hook;
    break;
    case DynamicArray_HOOK_ALLOCATE_CHECK:
        blank_array->allocate_indicator = user_hook;
    break;
    }
}
