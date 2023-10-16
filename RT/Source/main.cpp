#include "Application.h"

int main()
{
	Applciation app(1200, 800, "RT");

	app.Start();
    
	while (app.IsRuning())
	{
		app.PerFrame();
	}
}
