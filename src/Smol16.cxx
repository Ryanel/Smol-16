#include <config.h>
#include <smol16.hpp>
#include <memory.hpp>
#include <ppu.hpp>

#ifdef BACKEND_SDL
#include <sdl_backend.hpp>
CBackend_SDL * sdl;
#endif


CSystem *CSystem::_instance = NULL;
CSystem *CSystem::instance()
{
    if (!_instance)
    {
        _instance = new CSystem();
    }
    return _instance;
}


CSystem::CSystem()
{
    _log = spdlog::stdout_color_mt("sys");
    // Init subsystems
    L = luaL_newstate();
    // Load standard library
    luaL_openlibs(L);
    getGlobalNamespace(L)
       .beginNamespace("debug")
       .addFunction("dump_stack", &CSystem::StackDump)
       .endNamespace();
   _log->debug("Lua initialised");
}


/*! Initialises the enviroment */
void CSystem::Init()
{
    _mem = CMemory::instance();
    _ppu = CPPU::instance();
    // We now load the STD
    LoadFile(g_config.std_path);
    // We are now ready to accept carts!
    _log->info("Subsystems initialised!");
}


void CSystem::LoadFile(std::string path)
{
    int status = 0;
    // Load file into Lua Enviroment
    status = luaL_loadfile(L, path.c_str());
    if (status)
    {
        _log->critical("Couldn't load file: {}", lua_tostring(L, -1));
        exit(1);
    }

    // Run it.
    status = lua_pcall(L, 0, 0, 0); // Call with no args, no result
    if (status)
    {
        _log->critical("Error in executing lua code: {}", lua_tostring(L, -1));
        exit(1);
    }
}

void CSystem::Call(std::string function) {
    LuaRef func = getGlobal (L, function.c_str());
    try {
      func ();
    }
    catch (LuaException const& e) {
        _log->error("Error calling function {}: {}", function.c_str(), e.what());
        StackDump(L);
        exit(1);
    }
}

void CSystem::StackDump(lua_State *L)
{
    int i;
    int top = lua_gettop(L);

    printf("Stack dump:\n");
    for (i = 1; i <= top; i++)  /* repeat for each level */
    {
        int t = lua_type(L, i);
        switch (t)
        {
        case LUA_TSTRING: /* strings */
            printf("`%s'", lua_tostring(L, i));
            break;

        case LUA_TBOOLEAN: /* booleans */
            printf(lua_toboolean(L, i) ? "true" : "false");
            break;

        case LUA_TNUMBER: /* numbers */
            printf("%g", lua_tonumber(L, i));
            break;

        default: /* other values */
            printf("%s", lua_typename(L, t));
            break;
        }
        printf("  "); /* put a separator */
    }
    printf("\n");     /* end the listing */
}


void CSystem::Run()
{
    #ifdef BACKEND_SDL
    sdl = CBackend_SDL::instance();
    #endif

    setGlobal(L,g_config.cart_path,"_cart_path");
    LoadFile(g_config.cart_path + "/main.lua");

    Call("_init"); // Let the cart initialise itself

    while(this->running) {
        // TODO: Start FPS timer
        // TODO: Update Input
        #ifdef BACKEND_SDL
        sdl->EventLoop();
        #endif
        Call("_update"); // Now, we update every frame
        Call("_render"); // And draw
        //TODO: Sample here to see if we went over our time budget. Wait a frame if needed
        // Has the cart signaled to the console that a new frame is ready?
        // Let the PPU figure this out
        _ppu->DoRender();
    }

    if (g_config.enableDebugging)
    {
        StackDump(L);
    }
}
