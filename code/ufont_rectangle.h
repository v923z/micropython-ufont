/*
 * This file is part of the micropython-ufont project, 
 *
 * https://github.com/v923z/micropython-ufont
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Zoltán Vörös
*/
    
#ifndef _UFONT_RECTANGLE_
#define _UFONT_RECTANGLE_

mp_obj_t ufont_fill_rectangle(size_t , const mp_obj_t *);
mp_obj_t _fill_rectangle(mp_obj_t , mp_obj_t , size_t , size_t , size_t , size_t , size_t , size_t );

#endif
