#include "dependencies/utilities/csgo.hpp"
#include "core/features/features.hpp"
#include "core/menu/variables.hpp"

// Same as aimbot but for recoil crosshair
bool recoil_crosshair_weapon_check() {
	weapon_t* active_weapon = csgo::local_player->active_weapon();
	if (!active_weapon) return false;
	const weapon_info_t* weapon_data = active_weapon->get_weapon_data();
	if (!weapon_data) return false;

	switch (weapon_data->weapon_type) {												// Only draw recoil crosshair on weapons that shoot
		case WEAPONTYPE_MACHINEGUN:
		case WEAPONTYPE_RIFLE:
		case WEAPONTYPE_SUBMACHINEGUN:
		case WEAPONTYPE_SHOTGUN:
		case WEAPONTYPE_SNIPER_RIFLE:
		case WEAPONTYPE_PISTOL:
			break;
		default:
			return false;
	}

	return true;
}

// TODO: Improve the aim punch and fov thing
void visuals::crosshair::recoil_crosshair() {
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;
	if (!csgo::local_player) return;
	if (!variables::misc_visuals::recoil_crosshair) return;

	player_t* local_player_ent = (csgo::local_player->is_alive()) ? csgo::local_player : reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity_handle(csgo::local_player->observer_target()));
	if (!local_player_ent->is_alive()) return;
	if (local_player_ent->is_scoped()) return;

	if (!recoil_crosshair_weapon_check()) return;	// Weapon does not shoot

	int screen_w, screen_h;
	interfaces::surface->get_screen_size(screen_w, screen_h);
	int x = screen_w / 2;
	int y = screen_h / 2;

	vec3_t punch = csgo::local_player->aim_punch_angle();

	// Subtract the punch from the position
	x -= (screen_w / variables::misc_visuals::custom_fov_slider) * punch.y;
	y += (screen_h / variables::misc_visuals::custom_fov_slider) * punch.x;

	// Give a margin of 1px up, down, left and right
	x = (x == screen_w / 2 - 1 || x == screen_w / 2 + 1) ? screen_w / 2 : x;
	y = (y == screen_h / 2 - 1 || x == screen_h / 2 + 1) ? screen_h / 2 : y;

	visuals::crosshair::draw_custom_crosshair(x, y, true, variables::colors::recoil_crosshair_c);
}