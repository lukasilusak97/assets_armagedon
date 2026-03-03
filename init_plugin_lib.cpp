
#include "world/role_tools.h"
#include "utils/plugin_manager.h"
#include "world/world_init_tools.h"

using namespace ella::world;


extern "C" void Init() {
    for (auto const &pluginRole: Role::AllRoles()) {
        pluginRole->ReloadContent();
    }
}

extern "C" void Deinit() {
    for (auto const &pluginRole: Role::AllRoles()) {
        pluginRole->UnloadContent();
    }
    for (auto const &roleProps: RolePropsMap()) {
        roleProps.second->ResetFuncs();
    }
}