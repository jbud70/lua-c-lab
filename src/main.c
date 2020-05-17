#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

void lua_dofile(void)
{
    lua_State *L = luaL_newstate(); // Create a new Lua state

    printf("\nCalling lua_dofile ... \n");

    luaL_openlibs(L);                          // Import Lua std libs for the active state
    luaL_dofile(L, "./scripts/factorial.lua"); // Open lua file and execute it

    lua_close(L); // Always close your Lua state when finished
}

void lua_getvar(void)
{
    lua_State *L = luaL_newstate();

    printf("\nCalling lua_getvar ... \n");

    luaL_dostring(L, "some_var = 486");
    lua_getglobal(L, "some_var");
    lua_Number some_var_in_c = lua_tonumber(L, -1);

    printf("The value of some_var is %d\n", (int)some_var_in_c);

    lua_close(L);
}

void lua_call_func(void)
{
    lua_State *L = luaL_newstate();

    printf("\nCalling lua_call_func ... \n");

    luaL_requiref(L, LUA_MATHLIBNAME, luaopen_math, 1); // Import only math lib, as opposed to all libs as above
    luaL_dofile(L, "./scripts/pythagoras.lua");

    lua_getglobal(L, "pythagoras"); // Place function on stack

    if (lua_isfunction(L, -1)) // Check to see if top of stack is a function
    {
        lua_pushnumber(L, 3);                    // Push first arg to stack, x
        lua_pushnumber(L, 4);                    // Push second arg to stack, y
        lua_pcall(L, 2, 1, 0);                   // (LuaState, num of args, num of returns, error)
        lua_Number result = lua_tonumber(L, -1); // Get return from Lua stack
        printf("The return from the pythagoras func call is %f\n", (float)result);
    }
    else
    {
        printf("No function found on top of stack.\n");
    }

    lua_close(L);
}

int main(int argc, char *argv[])
{
    lua_dofile();
    lua_getvar();
    lua_call_func();
    return 0;
}