/*
 * xm_resolve2
 *
 * This file is NOT part of the nxlog log collector tool.
 * See the file LICENSE in the source root for licensing terms.
 *
 * Work on this module has been inspired by the documentation of the NXLog's Enterprise Module xm_resolver
 * Author: 2019 Stephan Seitz <s.seitz@mailbox.org>
 */

#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
char *_get_hostname_by_addr(char *address)
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
     throw_msg("getaddrinfo: '%s'", gai_strerror(error));
  } else {
    for (resorig = res; res != NULL; res = res->ai_next)
    {
      if ((error = getnameinfo(resorig->ai_addr, resorig->ai_addrlen,
              numhost, sizeof (numhost), NULL, 0, NI_NUMERICHOST)) != 0)
      {
        throw_msg("getnameinfo: '%s'", gai_strerror(error));
      } else if ((error = getnameinfo(resorig->ai_addr, resorig->ai_addrlen,
          host, sizeof (host), NULL, 0, 0)) != 0)
      {
        throw_msg("getnameinfo: '%s'", gai_strerror(error));
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

char *_get_ipaddr_by_addr(char *address)
{
	int error;
	struct addrinfo *res, *resorig, hints;
  struct sockaddr_in *addr;
  struct sockaddr_in6 *addr6;
  char *ipstring;
  unsigned char buf[sizeof(struct in6_addr)];

	memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
  ipstring = NULL;

  if ((error = getaddrinfo(address, NULL, &hints, &res)) != 0)
  {
    throw_msg("getaddrinfo: '%s'", gai_strerror(error));
  } else {
    for (resorig = res; res != NULL; res = res->ai_next)
    {
      switch (res->ai_family) {
        case AF_INET:
          addr = (struct sockaddr_in *)resorig->ai_addr;
          ipstring = inet_ntoa((struct in_addr)addr->sin_addr);
          freeaddrinfo(resorig);
          return ipstring;
        case AF_INET6:
          if ( (addr6 = (struct sockaddr_in6 *)resorig->ai_addr ) != NULL)
          {
            memcpy(buf, addr6->sin6_addr.s6_addr, sizeof(addr6->sin6_addr.s6_addr));
            ipstring = malloc(INET6_ADDRSTRLEN);
            inet_ntop(AF_INET6, buf, ipstring, INET6_ADDRSTRLEN);
          }
          freeaddrinfo(resorig);
          return ipstring;
        default:
          ipstring = NULL;
          break;
      }
    }
	  if (resorig) freeaddrinfo(resorig);
  }
	return ipstring;
}

void nx_expr_func__xm_resolve2_gid_to_name(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  gid_t gid;
  struct group* g;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if ( (args[0].type != NX_VALUE_TYPE_STRING) &&
      (args[0].type != NX_VALUE_TYPE_INTEGER) )
  {
    throw_msg("'%s' type argument is invalid. allowed types are '%s' and '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING),
        nx_value_type_to_string(NX_VALUE_TYPE_INTEGER));
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
      gid = (gid_t)atoi(args[0].string->buf);
      break;
    case NX_VALUE_TYPE_INTEGER:
      gid = (gid_t)atoi(nx_value_to_string(&args[0]));
      break;
    default:
      retval->defined = FALSE;
      return;
  }
  if( ( g = getgrgid( gid ) ) == NULL )
  {
    retval->defined = FALSE;
    return;
     }
  retval->string = nx_string_create(g->gr_name, -1);
  retval->defined = TRUE;
}

void nx_expr_func__xm_resolve2_group_get_gid(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  char *groupname;
  struct group* g;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if (args[0].type != NX_VALUE_TYPE_STRING)
  {
    throw_msg("'%s' type argument is invalid. allowed type is '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING));
  }

  retval->type = NX_VALUE_TYPE_INTEGER;
  if ( args[0].defined == FALSE )
  {
    retval->defined = FALSE;
    return;
  }

  groupname = args[0].string->buf;
  if( ( g = getgrnam( groupname ) ) == NULL )
  {
    retval->defined = FALSE;
    return;
     }
  retval->integer = (int64_t)g->gr_gid;
  retval->defined = TRUE;
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
  if ((hostname = _get_hostname_by_addr(ipaddr)) != NULL)
  {
    retval->string = nx_string_create(hostname, -1);
    free(hostname);
  } else {
    retval->string = nx_string_create(ipaddr, -1);
  }
  retval->defined = TRUE;
}

void nx_expr_func__xm_resolve2_name_to_ipaddr(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  char *ipaddr;
  char *hostname;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if (args[0].type != NX_VALUE_TYPE_STRING)
  {
    throw_msg("'%s' type argument is invalid. allowed type is '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING));
  }

  retval->type = NX_VALUE_TYPE_STRING;
  if ( args[0].defined == FALSE )
  {
    retval->defined = FALSE;
    return;
  }

  hostname = args[0].string->buf;

  if ( hostname == NULL )
  {
    retval->defined = FALSE;
    return;
  }
  if ((ipaddr = _get_ipaddr_by_addr(hostname)) != NULL)
  {
    retval->string = nx_string_create(ipaddr, -1);
    free(ipaddr);
    retval->defined = TRUE;
  } else {
    retval->defined = FALSE;
  }
}

void nx_expr_func__xm_resolve2_uid_to_name(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  uid_t uid;
  struct passwd* u;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if ( (args[0].type != NX_VALUE_TYPE_STRING) &&
      (args[0].type != NX_VALUE_TYPE_INTEGER) )
  {
    throw_msg("'%s' type argument is invalid. allowed types are '%s' and '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING),
        nx_value_type_to_string(NX_VALUE_TYPE_INTEGER));
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
      uid = (uid_t)atoi(args[0].string->buf);
      break;
    case NX_VALUE_TYPE_INTEGER:
      uid = (uid_t)atoi(nx_value_to_string(&args[0]));
      break;
    default:
      retval->defined = FALSE;
      return;
  }
  if( ( u = getpwuid( uid ) ) == NULL )
  {
    retval->defined = FALSE;
    return;
     }
  retval->string = nx_string_create(u->pw_name, -1);
  retval->defined = TRUE;
}

void nx_expr_func__xm_resolve2_user_get_gid(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  char *username;
  struct passwd* u;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if ( (args[0].type != NX_VALUE_TYPE_STRING) &&
      (args[0].type != NX_VALUE_TYPE_INTEGER) )
  {
    throw_msg("'%s' type argument is invalid. allowed type is '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING));
  }

  retval->type = NX_VALUE_TYPE_STRING;
  if ( args[0].defined == FALSE )
  {
    retval->defined = FALSE;
    return;
  }

  username = args[0].string->buf;
  if( ( u = getpwnam( username ) ) == NULL )
  {
    retval->defined = FALSE;
    return;
     }
  retval->integer = (uint64_t)u->pw_gid;
  retval->defined = TRUE;
}

void nx_expr_func__xm_resolve2_user_get_uid(nx_expr_eval_ctx_t *eval_ctx UNUSED,
    nx_module_t *module UNUSED,
    nx_value_t *retval,
    int32_t num_arg,
    nx_value_t *args)
{
  char *username;
  struct passwd* u;

  ASSERT(retval != NULL);
  ASSERT(num_arg == 1);

  if ( (args[0].type != NX_VALUE_TYPE_STRING) &&
      (args[0].type != NX_VALUE_TYPE_INTEGER) )
  {
    throw_msg("'%s' type argument is invalid. allowed type is '%s'.",
        nx_value_type_to_string(args[0].type),
        nx_value_type_to_string(NX_VALUE_TYPE_STRING));
  }

  retval->type = NX_VALUE_TYPE_STRING;
  if ( args[0].defined == FALSE )
  {
    retval->defined = FALSE;
    return;
  }

  username = args[0].string->buf;
  if( ( u = getpwnam( username ) ) == NULL )
  {
    retval->defined = FALSE;
    return;
     }
  retval->integer = (uint64_t)u->pw_uid;
  retval->defined = TRUE;
}

