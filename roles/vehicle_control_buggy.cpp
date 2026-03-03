#include "audio/audio.h"
#include "input/input_map.h"
#include "physics/vehicle_commands.h"
#include "physics/vehicle_data.h"
#include "physics/vehicle_state.h"
#include "roles/sound_manager_role.h"
#include "world/game_interface.h"
#include "world/plugin_role_tools.h"
#include "world/sim_module.h"
#include "utils/config.h"

using namespace std;
using namespace ella::utils;
using namespace ella::world;
using namespace ella::input;
using namespace ella::physics;
using namespace ella::roles;

namespace ella::roles::vehicle_control_buggy 
{
struct Data : public Base
{
};

IDKEY(vehicle_control_buggy);

VKEY(vehicle_link);
VKEY(vehicle_role);

auto OnAction(RoleRef r)
{
    auto const & c = GetActionContext();
    auto soundManagerRole = r->GetOrCreateModule(roles::sound_manager::id);
    // auto d = r->GetCore<Data>();
    const auto vehicle = r->GetBase<Role>(vehicle_role);
    if (!vehicle)
    {
        LogLI("No vehicle linked to vehicle control role");
        return;
    }
    LogW("Vehicle input key: {} , value: {}", c->key, c->GetValue());
    if (c->key == "forward" ) 
    {
        vehicle->Set("throttle", c->IsEnabled() ? 1.0 : 0.0);
        vehicle->Set("engine_target_gear", 2);
    }
    if (c->key == "reverse"  ) 
    {
        vehicle->Set("throttle", c->IsEnabled() ? 1.0 : 0.0);
        
        vehicle->Set("engine_target_gear", 0);
    }
    
        
        
    
}

auto Ready(RoleRef r)
{
    auto imp = r->GetRole("user_input")->GetBase<InputMap>();
    imp->OnAnyAction()->AddIfSingle(r, [r]()
    {
        OnAction(r);
    });
    
 
}

auto RegRole()
{
    auto &p = InitRole(id, "vehicle_control_buggy");
    p.SetCore<Data>();
    p.Category("examples");
    p.AddGroup(RoleGroups::step);
    p.AddRoleCachedLink(vehicle_link, vehicle_role).AddFilter("vehicle_base");

    

    p.ready = Ready;
    return true;
}

static auto ok = AddRoleReg(RegRole);
} // namespace ella::roles::vehicle_control_buggy