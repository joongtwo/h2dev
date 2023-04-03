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
 *   This file contains the declaration for the Extension H2_Common
 *
 */
 
#ifndef H2_COMMON_HXX
#define H2_COMMON_HXX
#include <tccore/method.h>
#include <tccore/method.h>
#include <tc/tc_util.h>
#include <ug_va_copy.h>
#include <tccore/tctype.h>
#include <tccore/aom.h>
#include <tccore/releasestatus.h>
#include <tccore/aom_prop.h>
#include <tccore/grm.h>
#include <tccore/item.h>
#include <sa/sa.h>
#include <tc/preferences.h>
#include <string>
#include <fclasses/tc_date.h>
#include <vector>
#include <tccore/workspaceobject.h>

#include <qry/qry.h>
#include <schmgt/schmgt_bridge_itk.h>
#include <schmgt/schmgt_itk.h>
#include <res/res_itk.h>
#include <sa/user.h>
#include <tccore/aom.h>
#include <H2_Common/libh2_common_exports.h>
#ifdef __cplusplus
         extern "C"{
#endif
                 
extern H2_COMMON_API int H2_Common(METHOD_message_t* msg, va_list args);
                 
#ifdef __cplusplus
                   }
#endif
                
#include <H2_Common/libh2_common_undef.h>
                
#endif  // H2_COMMON_HXX
