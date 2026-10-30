#include "RE/Starfield.h"

namespace
{
	// Mode 1 and 2: the engine's appearance rebuild on the actor, with and without the race-change path.
	// Mode 3: a silent native equip and unequip cycle of the passed token through the ActorEquipManager.
	bool Reset(std::monostate, RE::Actor* a_actor, std::int32_t a_mode, RE::TESObjectARMO* a_token)
	{
		if (!a_actor) {
			return false;
		}
		if (a_mode == 1) {
			a_actor->UpdateAppearance(false, 0, false);
			return true;
		}
		if (a_mode == 2) {
			a_actor->UpdateAppearance(true, 0, true);
			return true;
		}
		if (a_mode == 3) {
			if (!a_token) {
				return false;
			}
			auto* manager = RE::ActorEquipManager::GetSingleton();
			if (!manager) {
				return false;
			}
			RE::BGSObjectInstance instance(a_token, nullptr);
			manager->EquipObject(a_actor, instance, nullptr, false, true, false, true, false);
			manager->UnequipObject(a_actor, instance, nullptr, false, true, false, true, nullptr);
			return true;
		}
		return false;
	}

	void MessageCallback(SFSE::MessagingInterface::Message* a_msg)
	{
		if (a_msg->type == SFSE::MessagingInterface::kPostDataLoad) {
			if (auto* gameVM = RE::GameVM::GetSingleton()) {
				if (auto* vm = gameVM->GetVM()) {
					vm->BindNativeMethod("OrrWT_Native", "Reset", Reset, true, false);
				}
			}
		}
	}
}

SFSE_PLUGIN_LOAD(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);
	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);
	return true;
}
