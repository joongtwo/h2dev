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
 *   This file contains the implementation for the Extension H2_PartCreateAction
 *
 */
#include <H2_Part/H2_PartCreateAction.hxx>
#include <metaframework/CreateInput.hxx>
#include <H2_Common/H2_Common.hxx>

int H2_PartCreateAction( METHOD_message_t * /*msg*/, va_list args )
{
	int ifail = ITK_ok;
	TC_printf("-------------------------\n");
	TC_printf("H2_Part create post\n");
	TC_printf("-------------------------\n");

	va_list largs;
	va_copy(largs, args);
	Teamcenter::CreateInput *creInput = va_arg(largs, Teamcenter::CreateInput*);

	va_end(largs);

	std::string id = "";
	bool isNull = false;
	ifail = creInput->getString("item_id", id, isNull);


	TC_printf("-------------------------\n");
	TC_printf("  ID = %s  \n", id.c_str());
	TC_printf("-------------------------\n");

	return ifail;
}
