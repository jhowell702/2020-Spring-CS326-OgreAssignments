class Entity381;

class Aspect{

public:
	Aspect(){};
	Entity381* ent381;
	virtual void Tick(float dt) = 0;
	virtual ~Aspect(){};
};

class Physics : public Aspect{
public:
	Physics();
	Physics(Entity381* entity);
	void Tick(float dt);
	~Physics();

};

class Renderer : public Aspect{
public:
	Renderer();
	Renderer(Entity381* entity);
	void Tick(float dt);
	~Renderer();
};
