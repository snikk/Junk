#include "ActorFactory.h"
#include "../common.h"
#include "components/Pickup.h"
#include "components/PositionComponent.h"
#include "components/HealthComponent.h"
#include "../io/IOManager.h"

template<class Allocator>
rapidjson::Value * documentToValue(rapidjson::Document & document, Allocator & alloc) {

    rapidjson::Value * rtn = new rapidjson::Value();

    if(document.IsObject()) {
        rtn->SetObject();
        for (rapidjson::Value::MemberIterator itr = document.MemberBegin(); itr != document.MemberEnd(); ++itr) {
            rtn->AddMember(itr->name, itr->value, alloc);
        }
        return rtn;
    } else if (document.IsArray()) {
        rtn->SetArray();
        for (int64_t i = 0; i < document.Size(); i++) {
            rtn->PushBack(document[i], alloc);
        }
        return rtn;
    } else {
        delete rtn;
        return NULL;
    }
}

ActorFactory::ActorFactory(void) {
    m_actorComponentCreators["AmmoPickup"] = CreateAmmoPickup;
    m_actorComponentCreators["HealthPickup"] = CreateHealthPickup;
    m_actorComponentCreators["Position"] = CreatePosition;
    m_actorComponentCreators["Health"] = CreateHealth;
}

StrongActorPtr ActorFactory::CreateActor(const char* actorResource) {
    const char* json = IOManager::readFile(actorResource);
    rapidjson::Document d;
    d.Parse(json);
    if (d.HasParseError()) {
        printf("Actor Parse Error! | offset = %zu | %s\n", d.GetErrorOffset(), GetParseError_En(d.GetParseError()));
        return StrongActorPtr();
    }

    StrongActorPtr pActor(GCC_NEW Actor(GetNextActorId()));
    rapidjson::Value* value = documentToValue(d, d.GetAllocator());
    if (!pActor->Init(*value)) {
        printf("Failed to init actor: %s\n", actorResource);
        return StrongActorPtr();
    }
    
    const rapidjson::Value& comps = (*value)["components"];
    for (int i = 0; i < comps.Size(); i++) {
        //StrongActorComponentPtr pComponent(CreateComponent(nullptr));
        StrongActorComponentPtr pComponent(CreateComponent(comps[i]));
        if (pComponent) {
            pActor->AddComponent(pComponent);
            pComponent->SetOwner(pActor);
        } else {
            if (comps[i].HasMember("type") && comps[i]["type"].IsString())
                printf("Hey hey.  This failed!? | type = %s\n", comps[i]["type"].GetString());
            else
                printf("Hey hey.  This failed!?\n");
            //  Proper error handling.  But commenting it out for now.
            //return StrongActorPtr();
        }
    }

    pActor->PostInit();

    return pActor;
}

StrongActorComponentPtr ActorFactory::CreateComponent(const rapidjson::Value& data) {
    std::string name;
    if (data.IsObject() && data["type"].IsString()) {
        name = std::string(data["type"].GetString());
    } else {
        printf("Must be an object that contains a type.\n");
        return StrongActorComponentPtr();
    }

    StrongActorComponentPtr pComponent;

    auto findIt = m_actorComponentCreators.find(name);
    if (findIt != m_actorComponentCreators.end()) {
        ActorComponentCreator creator = findIt->second;
        pComponent.reset(creator());
    } else {
        printf("Couldn't find ActorComponent name %s\n", name.c_str());
        return StrongActorComponentPtr();
    }

    if (pComponent) {
        if (!pComponent->VInit(data)) {
            printf("Component failed to initialize: %s\n", name.c_str());
            return StrongActorComponentPtr();
        }
    }

    return pComponent;
}

