#ifndef _GLOBALS_H_
#define _GLOBALS_H_

/**
 * Header for global constants
 */

namespace globals
{
    const int SCREEN_WIDTH{800};
    const int SCREEN_HEIGHT{640};
    const int PIXEL_SIZE{32};
    const int FPS{60};
    const int FRAME_DELAY{1000 / FPS};
    const float SPRITE_SCALE{2.0f};
} // namespace globals

#endif