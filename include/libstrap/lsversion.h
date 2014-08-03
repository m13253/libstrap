#ifndef _LS_VERSION_H
#define _LS_VERSION_H

typedef struct ls_version_t {
    int release;
    int major;
    int minor;
    int rev;
    ls_str edition;
    ls_str timestamp;
} ls_version_t;

extern ls_version_t *ls_version(void);
extern ls_version_t *ls_version_free(ls_version_t *version);

#endif
