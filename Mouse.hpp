#pragma once

struct MouseEvent{
    char data[3];
    char xrel();
    char yrel();
    bool lmb();
    bool rmb();
    //unsigned char xrel, yrel;
    //bool lmb, rmb, mmb;
};

bool PollMouseEvent(MouseEvent &e);