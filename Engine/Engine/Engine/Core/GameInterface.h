#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class GameInterface {

public:
	GameInterface() {}
	virtual ~GameInterface() {}

	virtual bool Initialize() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
	//virtual void Draw() = 0; ////FOR 2D ONLY
};

#endif 
