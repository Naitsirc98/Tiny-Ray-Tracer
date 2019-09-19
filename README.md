# Tiny-Ray-Tracer
A simple Ray Tracer written in C

![Output Image 1920x1080 RGB, 64 samples](https://github.com/Naitsirc98/Tiny-Ray-Tracer/blob/master/Tiny%20Ray%20Tracer/Tiny%20Ray%20Tracer/output_image.png?raw=true "Ray Tracing Scene")

#### This is a C port of [*Ray Tracing in One Weekend*](http://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf) by Peter Shirley. The original code is available [here](https://github.com/RayTracing/raytracing.github.io).


This CPU-only Ray Tracer is totally written in C, with an (almost) Object Oriented design.

What it does is to render a semi-random generated scene to an image (called output_image.png). The result image is antialiased and gamma corrected.

The scene is made up with lots of random placed spheres, each of them with one of these different materials:
- Lamberdian (Diffuse)
- Metal 
- Dielectric (Glass)

The above scene was rendered to a 1920x1080 RGB image, with 64 samples per pixel and gamma correction of 2.2, after approximately 25 minutes, which is a pretty decent rendering time for the CPU.
