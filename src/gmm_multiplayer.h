#ifndef _ZGMM_MULTIPLAYER_H_
#define _ZGMM_MULTIPLAYER_H_

#include "zgui_main_menu_base.h"

class GMMMultiplayer : public ZGuiMainMenuBase
{
public:
	GMMMultiplayer();

private:
	GMMWTextBox host_textbox;

	void SetupLayout1();

	void HandleWidgetEvent(int event_type, ZGMMWidget *event_widget);
};

#endif
