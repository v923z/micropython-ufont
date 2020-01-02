/*
 * This file is part of the micropython-ufont project, 
 *
 * https://github.com/v923z/micropython-ufont
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Zoltán Vörös
*/
    
#include "py/obj.h"
#include "py/runtime.h"
#include "py/objarray.h"

mp_obj_t _fill_rectangle(mp_obj_t mv, mp_obj_t col, size_t x0, size_t y0, size_t width, size_t height, size_t canvas_width, size_t canvas_height) {
    mp_obj_array_t *memview = MP_OBJ_TO_PTR(mv); // pointer to the memoryview
    if (!MP_OBJ_IS_TYPE(memview, &mp_type_memoryview)) {
        mp_raise_ValueError("first argument must be a memoryview object");
    }
    char *v = memview->items;

    mp_obj_array_t *colour = MP_OBJ_TO_PTR(col); // pointer to the colour definition (2 bytes altogether)
    // TODO: should we allow for bytes, too?
    if ((colour->len != 2) || !MP_OBJ_IS_TYPE(colour, &mp_type_bytearray)) {
        mp_raise_ValueError("second argument must be a two-byte long bytearray");
    }
    char *c = colour->items;

    if((x0 + width > canvas_width) || (y0 + height > canvas_height)) {
        mp_raise_ValueError("rectangle does not fit canvas");
    }

    size_t k;
    for(size_t i=0; i<height; i++) {
        k = 2*(canvas_width*(y0+i)+x0);
        for(size_t j=0; j<width; j++, k+=2) {
            v[k] = c[0];
            v[k+1] = c[1];
        }
    }
    return mp_const_true;
}

mp_obj_t ufont_fill_rectangle(size_t nargs, const mp_obj_t *args) {
    // This is simply a wrapper for _fill_rectangle, so that the function can be exposed in the python interface
    if (nargs != 8) {
        mp_raise_ValueError("function requires 8 arguments");
    }
    size_t x0 = MP_OBJ_SMALL_INT_VALUE(args[2]); // (x0, y0) are the coordinates within the canvas
    size_t y0 = MP_OBJ_SMALL_INT_VALUE(args[3]);
    size_t width = MP_OBJ_SMALL_INT_VALUE(args[4]); // width, and height are the dimensions of the rectangle
    size_t height = MP_OBJ_SMALL_INT_VALUE(args[5]);
    size_t canvas_width = MP_OBJ_SMALL_INT_VALUE(args[6]); // cwidth, and cheight are the dimensions of the canvas
    size_t canvas_height = MP_OBJ_SMALL_INT_VALUE(args[7]);
    return _fill_rectangle(args[0], args[1], x0, y0, width, height, canvas_width, canvas_height);
}
