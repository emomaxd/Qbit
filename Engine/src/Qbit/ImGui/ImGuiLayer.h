#pragma once

#include "Qbit/Core/Layer.h"

#include "Qbit/Events/ApplicationEvent.h"
#include "Qbit/Events/KeyEvent.h"
#include "Qbit/Events/MouseEvent.h"

namespace Qbit {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
	};

}