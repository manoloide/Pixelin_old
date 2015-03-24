#ifndef EVENTS_H
#define EVENTS_H

class Events
{
public:
	static Events* Instance();

	int mouseButton;
	bool mousePressed;
	int amouseX, amouseY;
	int mouseX, mouseY;
protected:
	Events();
	Events(const Events & ) ;
	Events &operator= (const Events & ) ;
private:
	static Events* instance;
};

#endif