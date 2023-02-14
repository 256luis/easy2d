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

    ['A'] = {
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['B'] = {
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['C'] = {
        0, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['D'] = {
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['E'] = {
        1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['F'] = {
        1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['G'] = {
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['H'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['I'] = {
        1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['J'] = {
        0, 0, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['K'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 1, 0, 0,
        1, 0, 1, 0, 0, 0,
        1, 1, 0, 0, 0, 0,
        1, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['L'] = {
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['M'] = {
        1, 0, 0, 0, 1, 0,
        1, 1, 0, 1, 1, 0,
        1, 1, 0, 1, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['N'] = {
        1, 1, 0, 0, 1, 0,
        1, 1, 0, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 0, 1, 1, 0,
        1, 0, 0, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['O'] = {
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['P'] = {
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['Q'] = {
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 0, 1, 0, 0,
        0, 1, 1, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['R'] = {
        1, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 1, 1, 1, 0, 0,
        1, 0, 1, 0, 0, 0,
        1, 0, 0, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['S'] = {
        0, 1, 1, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 0, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['T'] = {
        1, 1, 1, 1, 1, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['U'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['V'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['W'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        1, 0, 1, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['X'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 1, 0, 1, 0, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['Y'] = {
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        1, 0, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
    },

    ['Z'] = {
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 1, 0,
        0, 0, 0, 1, 0, 0,
        0, 0, 1, 0, 0, 0,
        0, 1, 0, 0, 0, 0,
        1, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,        
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
    int cursor_x = x;
    int cursor_y = y;
    for (/* nothing here */; *text != 0; text++)
    {
        if (*text == '\n')
        {
            cursor_y += TEXT_HEIGHT;
            cursor_x = x;
            continue;
        }
        
        for (int row = 0; row < TEXT_HEIGHT; row++)
        {
            for (int col = 0; col < TEXT_WIDTH; col++)
            {
                if (chars[*text][col + (row * TEXT_WIDTH)])
                    e2d_set_pixel(window, col + cursor_x, row + cursor_y, color);
            }
        }

        cursor_x += TEXT_WIDTH;
    }
}
