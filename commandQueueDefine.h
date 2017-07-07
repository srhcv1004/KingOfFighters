#pragma once

//큐의 각 버퍼는 1프레임기준. 즉 60당 1초
const int KEYBUFFERSIZE = 60;
const int COMMANDBUFFERSIZE = 10;
const int KEYHOLDCHECKTIME = 10;

const int C_IDLE = 0x00000000;
const int C_UP = 0x00000001;
const int C_DOWN = 0x00000010;
const int C_LEFT = 0x00000100;
const int C_RIGHT = 0x00001000;
const int C_PUNCH = 0x00010000;
const int C_PPUNCH = 0x00100000;
const int C_KICK = 0x01000000;
const int C_PKICK = 0x10000000;

const int KEY_UP = VK_UP;
const int KEY_DOWN = VK_DOWN;
const int KEY_LEFT = VK_LEFT;
const int KEY_RIGHT = VK_RIGHT;
const int KEY_PUNCH = 'Q';
const int KEY_PPUNCH = 'W';
const int KEY_KICK = 'E';
const int KEY_PKICK = 'R';