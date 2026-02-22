#pragma once
#include "gameHeader.h"

const string DEFAULT_EXPLOSION_TEXTURE = "explosionf";
const int EXPLOSION_FRAMES = 18;
const int NEXT_EVERY_FRAME = 6;
class ExplosionPixie : public Pixie {
private:
	vector<string> textureFiles;
	int lastFrame;
	int startFrame;
	float posX;
	float posY;
	int spriteNum;
	int textureNums;
	float scaleIncrement;
	float currentScale;
	string baseTextureFile;
	static vector<int> explosionPixies;
public:
	ExplosionPixie(const string& baseTextureFile, int textureNums);
	ExplosionPixie(const string& baseTextureFile, int textureNums, sf::Vector2f& position);
	virtual ~ExplosionPixie() = default;
	void update();
	static void updateAll();
	bool isFinished();
	static shared_ptr<ExplosionPixie> create(int textureAmount, const string& textureFile);
	static shared_ptr<ExplosionPixie> create(int textureAmount, const string& textureFile, sf::Vector2f position);
	static shared_ptr<ExplosionPixie> create(int type, const std::string& textureFile, bool useOriginalOrigin) = delete;
};