# NXLog fork

This fork is used for developing additional modules.

**To build this project, use:**
```./autogen.sh
make  
sudo make install```

**Before commiting / merging into master:**

```make distclean```

## Modules added:
### xm_resolve2

Work on this module has been inspired by the documentation of the NXLog's Enterprise Module xm_resolver ( https://nxlog.co/documentation/nxlog-user-guide/xm_resolver.html ).
This module can be used, following the documentation of xm_resolver with following minor changes:
- ipaddr_to_name accepts Hostname, FQDN, IPv6 and IPv4 instead of IPv4 only.
- name_to_ipaddr returns a string instead of an ip4addr. Additionally, it returns not only IPv4, also IPv6 is supported.
- uid_to_name has not been tested on Windows, it's very unlikely that it translates a SID to DOMAIN\USER notation.
