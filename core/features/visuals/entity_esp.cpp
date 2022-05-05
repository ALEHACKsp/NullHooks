#include "../features.hpp"

void visuals::grenade_projectile_esp() {
	if (!(variables::nade_esp_bool
		|| variables::entitytext_bool
		|| variables::bombtimer_bool)) return;
	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game()) return;
	if (!csgo::local_player) return;

	const int highest_index = interfaces::entity_list->get_highest_index();

	for (int i = 1; i <= highest_index; i++) {
		entity_t* entity = reinterpret_cast<entity_t*>(interfaces::entity_list->get_client_entity(i));
		if (!entity) continue;

		vec3_t origin = entity->origin(), w2s;

		// TODO: Add fire, smoke, etc. effect timer
		// TODO: Add weapons
		switch (entity->client_class()->class_id) {
			/* ------------ NADE PROJECTILES ------------ */
			case cbasecsgrenadeprojectile: {
				if (!math::world_to_screen(origin, w2s)) break;
				const model_t* model = entity->model();
				if (!model) return;

				studio_hdr_t* hdr = interfaces::model_info->get_studio_model(model);
				if (!hdr) return;

				std::string name = hdr->name_char_array;
				if (name.find("incendiarygrenade") != std::string::npos || name.find("fraggrenade") != std::string::npos) {
					render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "frag", true, color(255, 0, 0));
					break;
				}
				render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "flash", true, color(255, 255, 0));
				break;
			}
			case cmolotovprojectile:
			case cinferno:
				if (!math::world_to_screen(origin, w2s)) break;
				render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "fire", true, color(255, 0, 0));
				break;
			case csmokegrenadeprojectile:
				if (!math::world_to_screen(origin, w2s)) break;
				render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "smoke", true, color(0, 160, 255));
				break;
			case cdecoyprojectile:
				if (!math::world_to_screen(origin, w2s)) break;
				render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "decoy", true, color::white(255));
				break;
			/* ------------ BOMB ------------ */
			case cplantedc4:
				entity_info::bomb(entity);
				break;
			case cc4:
				entity_info::dropped_bomb(entity);
				break;
			/* ------------ MISC ------------ */
			case cchicken:
				if (!math::world_to_screen(origin, w2s) || !variables::chickenpride_bool) break;
				render::draw_text_string(w2s.x, w2s.y, render::fonts::watermark_font, "chicken", true, color(255, 0, 255));
				break;
			/* ------------------------------ */
			default:
				break;
		}
	}
}