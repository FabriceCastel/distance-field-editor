Distance Field Editor
=====================

A project early in the works that aims to create a 3D modelling tool for OSX using signed disntance
fields.

In the short term, the goal is to set up a window with an associated OpenGL 3.* context that loads
and renders an arbitrary fragment shader with a convenient pre-determined set of uniforms (eg. time,
viewport size, camera position...). The program should be able to reload/compile the shader to later
enable seamless editing - the idea being the user will generate a fragment shader through a simple UI
resembling the likes of a stipped down Maya/Blender/Cinema4D/whatever toolset.
