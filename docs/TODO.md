# TODO

## General
- [ ] Move build output (and maybe SConstruct file) to build directory

## Engine
- [ ] Input handling
  - [x] Keyboard event handling
  - [ ] Keyboard polling
  - [ ] Mouse input handling
- [ ] More options for window handling
  - [ ] Full screen
  - [ ] Multi-monitor support
  - [ ] Resizable window
  - [ ] Less hardcoded options: load from config file
- [ ] OBJ Loader
  - [x] vertex positions (v, 3, 4, 6 and 7 values supported.)
  - [x] vertex indices (f, Should work with all notations, ignoring texture and normal indices)
  - [ ] normals (vn)
  - [ ] normal indices (extension of f)
  - [ ] texture coordinates (vt)
  - [ ] texture indices (extension of f)
  - [ ] Material references (needs MTL parser)
  - [x] colors (extension of v)
  - [ ] ~~parameter space vertices~~ (not planned)
- [ ] Lighting
  - [ ] normals
  - [ ] diffuse lighting from point source
  - [ ] specular lighting
  - [ ] multiple sources
  - [ ] dynamic range
- [ ] Textures
- [ ] Fix handling of window close and `exit()` in `Game`

- [ ] Use const keyword where useful
- [ ] Namespaces
- [ ] Implement copy constructors
- [ ] Add documentation

- [ ] Can we reduce the amount of boilerplate code?
- [ ] Improve ease-of-use

## Physics
