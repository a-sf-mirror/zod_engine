#include "gmm_multiplayer.h"

GMMMultiplayer::GMMMultiplayer()
{
	menu_type = GMM_MULTIPLAYER;
	title = "Multiplayer";
	w = 112;
	h = 118;

	SetupLayout1();
}

void GMMMultiplayer::SetupLayout1()
{
	int next_y;

	next_y = GMM_TITLE_MARGIN;

	host_textbox.SetCoords(GMM_SIDE_MARGIN, next_y);
	host_textbox.SetDimensions(w - (GMM_SIDE_MARGIN * 2), MMTEXT_BOX_HEIGHT);
	host_textbox.SetSelected(true);
	host_textbox.SetText("test");
	AddWidget(&host_textbox);
	next_y += MMTEXT_BOX_HEIGHT;

	h = next_y + GMM_BOTTOM_MARGIN;

	//needed if w is ever changed / set
	UpdateDimensions();
}

void GMMMultiplayer::HandleWidgetEvent(int event_type, ZGMMWidget *event_widget)
{

}
