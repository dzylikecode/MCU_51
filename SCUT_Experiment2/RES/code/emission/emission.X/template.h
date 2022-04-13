/* Microchip Technology Inc. and its subsidiaries.  You may use this software
 * and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */

/*
 * File:
 * Author:
 * Comments:
 * Revision history:
 */

// This is a guard condition so that contents of this file are not included
// more than once.
#ifndef XC_HEADER_TEMPLATE_H
#define XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>

    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>

    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage
// live documentation

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C
    // linkage so the functions can be used by the c code.

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XC_HEADER_TEMPLATE_H */

#ifdef Set_Byte_Logical
#ifndef X0
#error "X0 not defined"
#endif
#ifndef X1
#error "X1 not defined"
#endif
#ifndef X2
#error "X2 not defined"
#endif
#ifndef X3
#error "X3 not defined"
#endif
#ifndef X4
#error "X4 not defined"
#endif
#ifndef X5
#error "X5 not defined"
#endif
#ifndef X6
#error "X6 not defined"
#endif
#ifndef X7
#error "X7 not defined"
#endif



#include "port.h"
void Set_Byte_Logical(uint8_t value)
{
#ifdef FLIP
    value = ~value;
#else

#endif
    set_pin(X0, value & 0x01);
    set_pin(X1, (value & 0x02) >> 1);
    set_pin(X2, (value & 0x04) >> 2);
    set_pin(X3, (value & 0x08) >> 3);
    set_pin(X4, (value & 0x10) >> 4);
    set_pin(X5, (value & 0x20) >> 5);
    set_pin(X6, (value & 0x40) >> 6);
    set_pin(X7, (value & 0x80) >> 7);

}

#undef FLIP
#undef Set_Byte_Logical
#undef X0
#undef X1
#undef X2
#undef X3
#undef X4
#undef X5
#undef X6
#undef X7
#endif
