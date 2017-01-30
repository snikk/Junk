//
// Created by Glenn, Jeffrey on 7/25/16.
// Copyright (c) 2016 oxygine. All rights reserved.
//

#ifndef TESTGAME_MACOSX_GAME_H
#define TESTGAME_MACOSX_GAME_H

#include "Actor.h"
#include "Stage.h"

class Game : public oxygine::Actor {
public:
    void init() {
        oxygine::spStage stage = oxygine::getStage();
    }
};


#endif //TESTGAME_MACOSX_GAME_H
