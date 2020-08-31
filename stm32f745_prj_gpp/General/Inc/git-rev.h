#define STR_EXPAND(x) #x
#define STR(x) STR_EXPAND(x)
#define GIT_STR STR(GIT_REV)
#define GIT_REV 38b50753-dirty