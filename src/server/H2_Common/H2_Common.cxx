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
 *   This file contains the implementation for the Extension Common
 *
 */
#include <H2_Common/H2_Common.hxx>

/*
 *  H2_ERROR_REPORT 에서 사용하는 함수로 Error 일경우에 내용을 출력함.
 */
int H2_Error_Report(const char *pcFile, int iLine, const char *pcFunction, int iReturnCode) {
	if (iReturnCode != ITK_ok) {
		char *pcErrorMsgString;
		ECHO2("----------------------------------------------------------\n");
		ECHO2("\n\n\tReturn Code=%d", iReturnCode);
		EMH_ask_error_text(iReturnCode, &pcErrorMsgString);
		ECHO2("\n\n\tError_Msg_String=%s\n", pcErrorMsgString);
		ECHO2("\tFUNCTION: %s\t\nFILE: %s \t\nLINE: %d\n", pcFunction, pcFile, iLine);
		ECHO2("----------------------------------------------------------\n");
		H2_MEM_TCFREE(pcErrorMsgString);
		return iReturnCode;
	}
	return ITK_ok;
}


/*
 * Object의 유형명을 얻는다.
 */
int H2_Print_Object(const char *func, int line, const char* var, tag_t tag) {
	char *type_name = NULL;
	char *displayTypeName = NULL;
	tag_t inTypeTag = NULLTAG;
	tag_t type_tag = NULLTAG;
	tag_t parent_type_tag = NULLTAG;
	logical isTypeTag = false;
	char* objectString = NULL;

	if (TCTYPE_ask_parent_type(tag, &parent_type_tag) != ITK_ok) {
		EMH_clear_errors();
	}
	isTypeTag = parent_type_tag != NULLTAG;

	if (isTypeTag) {
		inTypeTag = tag;
		TCTYPE_ask_name2(tag, &type_name);
	} else {
		TCTYPE_ask_object_type(tag, &type_tag);
		inTypeTag = type_tag;
		TCTYPE_ask_name2(type_tag, &type_name);
	}
	TCTYPE_ask_display_name(inTypeTag, &displayTypeName);
	AOM_ask_value_string(tag, "object_string", &objectString);

	ECHO2("---------------------------------------------------------\n");
	ECHO2("PRINT OBJECT : %s(%d)\n", func, line);
	ECHO2("---------------------------------------------------------\n");
	ECHO2(" VAR NAME          : %s\n", var);
	ECHO2(" OBJECT_TAG        : %d\n", tag);
	ECHO2(" IS TYPE TAG       : %s\n", isTypeTag? "YES":"NO");
	ECHO2(" TYPE NAME         : %s\n", type_name);
	ECHO2(" DISPLAY TYPE NAME : %s\n", displayTypeName);
	ECHO2(" DISPLAY OBJ STR   : %s\n", objectString);
	ECHO2("---------------------------------------------------------\n");
	H2_MEM_TCFREE(type_name);
	H2_MEM_TCFREE(displayTypeName);
	H2_MEM_TCFREE(objectString);
	return ITK_ok;
}

///
/// 1년 1월 1일 부터 입력된 날짜사이의 일자를 반환하는 함수
/// @param y - Year (2020)
/// @param m - Month (12)
/// @day d - Day (31)
/// @return - 날짜 수
///
long totalDay(int y, int m, int d)
{
	int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int i;
	long total = 0L;
	total = (y-1)*365L + (y-1)/4-(y-1)/100+(y-1)/400;

	if(!(y%4) && y%100 || !(y%400))
		months[1]++;

	for(i=0; i<m-1; i++)
		total += months[i];

	total +=d;
	return total;
}

/**
 * Get Type Tag with Type Name
 */
tag_t H2_GetTypeTag(const char* typeName) {
	tag_t tType = NULLTAG;
	H2_ERROR_REPORT(TCTYPE_find_type ( typeName, NULL, &tType));
	return tType;
}

/**
 * Check whether Object type name is input type name
 */
logical H2_IsTypeOf(const tag_t tObj, const char* typeName) {
	logical bIsTypeOf = false;
	tag_t tType = NULLTAG;
	tag_t parent_type_tag = NULLTAG;

	if (TCTYPE_ask_parent_type(tObj, &parent_type_tag) == ITK_ok) {
		tType = tObj;
	} else {
		EMH_clear_errors();
		if (TCTYPE_ask_object_type(tObj, &tType) != ITK_ok) {
			EMH_clear_errors();
		}
	}
	H2_ERROR_REPORT(TCTYPE_is_type_of (tType, H2_GetTypeTag(typeName), &bIsTypeOf));
	return bIsTypeOf;
}

logical H2_IsTypeOfStr(const char* objectType, const char* typeName) {
	tag_t objType = NULLTAG;
	H2_ERROR_REPORT(TCTYPE_ask_type(objectType, &objType));

	logical isParenType = false;
	H2_ERROR_REPORT(TCTYPE_is_type_of(objType, H2_GetTypeTag(typeName), &isParenType));
	return isParenType;
}

/**
 * Get relation Type Tag with relation Name
 */
tag_t H2_GetRelationTypeTag(const char* relationTypeName) {
	tag_t relationType = NULLTAG;
	H2_ERROR_REPORT(GRM_find_relation_type(relationTypeName, &relationType));
	return relationType;
}

/**
 * Get primary Objects
 */
int H2_GetPrimaryObjectVector(const tag_t secondaryObject, const char* relationName, std::vector<tag_t> & values, std::vector<int> & isNull) {
	int count = 0;
	tag_t* objs = NULL;
	H2_ERROR_REPORT(GRM_list_primary_objects_only(secondaryObject, H2_GetRelationTypeTag(relationName), &count, &objs));
	for (int i = 0; i < count; i++) {
		values.push_back(objs[i]);
		isNull.push_back(objs[i] == NULLTAG );
	}
	H2_MEM_TCFREE(objs);
	return ITK_ok;
}


int H2_execute_saved_query2(const char* qryName, int entry_num, char **changed_entrys, char **changed_values, int *count, tag_t** resutls) {
	tag_t qry = NULLTAG;
	int entry_count = 0;
	char** entries = NULL;
	char** values = NULL;
	char** copy_values = NULL;

	H2_ERROR_REPORT_RETURN(QRY_find2(qryName, &qry));
	H2_ERROR_REPORT_RETURN(QRY_find_user_entries(qry, &entry_count, &entries, &values));
	copy_values = (char **) MEM_alloc(sizeof(char*) * entry_count);
	for (int i = 0; i < entry_count; i++) {
		copy_values[i] = MEM_string_copy(values[i]);
	}

	for (int i = 0; i < entry_count; i++) {
		for (int j = 0; j < entry_num; j++) {
			if (H2_EQUAL_STRING(entries[i], changed_entrys[j])) {
				H2_MEM_TCFREE(copy_values[i]);
				copy_values[i] = MEM_string_copy(changed_values[j]);
			}
		}
	}

	ECHO2("\n::entries 1::%s::\n", entries[0]);
	ECHO2("\n::values 1::%s::\n", copy_values[0]);

	H2_ERROR_REPORT_RETURN(QRY_execute(qry, entry_count, entries, changed_values, count, resutls));
	H2_MEM_TCFREE(entries);
	H2_MEM_TCFREE(values);
	H2_MEM_TCFREE(copy_values);
	return ITK_ok;
}

int H2_execute_saved_query(const char* qryName, int entry_num, char **changed_entrys, char **changed_values, int *count, tag_t** resutls) {
	tag_t qry = NULLTAG;

	H2_ERROR_REPORT_RETURN(QRY_find2(qryName, &qry));
	H2_ERROR_REPORT(QRY_execute(qry, entry_num, changed_entrys, changed_values, count, resutls));

	return ITK_ok;
}


int getSubTasks(const tag_t tScheduleTask)
{
	tag_t *tSubTasks = NULL;
	int subtask_count = 0;

	H2_ERROR_REPORT(AOM_ask_value_tags(tScheduleTask, "child_task_taglist", &subtask_count, &tSubTasks));

	for (int i=0;i<subtask_count;i++)
	{
		tag_t tSubTask = NULLTAG;
		char* strObjectName = NULL;

		tSubTask = tSubTasks[i];

		H2_ERROR_REPORT(AOM_ask_value_string(tSubTask, "object_name", &strObjectName));

		ECHO2("\n::Object name::%s::\n", strObjectName);

		H2_ERROR_REPORT(getSubTasks(tSubTask));

		H2_MEM_TCFREE(strObjectName);
	}

	H2_MEM_TCFREE(tSubTasks);

	return ITK_ok;
}

tag_t H2_get_relation_type_tag(const char* relation_type_name) {
	tag_t relation_type = NULLTAG;
	H2_ERROR_REPORT(GRM_find_relation_type(relation_type_name, &relation_type));
	return relation_type;
}

/* Delete Relation (by Relation Typye Name) */
int H2_delete_relation2(const tag_t primay, const tag_t seconday, const char* relType) {
	tag_t relation = NULLTAG;
	tag_t relationType = H2_get_relation_type_tag(relType);
	H2_ERROR_REPORT_RETURN(GRM_find_relation(primay, seconday, relationType, &relation));
	if(relation != NULL){
		H2_ERROR_REPORT_RETURN(GRM_delete_relation(relation));
	}
	return ITK_ok;
}

/* Relation을 생성함.(by Relation Typye Name) */
int H2_create_relation2(const tag_t primay, const tag_t seconday, const char* relType) {
	tag_t relation = NULLTAG;
	tag_t relationType = H2_get_relation_type_tag(relType);
	H2_ERROR_REPORT_RETURN(GRM_create_relation(primay, seconday, relationType, NULLTAG, &relation));
	H2_ERROR_REPORT_RETURN(GRM_save_relation(relation));
	return ITK_ok;
}

/**
 * change the user and group ownership for targetTag to new user
 */
int H2_ChangeOwnership(tag_t targetTag, tag_t userTag)
{
	tag_t   groupTag = NULLTAG;
	// get Group of user  being changed
	H2_ERROR_REPORT(SA_ask_user_login_group(userTag, &groupTag));
	//change owner of target object to user  being changed
	H2_ERROR_REPORT(AOM_set_ownership(targetTag, userTag , groupTag));
	return ITK_ok;
}

/**
 * check if object is currently in process
 */
logical H2_IsObjectInProcess(tag_t objecTag)
{
    logical isInProcess = false;
	int nTasks = 0;
	tag_t* taskTags;
	H2_ERROR_REPORT(AOM_ask_value_tags(objecTag, "process_stage_list", &nTasks, &taskTags));
	if (nTasks > 0)
		isInProcess = true;

    return isInProcess;
}

/**
 * check if object was currently released.
 */
logical H2_IsObjectReleased(tag_t objecTag)
{
	logical isReleased = false;
	tag_t* relTags = NULL;
	int nRelTags = 0;
	H2_ERROR_REPORT(WSOM_ask_release_status_list(objecTag, &nRelTags, &relTags));
	isReleased = nRelTags >0;
	H2_MEM_TCFREE(relTags);
	return isReleased;
}

/**
 * Get Project Doc Revision form Schedule Task
 */
tag_t getDelDocRevFromSchTask(tag_t scheduleTaskTag)
{
	tag_t  projectDocRevTag = NULLTAG;	//Project Doc Revision
	tag_t* deliverablesTags = NULLTAG; 	// Deliverables List
	tag_t  deliverableTag = NULLTAG;	//Deliverable
	tag_t  deliverInsTag = NULLTAG; 	// Deliverable Instance

	int deliverCnt = 0;      			// Deliverables Count

	H2_ERROR_REPORT(AOM_ask_value_tags(scheduleTaskTag, "sch_task_deliverable_list", &deliverCnt, &deliverablesTags));

	if(deliverCnt == 0)
	{
		H2_MEM_TCFREE(deliverablesTags);
		return NULLTAG;
	}

	for(int i = 0; i < deliverCnt; i++ )
	{
		deliverableTag = deliverablesTags[i];
		break;
	}

	H2_ERROR_REPORT(AOM_ask_value_tag(deliverableTag, "fnd0DeliverableInstance", &deliverInsTag));

	if(deliverInsTag == NULLTAG)
	{
		H2_MEM_TCFREE(deliverablesTags);
		return NULLTAG;
	}

//	if(!H2_IsTypeOf(deliverInsTag, H2_PROJECT_DOC))
//	{
//		H2_MEM_TCFREE(deliverablesTags);
//		return NULLTAG;
//	}

	H2_ERROR_REPORT(ITEM_ask_latest_rev(deliverInsTag, &projectDocRevTag));

	H2_MEM_TCFREE(deliverablesTags);

	return projectDocRevTag;
}

logical isDBA(){
	tag_t grMember = NULLTAG;
	int is_dba = false;
	tag_t group_tag = NULLTAG;
	SA_ask_current_groupmember(&grMember);
	SA_ask_groupmember_group(grMember, &group_tag);
//	SA_ask_groupmember_group_priv(grMember, &is_dba);

	SA_ask_group_system_priv(group_tag, &is_dba);
	return is_dba != 0;
}

logical isBypass(){

	if(!isDBA()){
		return false;
	}

	logical isBypass = false;
	ITK_ask_bypass(&isBypass);

	return isBypass;
}
