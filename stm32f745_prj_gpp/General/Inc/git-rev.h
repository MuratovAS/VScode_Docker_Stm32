#define STR_EXPAND(x) #x
#define STR(x) STR_EXPAND(x)
#define GIT_STR STR(GIT_REV)
#define GIT_REV 3a26d7bf-dirty