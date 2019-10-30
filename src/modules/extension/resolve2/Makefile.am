#
#	xm_resolve2
#
#	This file is NOT part of the nxlog log collector tool.
#	See the file LICENSE in the source root for licensing terms.
#
#	Work on this module has been inspired by the documentation of the NXLog's Enterprise Module xm_resolver
#	Author: 2019 Stephan Seitz <s.seitz@mailbox.org>
#
noinst_LTLIBRARIES = libresolve2.la
xm_resolve2_LTLIBRARIES		= xm_resolve2.la
xm_resolve2_la_SOURCES		= xm_resolve2.c xm_resolve2.h xm_resolve2_funcproc_cb.c $(xm_resolve2_la_BUILTSOURCES)
libresolve2_la_SOURCES    = resolve2.c resolve2.h
xm_resolve2_la_LDFLAGS		= -module -no-undefined -avoid-version
xm_resolve2_la_LIBADD		= libresolve2.la $(LIBNX)
xm_resolve2dir			= $(NX_MODULEDIR)/extension
xm_resolve2_la_BUILTSOURCES	= expr-xm_resolve2-funcproc.c expr-xm_resolve2-funcproc.h
expr-xm_resolve2-funcproc.c: $(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
	-$(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
expr-xm_resolve2-funcproc.h: $(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
	-$(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml

EXTRA_DIST			= xm_resolve2-api.xml $(xm_resolve2_la_BUILTSOURCES)
MAINTAINERCLEANFILES    	+= $(xm_resolve2_la_BUILTSOURCES)
