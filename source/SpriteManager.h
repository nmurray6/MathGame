#if !defined(_SPRITEMANAGER_H_)
#define _SPRITEMANAGER_H_

#include "Sprite.h"
#include "Iw2DSceneGraph.h"
#include "Label.h"

using namespace Iw2DSceneGraph;

class SpriteNode {
public:
	Sprite* sprite = NULL;
	Label* label = NULL;
	SpriteNode* next = NULL;

	SpriteNode() {};
	~SpriteNode() { delete sprite; delete label; };
};

class SpriteManager {

public:
	SpriteNode* head = NULL;

public:
	SpriteManager();
	~SpriteManager();
	void Render();
	void AddSprite(Sprite* newSprite);
	void AddLabel(Label* newLabel);
	void DeleteAllSprites();

};

#endif