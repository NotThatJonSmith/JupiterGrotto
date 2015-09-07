
#include <cstdlib>

extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

class LuaEngine {

private:
	lua_State *state;

public:
	LuaEngine();
	~LuaEngine();
	runScript(std::string);

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_close(L);

};