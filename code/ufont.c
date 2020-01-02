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

#include "ufont_rectangle.h"
#include "ufont_seven_segment.h"
#include "ufont_renderer.h"

#define UFONT_VERSION 0.99

typedef struct _mp_obj_float_t {
    mp_obj_base_t base;
    mp_float_t value;
} mp_obj_float_t;

mp_obj_float_t ufont_version = {{&mp_type_float}, UFONT_VERSION};

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ufont_seven_segment_obj, 6, 6, ufont_seven_segment);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ufont_fill_rectangle_obj, 8, 8, ufont_fill_rectangle);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(ufont_render_obj, 5, 5, ufont_render);

STATIC const mp_map_elem_t ufont_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_ufont) },
    { MP_ROM_QSTR(MP_QSTR___version__), MP_ROM_PTR(&ufont_version) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_fill_rectangle), (mp_obj_t)&ufont_fill_rectangle_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_seven_segment), (mp_obj_t)&ufont_seven_segment_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_render), (mp_obj_t)&ufont_render_obj }
};

STATIC MP_DEFINE_CONST_DICT (
    mp_module_ufont_globals,
    ufont_globals_table
);

const mp_obj_module_t ufont_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_ufont_globals,
};

MP_REGISTER_MODULE(MP_QSTR_ufont, ufont_user_cmodule, MODULE_UFONT_ENABLED);
