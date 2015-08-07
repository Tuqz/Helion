# TODO

## General
- [ ] Move build output (and maybe SConstruct file) to build directory

## Engine
- [ ] Input handling
  - [x] Keyboard event handling
  - [x] Keyboard polling
  - [x] Mouse input handling
  - [x] Default camera controls
  - [ ] Rebindable keys
  - [ ] Joystick support
- [ ] More options for window handling
  - [ ] Full screen
  - [ ] Multi-monitor support
  - [ ] Resizable window
  - [ ] Less hardcoded options: load from config file
- [ ] OBJ Loader
  - [x] vertex positions (v, 3, 4, 6 and 7 values supported.)
  - [x] vertex indices (f, Should work with all notations, ignoring texture and normal indices)
  - [x] normals (vn)
  - [x] normal indices (extension of f)
  - [ ] texture coordinates (vt)
  - [ ] texture indices (extension of f)
  - [ ] Material references (needs MTL parser)
  - [x] colors (extension of v)
  - [ ] ~~parameter space vertices~~ (not planned)
  - [ ] What should happen when some v-entries use color and others don't?
- [x] Basic lighting
  - [x] normals
  - [x] diffuse lighting from point source
  - [x] gamma
- [ ] Textures
- [ ] GUI

- [ ] Use const keyword where useful
- [ ] Reduce unneccesary includes
- [ ] Use smart pointers
- [ ] Namespaces
- [ ] Implement copy constructors
- [ ] Add documentation

- [ ] Can we reduce the amount of boilerplate code?

## Improved graphics
- [ ] FSAA/MSAA
- [ ] multiple light sources
- [ ] high dynamic range (HDR)
- [ ] specular lighting 
  - [ ] specular maps
- [ ] bump maps
- [ ] transparency
- [ ] camera transitions

## Physics
