//@<COPYRIGHT>@
//==================================================
//Copyright $2023.
//Siemens Product Lifecycle Management Software Inc.
//All Rights Reserved.
//==================================================
//@<COPYRIGHT>@

/* 
 * @file 
 *
 *   This file contains the declaration for the Extension H2_PartCreateAction
 *
 */
 
#ifndef H2_PARTCREATEACTION_HXX
#define H2_PARTCREATEACTION_HXX
#include <tccore/method.h>
#include <H2_Part/libh2_part_exports.h>
#ifdef __cplusplus
         extern "C"{
#endif
                 
extern H2_PART_API int H2_PartCreateAction(METHOD_message_t* msg, va_list args);
                 
#ifdef __cplusplus
                   }
#endif
                
#include <H2_Part/libh2_part_undef.h>
                
#endif  // H2_PARTCREATEACTION_HXX
