#ifndef __AI_H__
#define __AI_H__

#include <actor/ActorComponent.h>
#include <actor/components/PositionComponent.h>
#include "Health.h"
#include <drawing/Camera.h>

class PlayerComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void);
    virtual void VUpdate(int deltaMs);

    float speed;

    int forward;
    int backward;
    int left;
    int right;
    std::weak_ptr<Camera2D> camera;
    glm::vec2 direction;
    glm::vec2 center;

private:
    std::weak_ptr<HealthComponent> pHealth;
    std::weak_ptr<PositionComponent> pPosition;
};

class BulletComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void);
    virtual void VUpdate(int deltaMs);

    glm::vec2 direction;
    float damage;
    float speed;
    int ownerId;

private:
    std::weak_ptr<PositionComponent> pPosition;
};

class GunComponent : public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;

    virtual bool VInit(const rapidjson::Value& data);
    virtual ComponentId VGetId(void) const { return COMPONENT_ID; };
    virtual ComponentId VGetComponentId(void) const { return VGetId(); }
    virtual void VPostInit(void);
    virtual void VUpdate(int deltaMs);

    int fireRate;
    int bulletsPerShot;
    float spread;
    float bulletSpeed;
    int bulletDamage;

    bool CanFire() const { return frameCounter > fireRate; }
    void Reset() { frameCounter = 0; }

private:
    float frameCounter;
};

extern ActorComponent* CreatePlayerAI();
extern ActorComponent* CreateBulletComp();
extern ActorComponent* CreateGunComp();

#endif
