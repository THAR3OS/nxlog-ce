/*
 * This file is part of the nxlog third-party extension
 * xm_resolve2.
 * License: GNU GPLv2
 * Website: http://github.com/BN4OSS
 * Author: Stephan Seitz <s.seitz@mailbox.org>
 */

#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#include "../../../common/module.h"
#include "../../../core/nxlog.h"
#include "xm_resolve2.h"

#define NX_LOGMODULE NX_LOGMODULE_CORE

/**
 * This function returns the first PTR record of a given host,
 * fqdn, IPv4 or IPv6 address.
 *
 * @example
 *  char *hostname = NULL;
 *  char *address = "1.2.3.4";
 *  if ((hostname = get_hostname_by_addr(address)) != NULL) {
 *    // do something
 *    free(hostname);
 *    }
 *
 * @oaran address
 *  a string containing a hostname, an fqdn, a IPv4 or a IPv6
 *  @returm
 *  a pointer to an char array, containg an fqdn. NULL on error.
 */
char *get_hostname_by_addr(char *address)
{
	int error;
	struct addrinfo *res, *resorig, hints;
	char host[NI_MAXHOST], numhost[NI_MAXHOST];
  char *hostname;

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
  hostname = NULL;

  if ((error = getaddrinfo(address, NULL, &hints, &res)) != 0)
  {
    printf("%s",
        gai_strerror(error));
  } else {
    for (resorig = res; res != NULL; res = res->ai_next)
    {
      if ((error = getnameinfo(res->ai_addr, res->ai_addrlen,
              numhost, sizeof (numhost), NULL, 0, NI_NUMERICHOST)) != 0)
      {
        printf("%s",
            gai_strerror(error));
      } else if ((error = getnameinfo(res->ai_addr, res->ai_addrlen,
          host, sizeof (host), NULL, 0, 0)) != 0)
      {
        printf("%s",
            gai_strerror(error));
      } else {
        hostname = malloc(sizeof(host));
        strcpy(hostname,host);
        break; // return only the first PTR if more than one exists.
      }
    }
	  freeaddrinfo(resorig);
  }
	return hostname;
}

void nx_expr_func__xm_resolve2_ipaddr_to_name(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  char *ipaddr;
  char *hostname;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if ( (args[0].type != NX_VALUE_TYPE_STRING) &&
      (args[0].type != NX_VALUE_TYPE_IP4ADDR) &&
      (args[0].type != NX_VALUE_TYPE_IP6ADDR) )
  {
    throw_msg("'%s' type argument is invalid. allowed types are '%s', '%s' and '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING),
        nx_value_type_to_string(NX_VALUE_TYPE_IP4ADDR),
        nx_value_type_to_string(NX_VALUE_TYPE_IP6ADDR));
  }

  retval->type = NX_VALUE_TYPE_STRING;
  if ( args[0].defined == FALSE )
  {
    retval->defined = FALSE;
    return;
  }

  switch (args[0].type)
  {
    case NX_VALUE_TYPE_STRING:
      ipaddr = args[0].string->buf;
      break;
    case NX_VALUE_TYPE_IP4ADDR:
    case NX_VALUE_TYPE_IP6ADDR:
      ipaddr = nx_value_to_string(&args[0]);
      break;
    default:
      ipaddr = NULL;
  }

  if ( ipaddr == NULL )
  {
    retval->defined = FALSE;
    return;
  }
  if ((hostname = get_hostname_by_addr(ipaddr)) != NULL)
  {
    retval->string = nx_string_create(hostname, -1);
  } else {
    retval->string = nx_string_create(ipaddr, -1);
  }
  retval->defined = TRUE;
}
