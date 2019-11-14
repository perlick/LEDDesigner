# LEDDesigner #

LEDDesigner is ardiono program that controls ws2812b addressable LED strips. It has several animation functions that can be run concurrently on different parts of an LED strip.

## Installation ##

To run this on an arduino open the sketch_LED_test.ino file in the arduino IDE and upload it to your arduino uno. Connect your LED strip to the arduino by following the pin connections in pins.jpg (LED power source connected seperately. I'll put up a better graphic soon).

## Usage ##

If you have an IR remote, you may need to change the button mapping to work with your remote. Otherwise, you can add animation functions to the loop() to have an animation run continuously. Because this project is in development, it isn't plug-n-play yet.

## Contributing ##

Pull requests are welcome. I have a few goals for this project that contributions should work towards.
1. Adding unique, flexible animation functions.
    1. These should follow similar formats to fade() and walk_loop(). Being able to run concurrently with other animations and leaving plenty of room for adapability.
    2. Animation functions should use a minimal amount of memory. Space on the arduino uno is limited and can easily be overused. Each function animation should be simple and combined with other functions to make more interesting effects.
2. Adding documentation.
    1. I'd like this project to be easily accessable to people with limited programming knowledge. Adding a list of recomended products and setup guides would be great.
3. Animation design studio.
    1. I hope to create some kind of animation design program to let people design a sequesnce of animations with a graphical interface then have that animation sequence be converted into a .ino file that can be run on the arduino.
