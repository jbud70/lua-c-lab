// Use Lua 5.3.5

#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Open a lua file and executes it
void lua_dofile(void)
{
    printf("\n*** Called lua_dofile ... \n");

    lua_State *L = luaL_newstate(); // Create a new Lua state

    luaL_openlibs(L); // Import Lua std libs for the active state

    // Open lua file and execute it (with error checking)
    if (luaL_dofile(L, "./scripts/factorial.lua") != LUA_OK)
    {
        luaL_error(L, "!!! Lua Error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L); // Always close your Lua state when finished
}

// Manually set a variable in the lua state
void lua_getvar(void)
{
    printf("\n*** Called lua_getvar ... \n");

    lua_State *L = luaL_newstate();

    luaL_dostring(L, "some_var = 5326");            // Create varible in lua state manually
    lua_getglobal(L, "some_var");                   // Grab new variable and place it on stack
    lua_Number some_var_in_c = lua_tonumber(L, -1); // Retrieve variable from stack

    printf("The value of some_var is %d\n", (int)some_var_in_c);

    lua_close(L);
}

// Manipulate the lua stack
void lua_stack(void)
{
    printf("\n*** Called lua_stack ... \n");

    lua_State *L = luaL_newstate();

    lua_Number current_num;
    int stack_count = 0;

    lua_pushnumber(L, 10); // stack[1] aka stack[-4]
    lua_pushnumber(L, 20); // stack[2] aka stack[-3]
    lua_pushnumber(L, 30); // stack[3] aka stack[-2]
    lua_pushnumber(L, 40); // stack[4] aka stack[-1]

    /*
        Stack now looks like:
        40   <<< TOP (-1) or (4)
        30
        20
        10   <<< BOTTOM (-4) or (1)
    */

    stack_count = lua_gettop(L);       // Get element count of current stack (by retrieving the stack index of the top element)
    current_num = lua_tonumber(L, -1); // Retieve top number off stack (40)
    printf("The current stack count is: %i\n", stack_count);
    printf("The top number just retieved from the stack is: %d\n", (int)current_num);

    lua_remove(L, 2); // Remove second element in stack (20)

    /*
        Stack now looks like:
        40   <<< TOP (-1) or (3)
        30
        10   <<< BOTTOM (-3) or (1)
    */

    stack_count = lua_gettop(L);
    current_num = lua_tonumber(L, 2); // Retieve second number off stack (10)
    printf("The current stack count is: %i\n", stack_count);
    printf("The second number just retieved from the stack is: %d\n", (int)current_num); // Should be 30

    lua_close(L);
}

// Retrieve a function from a lua files and calls it
void lua_call_func(void)
{
    printf("\n*** Called lua_call_func ... \n");

    lua_State *L = luaL_newstate();

    int stack_count = 0;

    luaL_requiref(L, LUA_MATHLIBNAME, luaopen_math, 1); // Import only math lib, as opposed to all libs as above

    if (luaL_dofile(L, "./scripts/pythagoras.lua") != LUA_OK)
    {
        luaL_error(L, "!!! Lua Error: %s\n", lua_tostring(L, -1));
    }

    lua_getglobal(L, "pythagoras"); // Place function on stack

    if (lua_isfunction(L, -1)) // Check to see if top of stack is a function
    {
        lua_pushnumber(L, 35); // Push first arg to stack, x
        lua_pushnumber(L, 47); // Push second arg to stack, y
        stack_count = lua_gettop(L);
        printf("The stack count before function call: %i\n", stack_count);
        if (lua_pcall(L, 2, 1, 0) != LUA_OK) // (LuaState, num of args, num of returns, error), this pops off args from stack
        {
            luaL_error(L, "!!! Lua Error: %s\n", lua_tostring(L, -1));
        }
        else
        {
            lua_Number result = lua_tonumber(L, -1); // Get return from lua stack
            stack_count = lua_gettop(L);
            printf("The stack count after function call: %i\n", stack_count);
            printf("The return from the pythagoras func call is %f\n", (float)result);
        }
    }
    else
    {
        printf("No function found on top of stack.\n");
    }

    lua_close(L);
}