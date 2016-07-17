#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "renderable.h"
#include "../primitives/texture.h"
#include "../../resources/resource.h"

class Background : public Renderable
{
public:
	Background(Engine* engine, const std::shared_ptr<GL30Texture>& diffuse, float scale = 1);
	virtual ~Background();
	
	void setDiffuse(std::shared_ptr<GL30Texture> texture);
    std::shared_ptr<GL30Texture> getDiffuse() const;
	
	void setNormal(std::shared_ptr<GL30Texture> texture);
    std::shared_ptr<GL30Texture> getNormal() const;

    virtual void enableForRender();

    void push(lua_State* L, Renderable* ptr);
    void push(lua_State* L, std::shared_ptr<Renderable> ptr);
private:
    std::shared_ptr<GL30Texture> _diffuse;
    std::shared_ptr<GL30Texture> _normal;
	float _scale;

};

#endif // BACKGROUND_H
