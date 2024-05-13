#ifndef BALLJUMP_ANIMATION_H
#define BALLJUMP_ANIMATION_H

struct Animation{
    int index;
    int frames;
    int speed;

    Animation(){}
    Animation(int i, int f, int s){
        index = i;
        frames = f;
        speed = s;
    }
};







#endif //BALLJUMP_ANIMATION_H
