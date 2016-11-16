#include "SpriteManager.h"

SpriteManager::SpriteManager(){}

SpriteManager::~SpriteManager() {
	DeleteAllSprites();
}

void SpriteManager::Render() {
	SpriteNode* itr = head;
	while (itr != NULL) {
		if(itr->sprite != NULL)
			itr->sprite->Render();
		if (itr->label != NULL)
			itr->label->Render();
		itr = itr->next;
	}
}

void SpriteManager::AddSprite(Sprite* newSprite) {
	if (head == NULL) {
		head = new SpriteNode();
		head->sprite = newSprite;
	}
	else {
		SpriteNode* itr = head;
		SpriteNode* prev = itr;
		while (itr != NULL) {
			prev = itr;
			itr = itr->next;
		}

		prev->next = new SpriteNode();
		prev->next->sprite = newSprite;
	}

}

void SpriteManager::AddLabel(Label* newLabel) {
	if (head == NULL) {
		head = new SpriteNode();
		head->label = newLabel;
	}
	else {
		SpriteNode* itr = head;
		SpriteNode* prev = itr;
		while (itr != NULL) {
			prev = itr;
			itr = itr->next;
		}

		prev->next = new SpriteNode();
		prev->next->label = newLabel;
	}

}

void SpriteManager::DeleteAllSprites() {
	SpriteNode* itr = head;
	SpriteNode* prev;
	while (itr != NULL) {
		prev = itr;
		itr = itr->next;
		delete prev;
	}
}