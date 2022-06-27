#include "core/helpers/misc_helpers.hpp"
#include "core/features/features.hpp"

void commands_features::exec_autoexec() {
	interfaces::engine->execute_cmd("exec autoexec");
	custom_helpers::state_to_console("Command", "Executed autoexec...\n");
}