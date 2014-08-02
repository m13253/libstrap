
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
    return (struct ls_str_header *) (((void *) str)-LS_STR_HEADLEN);
}

static inline const struct ls_str_header *ls_const_str_header(ls_const_str str) {
    return (const struct ls_str_header *) (((const void *) str)-LS_STR_HEADLEN);
}

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

size_t ls_str_reserved_length(ls_const_str str) {
    size_t res = ls_const_str_header(str)->reserved;
    if(res >= 0) {
        return res;
    } else {
        assert(res >= 0);
        abort();
    }
}
