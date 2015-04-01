#include "view.h"


struct Pixel
{	
	int x;
	int y;
};

View::View(Layout* _parent) : Widget(_parent)
{
	setBackgroundColor(0x494E4A);
	canvas = new Graphics(40, 40);
	canvas->background(240);

	scale = 4; 
	posx = 10;//-canvas->w/2;
	posy = 10;//-canvas->h/2;
}

void View::update()
{
	if(events->mousePressed && events->mouseButton == SDL_BUTTON_MIDDLE)
	{
		posx += events->mouseX-events->amouseX;
		posy += events->mouseY-events->amouseY;
	}

	int amx = events->amouseX-posx-realLeft;
	int amy = events->amouseY-posy-realTop;
	int mx = events->mouseX-posx-realLeft;
	int my = events->mouseY-posy-realTop;
	int cmx = events->cmouseX-posx-realLeft;
	int cmy = events->cmouseY-posy-realTop;

	if(events->mousePressed)
	{

		if(global->tool == 0)
		{
			if(events->mouseButton == SDL_BUTTON_LEFT)
			{
				if(events->Ctrl && mx >= 0 && mx/scale < canvas->w && my >= 0 && my/scale < canvas->h)
				{
					global->colorSelect = canvas->getPixel(mx/scale, my/scale);
				}
				else
				{
					canvas->strokeColor = global->colorSelect;
					canvas->line(amx/scale, amy/scale, mx/scale, my/scale);
				}

			}
		}
		else if(global->tool == 1)
		{
			if(events->mouseButton == SDL_BUTTON_LEFT && events->mouseClicked)
			{
				int x = mx/scale;
				int y = my/scale;
				bool continguous = true;
				int tolerance = 0; //0-255 
				Uint32 colNew = global->colorSelect;
				Uint32 colSus = canvas->getPixel(x, y);

				if(continguous)
				{
					std::vector<Pixel> pixels, analyzed, replace;
					pixels.push_back({x, y});

					bool finish = false;

					while(!finish)
					{
						for(int i = 0; i < pixels.size(); i++)
						{
							Pixel ap = pixels[i];
							Uint32 pix = canvas->getPixel(ap.x, ap.y);
							int dr = abs(red(pix)-red(colSus));
							int dg = abs(green(pix)-green(colSus));
							int db = abs(blue(pix)-blue(colSus));
							int dif = (dr+dg+db)/3;
							if(dif <= tolerance)
							{
								replace.push_back(ap);

								if(ap.x-1 >= 0)
								{
									Pixel aux = {ap.x-1, ap.y};
									bool exist = false;
									for(int j = 0; j < analyzed.size(); j++)
									{
										Pixel ana = analyzed[j];
										if(aux.x == ana.x && aux.y == ana.y)
										{
											exist = true;
											j == analyzed.size();
										}
									}
									if(!exist)
									{
										pixels.push_back(aux);
									}
								}
								if(ap.x+1 < canvas->w)
								{
									Pixel aux = {ap.x+1, ap.y};
									bool exist = false;
									for(int j = 0; j < analyzed.size(); j++)
									{
										Pixel ana = analyzed[j];
										if(aux.x == ana.x && aux.y == ana.y)
										{
											exist = true;
											j == analyzed.size();
										}
									}
									if(!exist)
									{
										pixels.push_back(aux);
									}
								}
								if(ap.y-1 >= 0){
									Pixel aux = {ap.x, ap.y-1};
									bool exist = false;
									for(int j = 0; j < analyzed.size(); j++)
									{
										Pixel ana = analyzed[j];
										if(aux.x == ana.x && aux.y == ana.y)
										{
											exist = true;
											j == analyzed.size();
										}
									}
									if(!exist)
									{
										pixels.push_back(aux);
									}
								}

								if(ap.y+1 < canvas->h){
									Pixel aux = {ap.x, ap.y+1};
									bool exist = false;
									for(int j = 0; j < analyzed.size(); j++)
									{
										Pixel ana = analyzed[j];
										if(aux.x == ana.x && aux.y == ana.y)
										{
											exist = true;
											j == analyzed.size();
										}
									}
									if(!exist)
									{
										pixels.push_back(aux);
									}
								}
							}
							analyzed.push_back(ap);
							pixels.erase(pixels.begin() + i);
						}
						if(pixels.size() == 0)
						{
							finish = true;
						}
					}

					for(int i = 0; i < replace.size(); i++)
					{
						Pixel ap = replace[i];
						canvas->setPixel(ap.x, ap.y, colNew);	
					}
				}
				else
				{
					for(int j = 0; j < canvas->h; j++)
					{
						for(int i = 0; i < canvas->w; i++)
						{
							Uint32 pix = canvas->getPixel(i, j);
							int dr = abs(red(pix)-red(colSus));
							int dg = abs(green(pix)-green(colSus));
							int db = abs(blue(pix)-blue(colSus));
							int dif = (dr+dg+db)/3;
							if(dif <= tolerance)
							{
								canvas->setPixel(i, j, colNew);		
							}
						}
					}
				}
			}
		}
	}

	if(global->tool == 2)
	{
		if(events->mouseReleased)
		{
			Uint32 c1 = global->colorSelect;
			Uint32 c2 = color(240);

			int x1 = cmx/scale;
			int y1 = cmy/scale;
			int x2 = mx/scale;
			int y2 = my/scale;

			float dd = dist(x1, y1, x2, y2);
			for(int j = 0; j < canvas->h; j++){
				for(int i = 0; i < canvas->w; i++){
					float vv = dist(i, j, x1, y1)/dd;
					canvas->setPixel(i, j, lerpColor(c1, c2, vv));
				}
			}

		}
	}

	if(events->mouseWheel != 0)
	{	
		int ascale = scale;
		scale += events->mouseWheel;
		if(scale < 1) scale = 1;
	}
}

void View::redraw()
{
	
	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);

	SDL_Surface* aux = SDL_CreateRGBSurface(0, canvas->w*scale, canvas->h*scale, 32, 0, 0, 0, 0);

	SDL_Rect location = {0, 0, canvas->w*scale, canvas->h*scale}; 
	SDL_BlitScaled(canvas->get(), NULL, aux, &location); 
	location = {posx, posy, canvas->w*scale, canvas->h*scale}; 
	SDL_BlitSurface(aux, NULL, getSurface(), &location);

	SDL_FreeSurface(aux);
}