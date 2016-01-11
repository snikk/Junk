#ifndef __POSITION_H__
#define __POSITION_H__

#include "../ActorComponent.h"

class PositionComponent : public ActorComponent {
public:
    ~PositionComponent() { printf ("Destroyed this Position Component %u\n", VGetId()); }
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void) { printf("Position component | x = %f | y = %f | z = %f\n", x, y, z); }

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

extern ActorComponent* CreatePosition();

#endif
