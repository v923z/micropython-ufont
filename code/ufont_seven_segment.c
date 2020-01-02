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

#include "ufont_rectangle.h"

mp_obj_t ufont_seven_segment(size_t nargs, const mp_obj_t *args) {
    // Fills up the memoryview in the first argument with the digit given in the second argument
    // The third argument is the height of the font (in pixels), while the fourth is the weight (thickness)
    // The last two arguments are the foreground and background colours, two bytearrays of length at least 2.
    //
    // Example:
    //
    // buffer = bytearray(1000)
    // memview = memoryview(buffer)
    // foreground = bytearray([200, 200])
    // background = bytearray([0, 0])
    // seven_segment(memview, '1', 20, 3, foreground, background)
    //
    // TODO: it might make sense to implement the simple operators +, / and *, as well as the = sign

    if (MP_OBJ_IS_TYPE(args[0], &mp_type_memoryview)) {
        mp_obj_t mv = args[0]; // memoryview
        mp_obj_t fg = args[4]; // foreground colour
        mp_obj_t bg = args[5]; // background colour

        size_t digit, len;
        const byte *str = (const byte*)mp_obj_str_get_data(args[1], &len);
        len = utf8_charlen(str, len);
        if (len == 1) {
            digit = utf8_get_char(str);
        } else {
            mp_raise_ValueError("second argument must be of type character");	
        }

        size_t height = MP_OBJ_SMALL_INT_VALUE(args[2]);
        size_t weight = MP_OBJ_SMALL_INT_VALUE(args[3]); // thickness of the segments
        if (height < 3*weight) {
            mp_raise_ValueError("height must be at least three times as large as weight");
        }
        size_t segment_length = (height-3*weight)/2; // TODO: this number is not necessarily an integer...
        mp_obj_tuple_t *tuple = MP_OBJ_TO_PTR(mp_obj_new_tuple(2, NULL));
        tuple->items[0] = MP_OBJ_NEW_SMALL_INT(height);
        // paint the whole canvas with the background colour
        if (digit == '.') {
            size_t width = weight;
            _fill_rectangle(mv, bg, 0, 0, width, height, width, height); // fill the whole canvas
            _fill_rectangle(mv, fg, 0, height-width, width, width, width, height);
            tuple->items[1] = MP_OBJ_NEW_SMALL_INT(width);
        } else {
            size_t width = 2*weight + segment_length;
            tuple->items[1] = MP_OBJ_NEW_SMALL_INT(width);
            _fill_rectangle(mv, bg, 0, 0, width, height, width, height); // fill the whole canvas
            if (digit == '-') {
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
            } else if (digit == '0') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom left
                _fill_rectangle(mv, fg, 0, 2*weight+segment_length, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '1') {
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '2') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom left
                _fill_rectangle(mv, fg, 0, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '3') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '4') {
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '5') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '6') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // bottom left
                _fill_rectangle(mv, fg, 0, 2*weight+segment_length, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '7') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '8') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom left
                _fill_rectangle(mv, fg, 0, 2*weight+segment_length, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            } else if (digit == '9') {
                // top segment
                _fill_rectangle(mv, fg, weight, 0, segment_length, weight, width, height);
                // middle segment
                _fill_rectangle(mv, fg, weight, segment_length+weight, segment_length, weight, width, height);
                // bottom segment
                _fill_rectangle(mv, fg, weight, height-weight, segment_length, weight, width, height);
                // top left
                _fill_rectangle(mv, fg, 0, weight, weight, segment_length, width, height);
                // top right
                _fill_rectangle(mv, fg, weight+segment_length, weight, weight, segment_length, width, height);
                // bottom right
                _fill_rectangle(mv, fg, weight+segment_length, 2*weight+segment_length, weight, segment_length, width, height);
            }
        }
        return MP_OBJ_FROM_PTR(tuple);
    }
    mp_raise_TypeError("wrong argument type");
}
