#pragma once
#include "gameHeader.h"

class BackgroundPixie : public Pixie {
public:
	BackgroundPixie(const std::string& textureFile) : Pixie(PIXIE_TYPE_BACKGROUND, textureFile, true) {
		setScale(DEFAULT_PIXIE_SCALE, DEFAULT_PIXIE_SCALE);
	}
	static shared_ptr<BackgroundPixie> create(string textureFile) {
		auto pixie = make_shared<BackgroundPixie>(textureFile);
		pixies.push_back(pixie);
		return pixie;
	}
};