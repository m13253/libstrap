#ifndef _LS_STRING_H
#define _LS_STRING_H

typedef char *ls_str;
typedef const char *ls_const_str;

extern ls_str ls_str_empty(void) __ls_attr_warn_unused_result;
extern ls_str ls_str_fromsz(const char *cstr) __ls_attr_warn_unused_result;
extern ls_str ls_str_frombuf(const char *buffer, size_t length) __ls_attr_alloc_size(2) __ls_attr_warn_unused_result;
/* extern ls_str ls_str_fromarray(); __ls_attr_warn_unused_result */
extern ls_str ls_str_copy(ls_const_str str) __ls_attr_warn_unused_result;
extern ls_str ls_str_free(ls_str str) __ls_attr_warn_unused_result;

extern ls_str ls_str_slice(ls_const_str str, size_t begin, size_t end) __ls_attr_warn_unused_result;
extern ls_str ls_str_slicelen(ls_const_str str, size_t offset, size_t length) __ls_attr_warn_unused_result;

extern size_t ls_str_length(ls_const_str str) __ls_attr_pure;
extern size_t ls_str_utf8length(ls_const_str str) __ls_attr_pure;
extern size_t ls_str_reserved_length(ls_const_str str) __ls_attr_pure;
extern ls_str ls_str_reserve(ls_str str, size_t length) __ls_attr_warn_unused_result;
extern ls_str ls_str_append(ls_str str1, ls_const_str str2) __ls_attr_warn_unused_result;
extern ls_str ls_str_appendsz(ls_str str1, const char *cstr2) __ls_attr_warn_unused_result;
extern ls_str ls_str_appendbuf(ls_str str1, const char *buffer2, size_t length2) __ls_attr_warn_unused_result;
extern ls_str ls_str_trunc(ls_str str, size_t length) __ls_attr_warn_unused_result;

extern int ls_str_compare(ls_const_str str1, ls_const_str str2) __ls_attr_pure;
extern bool ls_str_beginswith(ls_const_str str, ls_const_str substr) __ls_attr_pure;
extern bool ls_str_endswith(ls_const_str str, ls_const_str substr) __ls_attr_pure;
extern size_t ls_str_find(ls_const_str str, ls_const_str substr, size_t begin) __ls_attr_pure;
extern size_t ls_str_findsz(ls_const_str str, const char *subcstr, size_t begin) __ls_attr_pure;
extern size_t ls_str_findbuf(ls_const_str str, const char *subbuffer, size_t sublength, size_t begin) __ls_attr_pure;
extern size_t ls_str_findchar(ls_const_str str, char substr, size_t begin) __ls_attr_pure;

extern ls_str ls_str_toasciiupper(ls_str str) __ls_attr_warn_unused_result;
extern ls_str ls_str_toasciilower(ls_str str) __ls_attr_warn_unused_result;

#endif
