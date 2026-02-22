#define _POSIX_C_SOURCE 200112L

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifdef _WIN32
# include <io.h>
# define isatty _isatty
# define fileno _fileno
#else
# ifndef _MSC_VER
#  include <unistd.h>
# endif
#endif

static int
lua_isatty(lua_State *L)
{
    FILE **fp = (FILE **) luaL_checkudata(L, 1, LUA_FILEHANDLE);

    lua_pushboolean(L, isatty(fileno(*fp)));
    return 1;
}

LUALIB_API int
luaopen_term_core(lua_State *L)
{
    lua_newtable(L);
    lua_pushstring(L, "lua-term 0.8");
    lua_setfield(L, -2, "_VERSION");
    lua_pushcfunction(L, lua_isatty);
    lua_setfield(L, -2, "isatty");

    return 1;
}
