A T-Pose character has been given life.

For this academic exercise, a rendering engine has been provided. I needed to create a skeleton with bones and to set the skinning indices and weights. A T-Pose character has been provided with 2 animation files, which needed to be parsed into keyframes.

A homemade math library is used in this project.

Controls:

    WASD: Move the camera around.
    Left-Click: Rotate the camera.
    Z: Show / hide the T-Pose skeleton.
    X: Show / hide the animated skeleton.
    F: Cycle through T-Pose, walking and running animations.
    Up / Down Arrows: Controls the speed of the animation. Speed multiplier is shown in console when modified. Animations can be reversed.

Due to an unknown bug in the engine, the application can only run in Win32/Release configuration. The engine's code is obfuscated, so no bug repair is possible. The model character also occasionally doesn't appear. In such a case, simply restart the application until it appears.

Engine developped by ISART Digital, animation programming developped by Gabriel Meloche over the course of 1 week.

Notes:

	- Mesh has been translated slightly backwards from its actual position in the vertex shader to make it easier to see the skeleton.
	
