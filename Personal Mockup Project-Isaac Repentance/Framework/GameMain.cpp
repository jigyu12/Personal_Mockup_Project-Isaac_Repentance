#include "pch.h"

int main()
{
    GAME.Init(L"The Binding Of Isaac : Repentance");
    GAME.TotalUpdate();
    GAME.Release();

    return 0;
}