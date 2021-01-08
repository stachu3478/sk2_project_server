#pragma once

class Game {
    public:
        Game();
        virtual ~Game();

        void tick() {}; // TODO: implement
        bool isFinished() { return false; };
};