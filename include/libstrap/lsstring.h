#ifndef _LS_STRING_H
#define _LS_STRING_H

typedef char *ls_str;
typedef const char *ls_const_str;

extern ls_str ls_str_empty(void);
extern ls_str ls_str_fromsz(const char *cstr);
extern ls_str ls_str_frombuf(const char *buffer, size_t length);
/* extern ls_str ls_str_fromarray(); */
extern ls_str ls_str_copy(ls_const_str str);
extern char *ls_str_tosz(ls_const_str str);
extern ls_str ls_str_free(ls_str str);

extern ls_str ls_str_slice(ls_const_str str, size_t begin, size_t end);
extern ls_str ls_str_slicelen(ls_const_str str, size_t offset, size_t length);

extern size_t ls_str_length(ls_const str);
extern size_t ls_str_utf8length(ls_const str);
extern size_t ls_str_reserved_length(ls_const str);
extern ls_str ls_str_reserve(ls_str str, size_t length);
extern ls_str ls_str_append(ls_str str1, ls_const_str str2);
extern ls_str ls_str_appendsz(ls_str str1, const char *cstr2);
extern ls_str ls_str_appendbuf(ls_str str1, const char *buffer2, size_t length2);
extern ls_str ls_str_trunc(ls_str str, size_t length);

extern int ls_str_compare(ls_const_str str1, ls_const_str str2);
extern int ls_str_cryptocompare(ls_const_str str1, ls_const_str str2);
extern size_t ls_str_find(ls_const_str str, ls_const_str substr, size_t begin);
extern size_t ls_str_findsz(ls_const_str str, const char *subcstr, size_t begin);
extern size_t ls_str_findbuf(ls_const_str str, const char *subbuffer, size_t sublength, size_t begin);
extern size_t ls_str_findchar(ls_const_str str, char substr, size_t begin);

extern ls_str ls_str_toasciiupper(ls_str str);
extern ls_str ls_str_toasciilower(ls_str str);

#endif
