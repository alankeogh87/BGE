Game Engines 1 Assignment:
Alan Keogh
C09299858

For this assignment I plan to make a bipedal robot in the vein of ED209 from the Robocop movie series or Metal Gear Rex for the Metal Gear Solid
video game series.  This animat should walk under its own power and if it is stable and time allows will rotate at the hip allowing it to shoot
at objects that will periodically spawn on the screen.

In order to achieve this I will use the following rigid bodies to build the model:
	- Two long thin boxes that will make up each leg; the lower legs will be connected to the upper via slider joints
	- A cylinder placed between the legs and joined with hinges and angular motors which will act as the hips
	- The body will consist of a cylinder in the front and a large box at back; these will be connected using fixed joints
	- Attached to this will be a box and cylinder to make up each arm; as these will rotate with the body they will also be fixed to the body

Links to pictures and videos:
ED209:	Walk cycle  https://www.youtube.com/watch?v=W9cFSllKYns
		https://encrypted-tbn3.gstatic.com/images?q=tbn:ANd9GcQuJcjuAX9izUAsTWtU-l_tgx5mdUokmpWhopsWI8ym3Y77sFktmA
		http://fc02.deviantart.net/fs48/f/2009/230/a/8/ED_209_rear_alternative_shot_by_nathy_d.jpg
		http://fc01.deviantart.net/fs71/f/2010/287/a/5/ed_209_by_b20vteg-d30r36s.jpg
		http://fc01.deviantart.net/fs48/f/2009/230/e/5/ED_209_by_nathy_d.jpg
		
Metal Gear Rex:	Walk cycle  https://www.youtube.com/watch?v=OCcrdQTBkOc
				http://assets.ign.com/thumbs/2012/03/20/014Rex.jpg
				https://www.nippon-yasan.com/3662-15091-thickbox/metal-gear-solid-metal-gear-rex.jpg
				http://oyster.ignimgs.com/wordpress/stg.ign.com/2012/09/metal-gear-rex-img-1-610x406.jpg
				http://blurppy.files.wordpress.com/2012/09/mg_rex_4992.jpg
				https://encrypted-tbn2.gstatic.com/images?q=tbn:ANd9GcT9XAZMXDBS976IttsXajNrj2ici_4bZhn8qBEqyzjRP0xA5jmv

![Alt text](https://raw.github.com/skooter500/BGE/master/Logo/BGE_Logo_01.png)

* [Course Notes](Course/index.md)
* [Labs](Labs/index.md)
* [Assignment](Course/assignment.md)

My scene graph based, C++ 3D engine that makes use of:
* OpenGL 3 with shaders
* GLEW
* SDL
* SDL_ttf
* Bullet Physics
* GLM
* The Kinect SDK
* FMOD
* The Oculus Rift SDK


The engine supports:

* A C++ API inspired by XNA
* A really cool component based scene graph inspired by Unity
* Load simple 3D models, textures and sounds through a content pipeline
* An API for drawing lines and text
* Physically simulated rigid bodies and a factory for making them
* Kinect Skeletal tracking
* Output to the Oculus rift

To build:

* Download the dependencies from here: http://1drv.ms/1wew5VT
* Unzip to the folder Dependencies in your project 
* Use the included Visual Studio 2013 project files
