#ifndef __PICKUP_INTERFACE_H__
#define __PICKUP_INTERFACE_H__

#include "ActorComponent.h"

class PickupInterface: public ActorComponent {
public:
    const static ComponentId COMPONENT_ID;
    virtual ComponentId VGetComponentId(void) const {
        return 7777;//PickupInterface::COMPONENT_ID;
    }

    virtual void VApply(WeakActorPtr pActor) = 0;
};

#endif
