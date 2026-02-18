#include "gameHeader.h"
/*
 *  game.cpp
 *     - A simple game loop that allows you to move the ship
 *       and eventually fire a missile. 
 *  AUTHOR: Initial work in this program was completed by Prof. Andy Harbert
 *          Prof. Pat Smith has made modifications (December 2021, 2024 upgrade to 3.0)
 */   

int main()
{
	// Create the window for graphics. 
	//  The "aliens" is the text in the title bar on the window. 
	RenderWindow window(VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Aliens!");
	
	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// To create a Sprite, which is a movable image on the display, 
	// You must first create a Texture 
	// a Texture is an image of pixels. You can load a .png file
	//   or a bitmap file.  These files are in the "Resource files" section of
	//   the solution explorer.  
	// load textures from file into memory. This doesn't display anything yet.
	// Notice we do this *before* going into animation loop.

	// create the ship texture variable, load the image file. 
	Texture shipTexture;
	if (!shipTexture.loadFromFile("ship.png"))
	{
		cout << "Unable to load ship texture!" << endl;
		exit(EXIT_FAILURE);
	}
	// create sprite and load the ship texture in it
	Sprite ship(shipTexture); 
  
	// initial position of the ship will be approx middle of screen
	float shipX = window.getSize().x / 2.0f;
	float shipY = window.getSize().y / 2.0f;
	ship.setPosition({ shipX, shipY });
	ship.setScale({ 1.5, 1.5 });

	// We use the star texture as a background for space in the window.
	//  it makes it more interesting. :)
	Texture starsTexture;
	if (!starsTexture.loadFromFile("stars.jpg"))
	{
		cout << "Unable to load stars texture!" << endl;
		exit(EXIT_FAILURE);
	}

	Sprite background(starsTexture); // the background is a sprite, though we'll never move it around. 
	// The texture file is 640x480, so scale it up a little to cover 800x600 window
	background.setScale({ 1.5, 1.5 });// must include vector2 types in curly braces. 

	// *** You will have to code to load the  texture for the missile here. 
	// Then create the missile Sprite. See how the ship was created above to make this work.
	bool isMissileInFlight = false; // used to know if a missile is 'on screen'. 

	/*
	 *    MAIN GAME LOOP BELOW
	 *     -- define all sprites and variables above. 
	 *
	 * As long as the window is open, keep running the animation loop. 
	 * the window closes when the user clicks the X in the window's upper right corner.
	 * that "event" is "caught and acted upon in the while loop just a few lines below here.
	 */
	while (window.isOpen())
	{
		/* check all the window's events that were triggered since the last iteration of the loop

		 * This while loop checks to see if anything happened since last time
		 * we drew the window and all its graphics. 
		 * In the while test an "optional" variable is created. This is an advanced 
		 *   concept where a variable "might" have a value - it's optional.
		 *   The "window.pollEvent()" function might or might not return an event.
		 *   If it doesn't return an event (no event happened) then the variable "event"
		 *   will not have a value. This will test as false in the while loop. 
		 * 
		 * This is a C++ version 17 function. It is why this solution adds c17 to the properties
		 */
		while (const std::optional event = window.pollEvent()) // get a polling event. 
		{
			// if (event.type == Event::Closed) // Did the user kill the window by pressing the "X"?
			if (event->is<sf::Event::Closed>()) // new 3.0.0 check on event "what *is* it?"
				window.close();
			//else if (event.type == Event::KeyPressed) // did the user press a key on the keyboard?
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				// if the key that was pressed was a space, fire a missile. 
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					// Time to fire the missile. Set it's position above the ship.
					// You can create a Vector Variable to store an X-Y position.
					//   Vector2f missileLocation = ship.getposition(); 
					// Then you can make the missile have this position
					// missile.setPosition(missileLocation); 
					// then you can move the missile "up" and "to the right" by
					//     moving it positive distance in the x direction and 
					//     moving it negative position in the y direction (up)
					//  missile.move({10, -10}); 

					// set the missile boolean to be TRUE!
					isMissileInFlight = true;
				}   
			}
		}

		//===========================================================
		// Everything from here to the end of the loop is where you put your
		// code to produce ONE frame of the animation. The next iteration of the loop will
		// render the next frame, and so on. All this happens ~ 60 times/second.
		//===========================================================

		// draw background first, so everything that's drawn later 
		// will appear on top of background
		window.draw(background);

		// call the function that will move this ship.
		// the "moveship(..)" function checks for arrow keys pressed 
		//    and changes the ships x and y coordinates to move it on the screen.
		moveShip(ship);

		// After checking for ship movement, draw the ship on top of background 
		// (the ship from previous frame was erased when we drew background)
		window.draw(ship);

		if (isMissileInFlight)
		{   
			
			// move it "up" the screen by decreasing 'y' using missile.move({deltax, deltay});
			// in later work you will check to see if the missile hit anything.
			// Don't forget to draw the missile in its new position in the if statement below 

			// Don't forget to see if the missile is off screen!
			//     You can check the Y position of the missile like this:
			//         if (missile.getposition().y ....) {
			// if it's moved off the top, set the boolean to false!
			// if the missile has not gone off the top of the screen, draw it!
			// this is the default now, but the statement below should be inside an if block.
			isMissileInFlight = false; 
				
		}

		// end the current frame; this makes everything that we have 
		// already "drawn" actually shows up on the screen
		window.display();

		// At this point the frame we have built is now visible on screen.
		// Now control will go back to the top of the animation loop
		// to build the next frame. Since we begin by drawing the
		// background, each frame is rebuilt from scratch.

	} // end body of animation loop

	return 0;
}

