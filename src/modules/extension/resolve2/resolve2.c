/*
 * xm_resolve2
 *
 * This file is NOT part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 *
 * Work on this module has been inspired by the documentation of the NXLog's Enterprise Module xm_resolver
 * Author: 2019 Stephan Seitz <s.seitz@mailbox.org>
 */

#include <string.h>
#include <stdlib.h>

#include "../../../common/error_debug.h"
#include "../../../common/exception.h"
#include "resolve2.h"

#define NX_LOGMODULE NX_LOGMODULE_MODULE

void nx_resolve2_ctx_init(nx_resolve2_ctx_t *ctx)
{
  ASSERT(ctx != NULL);

  ctx->cacheexpiry = 3600;
  ctx->cachelimit = 100000;;
}

char *ltrim(char *str, const char *seps)
{
  size_t totrim;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  totrim = strspn(str, seps);
  if (totrim > 0)
  {
    size_t len = strlen(str);
    if (totrim == len)
    {
      str[0] = '\0';
    }
    else {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
  return str;
}

char *rtrim(char *str, const char *seps)
{
  int i;
  if (seps == NULL)
  {
    seps = "\t\n\v\f\r ";
  }
  i = strlen(str) - 1;
  while (i >= 0 && strchr(seps, str[i]) != NULL)
  {
    str[i] = '\0';
    i--;
  }
  return str;
}

char *trim(char *str, const char *seps)
{
  return ltrim(rtrim(str, seps), seps);
}

int nx_resolve2_get_config_int(const char *str)
{
  int retval;
  char *s;

  ASSERT(str != NULL);

  // trim control chars, white spaces and quotes from the parameter
  s = trim(str, "\t\n\v\f\r\" ");
  retval = atoi(s);
  return ( retval );
}
