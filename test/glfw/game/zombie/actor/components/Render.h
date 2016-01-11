#ifndef __RENDER_H__
#define __RENDER_H__

#include <actor/ActorComponent.h>
#include <drawing/SpriteBatch.h>

class RenderComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void) { }

    virtual void draw(SpriteBatch& _spriteBatch);

    ColorRGBA8 color;
};

extern ActorComponent* CreateRender();

#endif
