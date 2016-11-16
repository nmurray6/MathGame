#if !defined(_SCENE_H_)
#define _SCENE_H_

#include <list>
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;

class SceneManager;

class Scene : public CNode {
protected:
	unsigned int m_NameHash;
	bool m_IsActive;
	bool m_IsInputActive;
	SceneManager* m_Manager;
	int SceneDifficulty = 1;
	int SceneMode = 1;

public:
	bool IsActive()
		const {
		return m_IsActive;
	}

	void SetActive(bool active) {
		m_IsActive = active;
	}

	void SetName(const char* name);
	unsigned int GetNameHash()
		const {
		return m_NameHash;
	}

	void SetManager(SceneManager* manager) {
		m_Manager = manager;
	}

	void SetInputActive(bool active) {
		m_IsInputActive = active;
	}

	void SetSceneDifficulty(int diff) {
		SceneDifficulty = diff;
	}

	int GetSceneDifficulty() {
		return SceneDifficulty;
	}

	void SetSceneMode(int mode) {
		SceneMode = mode;
	}

	int GetSceneMode() {
		return SceneMode;
	}

public:
	Scene();
	virtual ~Scene();
	virtual void Init();
	virtual void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
	virtual void Render();
};


class SceneManager {

protected:
	Scene* m_Current;
	Scene* m_Next;
	std::list<Scene*> m_Scenes;

public:
	Scene* GetCurrent() {
		return m_Current;
	}

	SceneManager();
	~SceneManager();

	void SwitchTo(Scene* scene);

	void Update(float deltaTime = 0.0f);
	void Render();
	void Add(Scene* scene);
	void Remove(Scene* scene);
	Scene* Find(const char* name);
};

extern SceneManager* g_pSceneManager;

#endif