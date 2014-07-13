#include "zgui_main_menu_widgets.h"

bool GMMWTextBox::finished_init = false;

ZSDL_Surface GMMWTextBox::top_img;
ZSDL_Surface GMMWTextBox::left_img;
ZSDL_Surface GMMWTextBox::right_img;
ZSDL_Surface GMMWTextBox::bottom_img;

GMMWTextBox::GMMWTextBox()
{
	widget_type = MMTEXT_BOX_WIDGET;

	selected = false;
	good_chars_only = false;
	passworded = false;
	do_rerender = false;
	max_text = -1;

	h = MMTEXT_BOX_HEIGHT;
}

void GMMWTextBox::Init()
{
	top_img.LoadBaseImage("assets/other/main_menu_gui/textbox/textbox_top.png");
	left_img.LoadBaseImage("assets/other/main_menu_gui/textbox/textbox_left.png");
	right_img.LoadBaseImage("assets/other/main_menu_gui/textbox/textbox_right.png");
	bottom_img.LoadBaseImage("assets/other/main_menu_gui/textbox/textbox_bottom.png");

	finished_init = true;
}

bool GMMWTextBox::Click(int x_, int y_)
{
	return WithinDimensions(x_, y_);
}

bool GMMWTextBox::KeyPress(int c)
{
	if(!selected) return false;

	if(c == 8) //delete key
	{
		if(text.length())
			text.erase(text.length()-1,1);
	}
	else
	{
		if(max_text != -1 && text.length() >= max_text) return true;
		if(good_chars_only && !good_user_char(c)) return true;

		//add it to the string
		text += c;
	}

	do_rerender = true;

	return true;
}

void GMMWTextBox::MakeTextImage()
{
	string render_str;

	if(passworded)
		render_str = string(text.length(), '*');
	else
		render_str = text;

	if(selected)
		render_str += "{";

	text_img.LoadBaseImage(ZFontEngine::GetFont(SMALL_WHITE_FONT).Render(render_str.c_str()));

	do_rerender = false;
}

void GMMWTextBox::Process()
{
	if(do_rerender) MakeTextImage();
}

void GMMWTextBox::DoRender(ZMap &the_map, SDL_Surface *dest, int tx, int ty)
{
	int ix, iy, iw;
	SDL_Rect dest_box, src_box;

	//backround color = 155,155,155

	if(!finished_init) return;

	if(!top_img.GetBaseSurface()) return;
	if(!left_img.GetBaseSurface()) return;
	if(!right_img.GetBaseSurface()) return;
	if(!bottom_img.GetBaseSurface()) return;

	tx += x;
	ty += y;

	//left
	left_img.BlitSurface(NULL, tx, ty);

	//right
	ix = tx + (w - right_img.GetBaseSurface()->w);
	right_img.BlitSurface(NULL, ix, ty);

	//top
	ix = tx + left_img.GetBaseSurface()->w;
	iw = w - (left_img.GetBaseSurface()->w + right_img.GetBaseSurface()->w);
	top_img.RenderSurfaceHorzRepeat(ix, ty, iw);

	//bottom
	//ix = tx + left_img.GetBaseSurface()->w;
	iy = ty + (h - bottom_img.GetBaseSurface()->h);
	//iw = w - (left_img.GetBaseSurface()->w + right_img.GetBaseSurface()->w);
	bottom_img.RenderSurfaceHorzRepeat(ix, iy, iw);

	//center
	dest_box.x = tx + left_img.GetBaseSurface()->w;
	dest_box.y = ty + top_img.GetBaseSurface()->h;
	dest_box.w = w - (left_img.GetBaseSurface()->w + right_img.GetBaseSurface()->w);
	dest_box.h = h - (top_img.GetBaseSurface()->h + bottom_img.GetBaseSurface()->h);
	ZSDL_Surface::ZSDL_FillRect(&dest_box, 115, 115, 115);

	//text
	if(text_img.GetBaseSurface())
	{
		iw = w - (left_img.GetBaseSurface()->w + right_img.GetBaseSurface()->w);
		iw -= 2;

		if(iw >= text_img.GetBaseSurface()->w) 
			src_box.x = 0;
		else 
			src_box.x = text_img.GetBaseSurface()->w - iw;

		src_box.y = 0;
		src_box.w = iw;
		src_box.h = text_img.GetBaseSurface()->h;

		dest_box.x = tx + left_img.GetBaseSurface()->w + 1;
		dest_box.y = ty + top_img.GetBaseSurface()->h + 1;
		
		text_img.BlitSurface(&src_box, &dest_box);
	}
}
