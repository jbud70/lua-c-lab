#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <math.h>

// Native C function that is called by lua
// (All C functions to be called from lua must retun an int and take a lua_state as an arg)
int pythagoras_c(lua_State *L)
{
    lua_Number b = lua_tonumber(L, -1); // get arg for b (last added to stack)
    lua_Number a = lua_tonumber(L, -2); // get arg for b (first added to stack)
    lua_Number result = sqrt(pow(a, 2.0) + pow(b, 2.0));
    lua_pushnumber(L, result); // Push function result to stack
    return 1;                  // how many values are returned
}

// Register and call a native C function
void lua_call_c_func(void)
{
    printf("\n*** Called lua_call_c_func ... \n");

    lua_State *L = luaL_newstate();

    lua_pushcfunction(L, pythagoras_c); // Push native C func to lua_state
    lua_setglobal(L, "pythagoras_c");

    if (luaL_dofile(L, "./scripts/pythagoras_c.lua") != LUA_OK)
    {
        luaL_error(L, "!!! Lua Error: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "pythagoras");

    if (lua_isfunction(L, -1))
    {
        lua_pushnumber(L, 35); // Push first arg to stack, x
        lua_pushnumber(L, 47); // Push second arg to stack, y
        if (lua_pcall(L, 2, 1, 0) != LUA_OK)
        {
            luaL_error(L, "!!! Lua Error: %s\n", lua_tostring(L, -1));
        }
        else
        {
            lua_Number result = lua_tonumber(L, -1);
            printf("The return from the pythagoras_c func call is %f\n", (float)result);
        }
    }
    else
    {
        printf("No function found on top of stack.\n");
    }

    lua_close(L);
}