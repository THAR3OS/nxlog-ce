/* Automatically generated from xm_resolve2_-api.xml by codegen.pl */
#include "expr-xm_resolve2-funcproc.h"


/* FUNCTIONS */

// ipaddr_to_name
const char *nx_expr_func__xm_resolve2_ipaddr_to_name_string_argnames[] = {
    "address", 
};
nx_value_type_t nx_expr_func__xm_resolve2_ipaddr_to_name_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};

nx_expr_func_t nx_api_declarations_xm_resolve2_funcs[] = {
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "ipaddr_to_name",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_ipaddr_to_name,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_ipaddr_to_name_string_argnames,
   nx_expr_func__xm_resolve2_ipaddr_to_name_string_argtypes,
 },
};


nx_expr_proc_t nx_api_declarations_xm_resolve2_procs[] = {
};

nx_module_exports_t nx_module_exports_xm_resolve2 = {
	1,
	nx_api_declarations_xm_resolve2_funcs,
	0,
	nx_api_declarations_xm_resolve2_procs,
};
