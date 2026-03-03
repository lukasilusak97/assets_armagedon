#include "world/plugin_role_tools.h"
#include "world/role_props.h"
#include "world/world.h"

using namespace std;
using namespace ella;
using namespace ella::utils;
using namespace ella::world;

namespace ella::roles::vehicle_control_buggy 
{
struct Data : public Base
{
};

IDKEY(vehicle_control_buggy);
VKEY(example_var);

auto Ready(RoleRef r)
{
    LogD("Example var: {}", r->GetInt(example_var));
}

auto RegRole()
{
    auto &p = InitRole(id, "vehicle_control_buggy");
    p.SetCore<Data>();
    p.Category("examples");
    p.AddGroup(RoleGroups::step);

    p.AddInt(example_var);

    p.ready = Ready;
    return true;
}

static auto ok = AddRoleReg(RegRole);
} // namespace ella::roles::vehicle_control_buggy