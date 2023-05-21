# Masken 

A snake clone written in C for educational purposes by Joachim Westlund.

It is coded with [Code::Blocks IDE](https://www.codeblocks.org)

It won't compile on Linux because the use of itoa() function that is not in the ANSI C standard.
But that can easily be changed with snprintf() function. But I will not do it now.
I'm sure there are other things too.

[Simple DirectMedia Layer (SDL2)](https://www.libsdl.org) is used for various things.

* Rendering pixels to the screen
* Image processing
* Music processing
* True type fonts processing

Music from [The Mod Archive](https://modarchive.org) converted to ogg without any other modifications. [License](https://modarchive.org/index.php?terms-upload)

[Worm picture](https://www.kindpng.com/imgv/iRTbwRm_worms-png-file-worm-clip-art-transparent-png/). License: free for personal use.

## How to play:

**From the start screen**

Press space to play.

At any time you can hit ESC-key to go back.

At any time you can change music with keys 1-5, or silence with the 0-key.

**In game:**

Use arrow keys to move the snake around.
You are not allowed to hit the walls or yourself with the head of the snake.

You can "eat" the apple that is somewhere on the play field. Your snake will grow in the direction you came from.
The apple has a random score associated with it and your snake will grow that many sections when "eating". 
It will grow instantly so if you grow into a wall the game is over.

Every 30 seconds the game will speed up until a certain point.