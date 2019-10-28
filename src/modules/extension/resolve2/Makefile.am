xm_resolve2_LTLIBRARIES		= xm_resolve2.la
xm_resolve2_la_SOURCES		= xm_resolve2.c xm_resolve2_funcproc_cb.c $(xm_resolve2_la_BUILTSOURCES)
xm_resolve2_la_LDFLAGS		= -module -no-undefined -avoid-version
xm_resolve2_la_LIBADD		= $(LIBNX)
xm_resolve2dir			= $(NX_MODULEDIR)/extension
xm_resolve2_la_BUILTSOURCES	= expr-xm_resolve2-funcproc.c expr-xm_resolve2-funcproc.h
expr-xm_resolve2-funcproc.c: $(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
	-$(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
expr-xm_resolve2-funcproc.h: $(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml
	-$(top_builddir)/src/utils/codegen.pl xm_resolve2-api.xml

EXTRA_DIST			= xm_resolve2-api.xml $(xm_resolve2_la_BUILTSOURCES)
MAINTAINERCLEANFILES    	+= $(xm_resolve2_la_BUILTSOURCES)
