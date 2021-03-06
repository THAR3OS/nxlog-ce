/* Automatically generated from xm_resolve2-api.xml by codegen.pl */
#include "expr-xm_resolve2-funcproc.h"


/* FUNCTIONS */

// gid_to_name
const char *nx_expr_func__xm_resolve2_gid_to_name_integer_argnames[] = {
    "gid", 
};
nx_value_type_t nx_expr_func__xm_resolve2_gid_to_name_integer_argtypes[] = {
    NX_VALUE_TYPE_INTEGER, 
};
// gid_to_name
const char *nx_expr_func__xm_resolve2_gid_to_name_string_argnames[] = {
    "gid", 
};
nx_value_type_t nx_expr_func__xm_resolve2_gid_to_name_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// group_get_gid
const char *nx_expr_func__xm_resolve2_group_get_gid_string_argnames[] = {
    "groupname", 
};
nx_value_type_t nx_expr_func__xm_resolve2_group_get_gid_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// ipaddr_to_name
const char *nx_expr_func__xm_resolve2_ipaddr_to_name_string_argnames[] = {
    "ipaddr", 
};
nx_value_type_t nx_expr_func__xm_resolve2_ipaddr_to_name_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// name_to_ipaddr
const char *nx_expr_func__xm_resolve2_name_to_ipaddr_string_argnames[] = {
    "name", 
};
nx_value_type_t nx_expr_func__xm_resolve2_name_to_ipaddr_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// uid_to_name
const char *nx_expr_func__xm_resolve2_uid_to_name_integer_argnames[] = {
    "uid", 
};
nx_value_type_t nx_expr_func__xm_resolve2_uid_to_name_integer_argtypes[] = {
    NX_VALUE_TYPE_INTEGER, 
};
// uid_to_name
const char *nx_expr_func__xm_resolve2_uid_to_name_string_argnames[] = {
    "uid", 
};
nx_value_type_t nx_expr_func__xm_resolve2_uid_to_name_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// user_get_gid
const char *nx_expr_func__xm_resolve2_user_get_gid_string_argnames[] = {
    "username", 
};
nx_value_type_t nx_expr_func__xm_resolve2_user_get_gid_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};
// user_get_uid
const char *nx_expr_func__xm_resolve2_user_get_uid_string_argnames[] = {
    "username", 
};
nx_value_type_t nx_expr_func__xm_resolve2_user_get_uid_string_argtypes[] = {
    NX_VALUE_TYPE_STRING, 
};

nx_expr_func_t nx_api_declarations_xm_resolve2_funcs[] = {
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "gid_to_name",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_gid_to_name,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_gid_to_name_integer_argnames,
   nx_expr_func__xm_resolve2_gid_to_name_integer_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "gid_to_name",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_gid_to_name,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_gid_to_name_string_argnames,
   nx_expr_func__xm_resolve2_gid_to_name_string_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "group_get_gid",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_group_get_gid,
   NX_VALUE_TYPE_INTEGER,
   1,
   nx_expr_func__xm_resolve2_group_get_gid_string_argnames,
   nx_expr_func__xm_resolve2_group_get_gid_string_argtypes,
 },
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
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "name_to_ipaddr",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_name_to_ipaddr,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_name_to_ipaddr_string_argnames,
   nx_expr_func__xm_resolve2_name_to_ipaddr_string_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "uid_to_name",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_uid_to_name,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_uid_to_name_integer_argnames,
   nx_expr_func__xm_resolve2_uid_to_name_integer_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "uid_to_name",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_uid_to_name,
   NX_VALUE_TYPE_STRING,
   1,
   nx_expr_func__xm_resolve2_uid_to_name_string_argnames,
   nx_expr_func__xm_resolve2_uid_to_name_string_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "user_get_gid",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_user_get_gid,
   NX_VALUE_TYPE_INTEGER,
   1,
   nx_expr_func__xm_resolve2_user_get_gid_string_argnames,
   nx_expr_func__xm_resolve2_user_get_gid_string_argtypes,
 },
 {
   { .next = NULL, .prev = NULL },
   NULL,
   "user_get_uid",
   NX_EXPR_FUNCPROC_TYPE_GLOBAL,
   nx_expr_func__xm_resolve2_user_get_uid,
   NX_VALUE_TYPE_INTEGER,
   1,
   nx_expr_func__xm_resolve2_user_get_uid_string_argnames,
   nx_expr_func__xm_resolve2_user_get_uid_string_argtypes,
 },
};

nx_module_exports_t nx_module_exports_xm_resolve2 = {
	9,
	nx_api_declarations_xm_resolve2_funcs,
	0,
	NULL,
};
