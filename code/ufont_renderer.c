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

mp_obj_t ufont_render(size_t nargs, const mp_obj_t *args) {
    // Unpacks a pattern into a binary array. The function is meant as a fast implementation of 
    // https://github.com/peterhinch/micropython-font-to-py/blob/master/writer/writer.py
    //
    // Arguments are
    //
    // 		output buffer (memoryview)
    // 		pattern (bytearray/memoryview)
    // 		height (font height, integer, pixels)
    // 		foreground colour (2-byte bytearray)
    // 		background colour (2-byte bytearray)
    //  
    // If a bit is set in 'pattern', then the corresponding two bytes in the output buffer 
    // will be set to the two bytes given by 'foreground', while in the opposite 
    // case, the two bytes will be taken from 'background'. 
    //
    // Example
    //
    // 	buffer = bytearray(1000)
    // 	memview = memoryview(buffer)
    //  pat = bytearray([1, 2, 3, 4, 5]) # this is 40 bits altogether
    //  pattern = memoryview(pat)
    //  height = 10 # this particular font is 4 pixels wide
    // 	foreground = bytearray([200, 200])
    // 	background = bytearray([0, 0])
    // 	render(memview, pattern, height, foreground, background)

    // TODO: in principle, args[1], args[3], and args[4] could be bytes. Should we allow for that?
    if (!mp_obj_is_type(args[0], &mp_type_memoryview) || !mp_obj_is_type(args[1], &mp_type_bytearray) 
        || !mp_obj_is_type(args[3], &mp_type_bytearray) || !mp_obj_is_type(args[4], &mp_type_bytearray)) {
        mp_raise_TypeError("wrong argument type");		
    }

    mp_obj_array_t *mv = MP_OBJ_TO_PTR(args[0]);
    mp_obj_array_t *pat = MP_OBJ_TO_PTR(args[1]);
    size_t height = MP_OBJ_SMALL_INT_VALUE(args[2]);
    mp_obj_array_t *fg = MP_OBJ_TO_PTR(args[3]);
    mp_obj_array_t *bg = MP_OBJ_TO_PTR(args[4]);
    if ((fg->len != 2) || (bg->len != 2)) {
        mp_raise_ValueError("foreground/background pattern should be two bytes long");
    }
    if (mv->len < 2*8*pat->len) {
        // Each byte in the pattern holds the description of 8 pixels, and each pixel requires two bytes
        mp_raise_ValueError("buffer length should be larger than pattern length times 16");
    }
    size_t i, j, k=0;
    char pattern_byte;
    char *p = pat->items;
    char *m = mv->items;
    char *fore = fg->items;
    char *back = bg->items;

    for (i=0; k < (pat->len*16/height)*height; i++) {
        char mask = 0b10000000;
        pattern_byte = p[i];
        for (j=0; j < 8; j++) {
            if (mask & pattern_byte) {
                m[k] = fore[0];
                m[k+1] = fore[1];
            } else {
                m[k] = back[0];
                m[k+1] = back[1];
            }
            mask >>= 1;
            k += 2;
        }
    }
    return mp_const_true;
}
