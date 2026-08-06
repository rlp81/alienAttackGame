#pragma once
#include "gameHeader.h"
/*
* BackgroundPixie.h
* Description: Header file for the BackgroundPixie class
* Author: Cole
*/

// The basic Pixie class for the game's background
class BackgroundPixie : public Pixie {
public:

	// Constructors

	/*
	* BackgroundPixie(string& textureFile)
	* Params: textureFile - The file to be loaded as the background
	* Returns: None
	* Desc: Create the games background
	*/
	BackgroundPixie(const std::string& textureFile) : Pixie(PIXIE_TYPE_BACKGROUND, textureFile, true) {
		setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE); // Set the scale to the default Pixie scale
	}

	/*
	* create(string& textureFile)
	* Params: textureFile - The file to be loaded as the background
	* Returns: shared_ptr<BackgroundPixie>
	* Desc: Create the games background as a shard pointer and adds it to the active Pixies vector
	*/
	static shared_ptr<BackgroundPixie> create(string textureFile) {
		auto pixie = make_shared<BackgroundPixie>(textureFile); // Create the BackgroundPixie as a shared pointer
		pixies[pixie->pixieID] = pixie; // Add the Pixie to the active Pixies vector
		return pixie; // Return the created Pixie0
	}
};
