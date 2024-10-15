#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Lab1 : public gfxc::SimpleScene
    {
     public:
        Lab1();
        ~Lab1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        bool CheckCollisionInterval(float firstX, float firstY, float firstZ,
            float secondX, float secondY, float secondZ, float interval);
        void CycleColorMode();
        void CycleObjectMesh();
        void CycleMovementSpeed();

        GLclampf redVal;
        GLclampf greenVal;
        GLclampf blueVal;
        GLclampf alphaVal;

        std::string meshCycle;
        float meshScaling;
        uint8_t colorMode;

        uint8_t moveTarget;
        float speed;
        float interval;

        float smallX;
        float smallY;
        float smallZ;

        float bigX;
        float bigY;
        float bigZ;
    };
}   // namespace m1
