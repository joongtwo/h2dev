//@<COPYRIGHT>@
//==================================================
//Copyright $2023.
//Siemens Product Lifecycle Management Software Inc.
//All Rights Reserved.
//==================================================
//@<COPYRIGHT>@


#include <common/library_indicators.h>

#if !defined(EXPORTLIBRARY)
#   error EXPORTLIBRARY is not defined
#endif

#undef EXPORTLIBRARY

#if !defined(LIBH2_COMMON) && !defined(IPLIB)
#   error IPLIB or LIBH2_COMMON is not defined
#endif

#undef H2_COMMON_API
#undef H2_COMMONEXPORT
#undef H2_COMMONGLOBAL
#undef H2_COMMONPRIVATE
