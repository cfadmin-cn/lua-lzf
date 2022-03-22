#define LUA_LIB

#include <core.h>
#include <lzf.h>


static int llzf_compress(lua_State *L) {
  size_t tsize;
  const char *text = luaL_checklstring(L, 1, &tsize);
  if (!text || tsize < 1)
    return luaL_error(L, "[lzf_compress error]: Invalid buffer.");

  size_t bsize = LZF_MAX_COMPRESSED_SIZE(tsize);
  char *buffer = lua_newuserdata(L, bsize);

  int rsize;
  if ((rsize = lzf_compress(text, tsize, buffer, bsize)) < 1)
    return luaL_error(L, "[lzf_compress error]: Can't compressed text.");

  lua_pushlstring(L, buffer, rsize);
  return 1;
}

static int llzf_uncompress(lua_State *L) {

  size_t tsize;
  const char *text = luaL_checklstring(L, 1, &tsize);
  if (!text || tsize < 1)
    return luaL_error(L, "[lzf_compress error]: Invalid buffer.");

  size_t bsize = tsize * 2;
  for (;;) {
    char* buffer = lua_newuserdata(L, bsize);
    int ret = lzf_decompress(text, tsize, buffer, bsize);
    printf("ret = %d\n", ret);
    if (ret == 0) {
      if (errno == EINVAL) {
        errno = 0;
        bsize *= 2;
        lua_pop(L, 1);
        continue;
      }
      if (errno == EINVAL) {
        lua_pushboolean(L, 0);
        lua_pushliteral(L, "[lzf_decompress error]: Invalid text buffer.");
        return 2;
      }
      return luaL_error(L, "[lzf_decompress error]: Unknown error.");
    }
    if (ret > 0) {
      lua_pushlstring(L, buffer, ret);
      break;
    }
  }
  return 1;
}


LUAMOD_API int
luaopen_llzf(lua_State *L) {
  luaL_checkversion(L);
  luaL_Reg lzf_libs[] = {
    {"compress", llzf_compress},
    {"uncompress", llzf_uncompress},
    {NULL, NULL},
  };
  luaL_newlib(L, lzf_libs);
  return 1;
}