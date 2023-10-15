#include "Application.h"

int main()
{
	Applciation app(1500, 1500, "RT");

	app.Start();
    
	while (app.IsRuning())
	{
		app.PerFrame();
	}
}
