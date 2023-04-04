/*
 * H2_Constants.hxx
 *
 *  Created on: Apr 4, 2023
 *      Author: Administrator
 */

#ifndef H2_CONSTANTS_HXX_
#define H2_CONSTANTS_HXX_


/**
 * Custom Item
 */
#define H2_ITEM                      	"H2_Item"
#define H2_ITEM_REV                     "H2_ItemRevision"


/**
 * Schedule Manager
 */
#define SCHEDULE_TASK					"ScheduleTask"


/**
 * Schedule Property
 */
#define SCHD_START_DATE				"start_date"
#define SCHD_FINISH_DATE			"finish_date"
#define SCHD_ACT_START_DATE			"actual_start_date"
#define SCHD_ACT_FINISH_DATE		"actual_finish_date"


/**
 * Schedule Task
 */
#define	SCHTASK_TYPE_NORMAL		0
#define SCHTASK_TYPE_SUMMARY	2
#define SCHTASK_TYPE_PHASE		3
#define SCHTASK_TYPE_GATE		4
#define SCHTASK_TYPE_SCHSUMMARY  6
#define SCHTASK_TASK_DEPENDENCY	"TaskDependency"


/**
 * Object Type
 */
#define ITEM_ID						"item_id"
#define OBJECT_NAME					"object_name"
#define OBJECT_TYPE					"object_type"
#define OBJECT_DESC					"object_desc"

#endif /* SRC_SERVER_H2_COMMON_H2_CONSTANTS_HXX_ */
