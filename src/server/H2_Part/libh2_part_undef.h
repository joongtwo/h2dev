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

#if !defined(LIBH2_PART) && !defined(IPLIB)
#   error IPLIB or LIBH2_PART is not defined
#endif

#undef H2_PART_API
#undef H2_PARTEXPORT
#undef H2_PARTGLOBAL
#undef H2_PARTPRIVATE
