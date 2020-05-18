#include "c_to_lua.h"
#include "lua_to_c.h"

int main(int argc, char *argv[])
{
    lua_dofile();
    lua_getvar();
    lua_stack();
    lua_call_func();
    lua_call_c_func();
    return 0;
}