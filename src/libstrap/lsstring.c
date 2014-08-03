
/* for memmem */
#define _GNU_SOURCE

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <libstrap.h>

struct ls_str_header {
    size_t reserved;
    size_t length;
    char buffer[];
};

#define LS_STR_HEADLEN (2*sizeof (size_t))

static inline struct ls_str_header *ls_str_header(ls_str str) {
    if(!str) {
        assert(str != NULL);
        abort();
    }
    return (struct ls_str_header *) (((void *) str)-LS_STR_HEADLEN);
} __ls_attr_const

static inline const struct ls_str_header *ls_const_str_header(ls_const_str str) {
    if(!str) {
        assert(str != NULL);
        abort();
    }
    return (const struct ls_str_header *) (((const void *) str)-LS_STR_HEADLEN);
} __ls_attr_const

ls_str ls_str_empty(void) {
    struct ls_str_header *header = ls_malloc(LS_STR_HEADLEN+sizeof (char));
    header->reserved = 0;
    header->length = 0;
    header->buffer[0] = '\0';
    return header->buffer;
}

ls_str ls_str_fromsz(const char *cstr) {
    return ls_str_frombuf(cstr, strlen(cstr));
}

ls_str ls_str_frombuf(const char *buffer, size_t length) {
    if(length > 0) {
        struct ls_str_header *header = ls_malloc(LS_STR_HEADLEN+(length+1)*sizeof (char));
        header->reserved = length;
        header->length = length;
        memcpy(header->buffer, buffer, length);
        header->buffer[length] = '\0';
        return header->buffer;
    } else {
        return ls_str_empty();
    }
}

ls_str ls_str_copy(ls_const_str str) {
    return ls_str_frombuf(str, ls_str_length(str));
}

ls_str ls_str_free(ls_str str) {
    ls_free(str);
    return NULL;
}

ls_str ls_str_slice(ls_const_str str, size_t begin, size_t end) {
    size_t totallength = ls_str_length(str);
    if(begin < 0) {
        begin = totallength+begin;
    }
    if(begin < 0) {
        begin = 0;
    } else if(begin > totallength) {
        begin = totallength;
    }
    if(end < 0) {
        end = totallength+end;
    }
    if(end < 0) {
        end = 0;
    } else if(end > totallength) {
        end = totallength;
    }
    return ls_str_frombuf(str+begin, end-begin);
}

ls_str ls_str_slicelen(ls_const_str str, size_t offset, size_t length) {
    size_t totallength = ls_str_length(str);
    if(offset < 0) {
        offset = totallength+offset;
    }
    if(offset < 0) {
        offset = 0;
    } else if(offset > totallength) {
        return ls_str_empty();
    }
    if(length <= 0 || offset+length > totallength) {
        length = totallength-offset;
    }
    return ls_str_frombuf(str+offset, length);
}

size_t ls_str_length(ls_const_str str) {
    size_t res = ls_const_str_header(str)->length;
    if(res >= 0) {
        return res;
    } else {
        assert(res >= 0);
        abort();
    }
}

/*
static size_t utf8lengthmap[] = {0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfc, 0xfe};

size_t ls_str_utf8length(ls_const_str str) {
    size_t totallength = ls_str_length(str);
    size_t i = 0;
    size_t res = 0;
    for(i = 0; i < totallength; i++) {
    }
}
*/

size_t ls_str_reserved_length(ls_const_str str) {
    size_t res = ls_const_str_header(str)->reserved;
    if(res >= 0) {
        return res;
    } else {
        assert(res >= 0);
        abort();
    }
}

ls_str ls_str_reserve(ls_str str, size_t length) {
    struct ls_str_header *header;
    size_t current_length;
    if(!str) {
        str = ls_str_empty();
    }
    header = ls_str_header(str);
    current_length = ls_str_length(str);
    if(current_length > length) {
        length = current_length;
    }
    header = ls_realloc(header, LS_STR_HEADLEN+(length+1)*sizeof (char));
    header->buffer[length] = '\0';
    header->reserved = length;
    return header->buffer;
}

ls_str ls_str_append(ls_str str1, ls_const_str str2) {
    return ls_str_appendbuf(str1, str2, ls_str_length(str2));
}

ls_str ls_str_appendsz(ls_str str1, const char *cstr2) {
    return ls_str_appendbuf(str1, cstr2, strlen(cstr2));
}

ls_str ls_str_appendbuf(ls_str str1, const char *buffer2, size_t length2) {
    size_t length1 = ls_str_length(str1);
    if(ls_str_reserved_length(str1) < length1+length2) {
        str1 = ls_str_reserve(str1, length1+length2);
    }
    memcpy(str1+length1, buffer2, length2);
    str1[length1+length2] = '\0';
    ls_str_header(str1)->length = length1+length2;
    return str1;
}

ls_str ls_str_trunc(ls_str str, size_t length) {
    size_t current_length = ls_str_length(str);
    if(current_length < length) {
        str = ls_str_reserve(str, length);
        memset(str+current_length, 0, length-current_length+1);
        ls_str_header(str)->length = length;
    } else {
        str[length] = '\0';
        ls_str_header(str)->length = length;
        str = ls_str_reserve(str, length);
    }
    return str;
}

int ls_str_compare(ls_const_str str1, ls_const_str str2) {
    size_t length1 = ls_str_length(str1);
    size_t length2 = ls_str_length(str2);
    if(length1 == length2) {
        return memcmp(str1, str2, length1);
    } else {
        int res = memcmp(str1, str2, length1 < length2 ? length1 : length2);
        if(res != 0) {
            return res;
        } else {
            return length1 < length2 ? -(int) ((unsigned char *) str2)[length1] : (int) ((unsigned char *) str1)[length2];
        }
    }
}

bool ls_str_beginswith(ls_const_str str, ls_const_str substr) {
    size_t sublength = ls_str_length(substr);
    if(sublength < ls_str_length(str)) {
        return !memcmp(str, substr, sublength);
    } else {
        return false;
    }
}

bool ls_str_endswith(ls_const_str str, ls_const_str substr) {
    size_t length = ls_str_length(str);
    size_t sublength = ls_str_length(substr);
    if(sublength < length) {
        return !memcmp(str+(length-sublength), substr, sublength);
    } else {
        return false;
    }
}

size_t ls_str_find(ls_const_str str, ls_const_str substr, size_t begin) {
    return ls_str_findbuf(str, substr, ls_str_length(substr), begin);
}

size_t ls_str_findsz(ls_const_str str, const char *subcstr, size_t begin) {
    return ls_str_findbuf(str, subcstr, strlen(subcstr), begin);
}

size_t ls_str_findbuf(ls_const_str str, const char *subbuffer, size_t sublength, size_t begin) {
    size_t length = ls_str_length(str);
    if(begin > length) {
        return -1;
    } else {
        const char *res = memmem(str+begin, length-begin, subbuffer, sublength);
        if(res) {
            return res-str;
        } else {
            return -1;
        }
    }
}

size_t ls_str_findchar(ls_const_str str, char substr, size_t begin) {
    size_t length = ls_str_length(str);
    if(begin >= length) {
        return -1;
    } else {
        const char *res = memchr(str+begin, substr, length-begin);
        if(res) {
            return res-str;
        } else {
            return -1;
        }
    }
}

ls_str ls_str_toasciiupper(ls_str str) {
    size_t length = ls_str_length(str);
    while(length-- > 0) {
        if(*str > 96 && *str <= 122) {
            *str &= ~32;
        }
        str++;
    }
    return str;
}

ls_str ls_str_toasciilower(ls_str str) {
    size_t length = ls_str_length(str);
    while(length-- > 0) {
        if(*str > 64 && *str <= 90) {
            *str |= 32;
        }
        str++;
    }
    return str;
}
