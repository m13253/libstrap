
#include <libstrap.h>

extern ls_version_t *ls_version(void) {
    ls_version_t *version = ls_malloc(sizeof (ls_version_t));
    version->release = 0;
    version->major   = 0;
    version->minor   = 1;
    version->rev     = 0;
    version->edition   = ls_str_fromsz("default");
    version->timestamp = ls_str_fromsz(__DATE__ ", " __TIME__);
    return version;
}

extern ls_version_t *ls_version_free(ls_version_t *version) {
    if(version) {
        version->edition = ls_str_free(version->edition);
        version->timestamp = ls_str_free(version->timestamp);
        ls_free(version);
    }
    return NULL;
}
