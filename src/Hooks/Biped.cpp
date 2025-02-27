#include "Biped.h"

#include "RE/Offset.h"

namespace Hooks
{
	void Biped::Install()
	{
		static const auto hook = util::MakeHook(RE::Offset::TESNPC::DismemberHeadParts, 0xCD);

		if (!REL::make_pattern<"E8">().match(hook.address())) {
			util::report_and_fail("Biped::BeardSlotPatch failed to install"sv);
		}

		struct Patch : Xbyak::CodeGenerator
		{
			Patch()
			{
				mov(r8d, r12d);
				mov(rdx, rdi);
				mov(rax, reinterpret_cast<std::uintptr_t>(&DismemberBeard));
				call(rax);

				jmp(ptr[rip]);
				dq(hook.address() + 0x5);
			}
		};

		Patch patch{};

		auto& trampoline = SKSE::GetTrampoline();
		_FindHeadPart = trampoline.write_branch<5>(hook.address(), trampoline.allocate(patch));
	}

	RE::BGSHeadPart* Biped::DismemberBeard(
		RE::TESNPC* a_npc,
		RE::NiAVObject* a_actor3D,
		std::uint32_t a_wornMask)
	{
		auto result = _FindHeadPart(a_npc, RE::BGSHeadPart::HeadPartType::kHair);

		static constexpr std::uint32_t beardSlot = 1U << (44 - 30);
		bool wearingBeardSlot = (a_wornMask & beardSlot) != 0;

		RE::BGSHeadPart* beard = nullptr;
		if (a_npc->headParts && a_npc->numHeadParts > 0) {
			for (const auto& headPart : std::span(a_npc->headParts, a_npc->numHeadParts)) {
				if (headPart && headPart->type == RE::BGSHeadPart::HeadPartType::kFacialHair) {
					beard = headPart;
					break;
				}
			}
		}

		if (!beard) {
			return result;
		}

		if (auto beard3D = a_actor3D->GetObjectByName(beard->formEditorID)) {
			if (wearingBeardSlot) {
				beard3D->flags.set(RE::NiAVObject::Flag::kHidden);
			}
			else {
				beard3D->flags.reset(RE::NiAVObject::Flag::kHidden);
			}
		}

		for (const auto& extraPart : beard->extraParts) {
			if (extraPart) {
				if (auto extra3D = a_actor3D->GetObjectByName(extraPart->formEditorID)) {
					if (wearingBeardSlot) {
						extra3D->flags.set(RE::NiAVObject::Flag::kHidden);
					}
					else {
						extra3D->flags.reset(RE::NiAVObject::Flag::kHidden);
					}
				}
			}
		}

		return result;
	}
}
