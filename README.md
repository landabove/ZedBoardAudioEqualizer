# ZedBoard Audio Equalizer Project

-- Sean Kerr, Dan LaBove, Luke Jaffe --

## Programming conventions
    -Each block/subblock should be a struct with associated functions,
    like the lab 4 skeleton code
        -Block names should be capital words, no under scores:
        e.g. AudioOutput
        -Block structs should be typedefed to the same name followed
        by _t:
        e.g. 
        typedef struct
        {
        } AudioOutput_t;
        -Block member functions should be the block name separated
        from the function name with an underscore:
        -Member function names should be camel case:
        e.g. AudioOutput_volumeIncrease
        -Member functions should take a pointer to the associated
        struct as input
        e.g. void AudioOutput_volumeIncrease(AudioPlayer_t *p_this)
    -Variables/function parameters should be all lowercase 
    separated by underscores
    -Function bodies, conditional bodies, and loop bodies should
    get a new line for both curly brackets:
    e.g.
    void func()
    {
        int i;
        for (i = 0; i < 10; i++)
        {
            if (i > 5)
            {
                break;
            }
        }
    }
