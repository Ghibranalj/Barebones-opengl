#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include <GLFW/glfw3.h>

namespace Window {

typedef void (*inputCallback)(int key, int scancode, int action, int mods);

void init(unsigned int width, unsigned int height, std::string title,
          bool resizable);
void update();
void destroy();
int shouldClose();
void swapBuffers();
void setInputCallback(inputCallback callback);
void close();
void toggleVsync();
void setVsync(bool enabled);
bool isVsyncEnabled();
void getSize(int &width, int &height);

} // namespace Window

#define Key(x) GLFW_KEY_##x
#define Mouse(x) GLFW_MOUSE_BUTTON_##x
#define Action(x) GLFW_##x
#define Mod(x) GLFW_MOD_##x
#define Joystick(x) GLFW_JOYSTICK_##x
#define Gamepad(x) GLFW_GAMEPAD_BUTTON_##x

#endif /* WINDOW_H_ */
