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

#include <H2_Common/H2_Macro.hxx>
#include <H2_Common/H2_Constants.hxx>

#include <H2_Common/libh2_common_exports.h>
#ifdef __cplusplus
         extern "C"{
#endif
                 
extern H2_COMMON_API int H2_Error_Report(const char *pcFile, int iLine, const char *pcFunction, int iReturnCode);

extern H2_COMMON_API int H2_Print_Object(const char *func, int line, const char* var, tag_t tag);

extern H2_COMMON_API long totalDay(int y, int m, int d);

extern H2_COMMON_API tag_t H2_GetTypeTag(const char* typeName);

extern H2_COMMON_API logical H2_IsTypeOf(const tag_t tObj, const char* typeName);

extern H2_COMMON_API logical H2_IsTypeOfStr(const char* objectType, const char* typeName);

extern H2_COMMON_API tag_t H2_GetRelationTypeTag(const char* relationTypeName);

extern H2_COMMON_API int H2_GetPrimaryObjectVector(const tag_t secondaryObject, const char* relationName, std::vector<tag_t> & values, std::vector<int> & isNull);

extern H2_COMMON_API int H2_execute_saved_query2(const char* qryName, int entry_num, char **changed_entrys, char **changed_values, int *count, tag_t** resutls);

extern H2_COMMON_API int H2_execute_saved_query(const char* qryName, int entry_num, char **changed_entrys, char **changed_values, int *count, tag_t** resutls);

extern H2_COMMON_API int getSubTasks(const tag_t tScheduleTask);

extern H2_COMMON_API tag_t H2_get_relation_type_tag(const char* relation_type_name);

extern H2_COMMON_API int H2_delete_relation2(const tag_t primay, const tag_t seconday, const char* relType);

extern H2_COMMON_API int H2_create_relation2(const tag_t primay, const tag_t seconday, const char* relType);

extern H2_COMMON_API int H2_ChangeOwnership(tag_t targetTag, tag_t userTag);

extern H2_COMMON_API logical H2_IsObjectInProcess(tag_t objecTag);

extern H2_COMMON_API logical H2_IsObjectReleased(tag_t objecTag);

extern H2_COMMON_API tag_t getDelDocRevFromSchTask(tag_t scheduleTaskTag);

extern H2_COMMON_API logical isDBA();

extern H2_COMMON_API logical isBypass();

#ifdef __cplusplus
                   }
#endif
                
#include <H2_Common/libh2_common_undef.h>
                
#endif  // H2_COMMON_HXX
