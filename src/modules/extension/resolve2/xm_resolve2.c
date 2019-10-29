/*
 * This file is part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 * Website: http://nxlog.org
 * Author: Botond Botyanszki <botond.botyanszki@nxlog.org>
 */

#include "../../../common/module.h"
#include "../../../common/error_debug.h"
#include "xm_resolve2.h"

#define NX_LOGMODULE NX_LOGMODULE_MODULE

static void xm_resolve2_config(nx_module_t *module)
{
  const nx_directive_t *curr;
  nx_xm_resolve2_conf_t *modconf;
  int i;

  curr = module->directives;
  modconf = apr_pcalloc(module->pool, sizeof(nx_xm_resolve2_conf_t));
  module->config = modconf;
  nx_resolve2_ctx_init(&(modconf->ctx));

  while ( curr != NULL )
  {
    if ( nx_module_common_keyword(curr->directive) == TRUE )
    {
    }
    else if ( strcasecmp(curr->directive, "cacheexpiry") == 0 )
    {
      if ( (curr->args == NULL) || (curr->args[0] == '\0') )
      {
        nx_conf_error(curr, "CacheExpiry needs a parameter");
      }
      i = nx_resolve2_get_config_int(curr->args);
      if ( i == 0 )
      {
        nx_conf_error(curr, "invalid CacheExpiry parameter: %s", curr->args);
      }
      modconf->ctx.cacheexpiry = i;
    }
    else if ( strcasecmp(curr->directive, "cachelimit") == 0 )
    {
      if ( (curr->args == NULL) || (curr->args[0] == '\0') )
      {
        nx_conf_error(curr, "CacheLimit needs a parameter");
      }
      i = nx_resolve2_get_config_int(curr->args);
      if ( i == 0 )
      {
        nx_conf_error(curr, "invalid CacheConfig parameter: %s", curr->args);
      }
      modconf->ctx.cachelimit = i;
    }
    curr = curr->next;
  }
}

extern nx_module_exports_t nx_module_exports_xm_resolve2;

NX_MODULE_DECLARATION nx_xm_resolve2_module =
{
  NX_MODULE_API_VERSION,
  NX_MODULE_TYPE_EXTENSION,
  NULL,               // capabilities
  xm_resolve2_config, // config
  NULL,               // start
  NULL,               // stop
  NULL,               // pause
  NULL,               // resume
  NULL,               // init
  NULL,               // shutdown
  NULL,               // event
  NULL,               // info
  &nx_module_exports_xm_resolve2, //exports
};
