#ifndef _LS_COMPAT_H
#define _LS_COMPAT_H

#define __ls_attr_alloc_size(n)      __attribute__((__alloc_size__(n)))
#define __ls_attr_alloc_size2(m, n)  __attribute__((__alloc_size__(m, n)))
#define __ls_attr_const              __attribute__((__const__))
#define __ls_attr_malloc             __attribute__((__malloc__))
#define __ls_attr_pure               __attribute__((__pure__))
#define __ls_attr_returns_nonnull    __attribute__((__returns_nonnull__))
#define __ls_attr_warn_unused_result __attribute__((__warn_unused_result__))

#endif
