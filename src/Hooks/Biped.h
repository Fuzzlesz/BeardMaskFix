#include <xbyak/xbyak.h>

namespace Hooks
{
	class Biped
	{
	public:
		static void Install();

	private:

		inline static REL::Relocation<RE::BGSHeadPart* (*)(RE::TESNPC*, RE::BGSHeadPart::HeadPartType)>
			_FindHeadPart;

	};
}
