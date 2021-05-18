#ifndef _ANIMATION_H_
#define _ANIMATION_H_

struct Animation
{
    int index_;
    int frames_;
    int delay_;

    Animation() {}
    Animation(int index, int frames, int delay) 
        : index_{index}, frames_{frames}, delay_{delay}
    {

    }
};


#endif