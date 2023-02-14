#include <stdbool.h>
#include "easy2d.h"

#define TEXT_HEIGHT 10
#define TEXT_WIDTH 6
#define CHAR_COUNT 127

bool chars[][CHAR_COUNT] = {    
    [' '] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['a'] = {
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
    },
    
    ['b'] = {
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['c'] = {
        0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
    },
    
    ['d'] = {
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0        
    },
    
    ['e'] = {
        0, 0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['f'] = {
        0, 0, 1, 1, 1, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['g'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['h'] = {        
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['i'] = {        
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 1, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['j'] = {        
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['k'] = {        
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 0, 0,
        1, 1, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['l'] = {        
        1, 1, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['m'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 0, 1, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['n'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['o'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['p'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 0, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['q'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        0, 1, 1, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0
    },

    ['r'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
    
    ['s'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['t'] = {        
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['u'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['v'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['w'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['x'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['y'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    ['z'] = {        
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },
};

void e2d_draw_text(e2d_Window* window, const char* text, int x, int y, e2d_Color color)
{
    for (/* nothing here */; *text != 0; text++)
    {
        for (int row = 0; row < TEXT_HEIGHT; row++)
        {
            for (int col = 0; col < TEXT_WIDTH; col++)
            {
                if (chars[*text][col + (row * TEXT_WIDTH)])
                    e2d_set_pixel(window, col + x, row + y, color);
            }
        }

        x += TEXT_WIDTH;
    }    
}
