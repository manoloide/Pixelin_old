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

View::~View()
{
	delete canvas;
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

		if(global->tool == PENCIL)
		{
			if((events->mouseClicked || events->mouseDragged) && events->mouseButton == SDL_BUTTON_LEFT)
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
		else if(global->tool == BUCKET)
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

	if(global->tool == GRADIENT)
	{
		if(events->mouseReleased && events->mouseButton == SDL_BUTTON_LEFT)
		{
			Uint32 c1 = global->colorSelect;
			Uint32 c2 = color(240);
			bool radius = false;
			bool linear = false;
			bool angle = false;

			if(global->gradientType == 0) radius = true;
			if(global->gradientType == 1) linear = true;
			if(global->gradientType == 2) angle = true;


			int x1 = cmx/scale;
			int y1 = cmy/scale;
			int x2 = mx/scale;
			int y2 = my/scale;

			float dd = dist(x1, y1, x2, y2);
			if(dd >= 1)
			{
				if(radius)
				{
					for(int j = 0; j < canvas->h; j++){
						for(int i = 0; i < canvas->w; i++){
							float vv = (dd > 0)? dist(i, j, x1, y1)/dd : 1;
							canvas->setPixel(i, j, lerpColor(c1, c2, vv));
						}
					}

				}
				if(linear)
				{
					float ang = atan2(y1-y2, x1-x2);
					float x2 = x1 + cos(ang+M_PI/2)*dd;
					float y2 = y1 + sin(ang+M_PI/2)*dd;
					for(int j = 0; j < canvas->h; j++){
						for(int i = 0; i < canvas->w; i++){
							float d = ((x2-x1)*(j-y1)-(y2-y1)*(i-x1))/dd;
							float v = d/dd;
							canvas->setPixel(i, j, lerpColor(c1, c2, v));
						}
					}
				}
				if(angle)
				{
					float ang = atan2(y1-y2, x1-x2)-M_PI;
					float TWO_PI = M_PI*2;
					for(int j = 0; j < canvas->h; j++){
						for(int i = 0; i < canvas->w; i++){
							float v = map(atan2(y1-j, x1-i)-ang, -M_PI, M_PI, 0, 1);
							if(v > 1) v-=1;
							if(v < 0) v+=1;
							canvas->setPixel(i, j, lerpColor(c1, c2, v));
						}
					}
				}
			}
		}
	}

	if(global->tool == ERASER)
	{
		canvas->strokeColor = global->colorSelect;
		Uint32 c = color(255, 0, 0, 20);
		canvas->setPixel(amx/scale, my/scale, c);
	}

	if(events->mouseWheel != 0)
	{	
		int ascale = scale;
		scale += events->mouseWheel;
		if(scale < 1) scale = 1;


		int mx = events->mouseX-realLeft;
		int my = events->mouseY-realTop;
		int ww = canvas->w;
		int hh = canvas->h;
		posx -= (((mx-posx)*1./(ww*ascale))*(ww*scale - ww*ascale));
		posy -= (((my-posy)*1./(hh*ascale))*(hh*scale - hh*ascale));
	}
}

void View::redraw()
{

	Uint32 col = getBackgroundColor();
	SDL_FillRect(getSurface(), NULL, col);


	SDL_Surface* aux = SDL_CreateRGBSurface(0, canvas->w*scale, canvas->h*scale, 32, 0, 0, 0, 0);
	SDL_Rect location = {0, 0, canvas->w*scale, canvas->h*scale}; 
	SDL_BlitScaled(canvas->get(), NULL, aux, &location); 
	//SDL_SetAlpha(aux,SDL_SRCALPHA,255);
	location = {posx, posy, canvas->w*scale, canvas->h*scale}; 
	SDL_FillRect(getSurface(), &location, 0xFFFFAA00);
	SDL_BlitSurface(aux, NULL, getSurface(), &location);

	SDL_FreeSurface(aux);
}