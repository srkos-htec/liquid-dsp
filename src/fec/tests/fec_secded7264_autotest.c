/*
 * Copyright (c) 2011 Joseph Gaeddert
 * Copyright (c) 2011 Virginia Polytechnic Institute & State University
 *
 * This file is part of liquid.
 *
 * liquid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * liquid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with liquid.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>

#include "autotest/autotest.h"
#include "liquid.internal.h"

//
// AUTOTEST: SEC-DEC (72,64) codec (no errors)
//
void autotest_secded7264_codec_e0()
{
    // arrays
    unsigned char sym_org[8];   // original symbol
    unsigned char sym_enc[9];   // encoded symbol
    unsigned char sym_dec[8];   // decoded symbol

    // generate symbol
    sym_org[0] = rand() & 0xff;
    sym_org[1] = rand() & 0xff;
    sym_org[2] = rand() & 0xff;
    sym_org[3] = rand() & 0xff;
    sym_org[4] = rand() & 0xff;
    sym_org[5] = rand() & 0xff;
    sym_org[6] = rand() & 0xff;
    sym_org[7] = rand() & 0xff;

    // encoded symbol
    fec_secded7264_encode_symbol(sym_org, sym_enc);

    // decoded symbol
    fec_secded7264_decode_symbol(sym_enc, sym_dec);

    // validate data are the same
    CONTEND_EQUALITY(sym_org[0], sym_dec[0]);
    CONTEND_EQUALITY(sym_org[1], sym_dec[1]);
    CONTEND_EQUALITY(sym_org[2], sym_dec[2]);
    CONTEND_EQUALITY(sym_org[3], sym_dec[3]);
    CONTEND_EQUALITY(sym_org[4], sym_dec[4]);
    CONTEND_EQUALITY(sym_org[5], sym_dec[5]);
    CONTEND_EQUALITY(sym_org[6], sym_dec[6]);
    CONTEND_EQUALITY(sym_org[7], sym_dec[7]);
}

//
// AUTOTEST: SEC-DEC (72,64) codec (single error)
//
void autotest_secded7264_codec_e1()
{
    // arrays
    unsigned char sym_org[8];   // original symbol
    unsigned char sym_enc[9];   // encoded symbol
    unsigned char e[9];         // error vector
    unsigned char sym_rec[9];   // received symbol
    unsigned char sym_dec[8];   // decoded symbol

    unsigned int i;
    unsigned int k; // error location

    for (k=0; k<72; k++) {
        // generate symbol
        for (i=0; i<8; i++)
            sym_org[i] = rand() & 0xff;

        // encoded symbol
        fec_secded7264_encode_symbol(sym_org, sym_enc);

        // generate error vector (single error)
        for (i=0; i<9; i++)
            e[i] = 0;
        div_t d = div(k,8);
        e[9-d.quot-1] = 1 << d.rem;   // flip bit at index k

        // received symbol
        for (i=0; i<9; i++)
            sym_rec[i] = sym_enc[i] ^ e[i];

        // decoded symbol
        fec_secded7264_decode_symbol(sym_rec, sym_dec);

        // validate data are the same
        for (i=0; i<8; i++)
            CONTEND_EQUALITY(sym_org[i], sym_dec[i]);
    }
}

