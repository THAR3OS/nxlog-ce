/*
 * xm_resolve2
 *
 * This file is NOT part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 *
 * Work on this module has been inspired by the documentation of the NXLog's Enterprise Module xm_resolver
 * Author: 2019 Stephan Seitz <s.seitz@mailbox.org>
 */

#ifndef __NX_RESOLVE2_H
#define __NX_RESOLVE2_H

#include "../../../common/types.h"
#include "../../../common/logdata.h"
#include "../../../common/module.h"

typedef struct nx_resolve2_ctx_t
{
    int cacheexpiry;
    int cachelimit;
} nx_resolve2_ctx_t;

void nx_resolve2_ctx_init(nx_resolve2_ctx_t *ctx);
char *ltrim(char *str, const char *seps);
char *rtrim(char *str, const char *seps);
char *trim(char *str, const char *seps);
int nx_resolve2_get_config_int(const char *str);

#endif /* __NX_RESOLVE2_H */
