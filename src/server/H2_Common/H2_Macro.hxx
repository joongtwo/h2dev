/*
 * H2_Macro.hxx
 *
 *  Created on: Apr 4, 2023
 *      Author: Administrator
 */


#ifndef H2_CMACRO_HXX_
#define H2_CMACRO_HXX_


#define STR_CAST(X) const_cast<char*>(X)


#define H2_ERROR_REPORT(X) (H2_Error_Report(__FILE__,__LINE__, #X,(X)))

#define H2ITK(X) {							\
	int __ifail = ITK_ok;									\
	__ifail = H2_Error_Report(__FILE__,__LINE__, #X,(X)); 	\
	if (__ifail != ITK_ok) return __ifail; 					\
}

/* Object Print */
#define H2_PRINT_OBJECT(X) (H2_Print_Object(__FUNCTION__, __LINE__, #X, (X)))

/* Error Report */
#define H2_MEM_TCFREE(pMem) 		\
{									\
   if (pMem != NULL) {				\
	   MEM_free(pMem);				\
	   pMem = NULL;					\
   }								\
}

/* MEM Free */
#define H2_MEM_TCFREE2(n, pMem) 							\
{															\
	if(pMem != NULL) {										\
		for (int memIndex = 0; memIndex < n; memIndex++){	\
			H2_MEM_TCFREE(pMem[memIndex]);					\
		}													\
		H2_MEM_TCFREE(pMem);								\
	}														\
}

#define ECHO(...)									\
		TC_printf(__VA_ARGS__); 					\
		TC_write_syslog(__VA_ARGS__)


#define ECHO2(...)												\
		TC_printf("%s(%04d) : ", __FUNCTION__, __LINE__);		\
		TC_printf(__VA_ARGS__);									\
		TC_write_syslog("%s(%04d) : ", __FUNCTION__, __LINE__);	\
		TC_write_syslog(__VA_ARGS__)

#define ECHO3(...)	TC_printf(__VA_ARGS__)

#define ECHO4(...)	TC_printf("%s(%04d) : ", __FUNCTION__, __LINE__); TC_printf(__VA_ARGS__);

#define H2_EQUAL_STRING(s1, s2) 				((H2_IS_EMPTY_STRING(s1) && H2_IS_EMPTY_STRING(s2)) || (tc_strcmp((s1), (s2)) == 0))

#define H2_IS_EMPTY_STRING(s) 					(((void*)s) == NULL || tc_strlen((s)) == 0)

/* Error Report 출력 후 리턴 */
#define H2_ERROR_REPORT_RETURN(X) {										\
	int __ifail = ITK_ok;													\
	__ifail = H2_Error_Report(__FILE__,__LINE__, #X,(X)); 					\
	if (__ifail != ITK_ok) return __ifail; 									\
}

#endif /* SRC_SERVER_A4PMS_H2_MACRO_HXX_ */


