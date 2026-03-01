#include "vkHW.hpp"

void vkHW::CreateDevice(SDL_Window* win) {
    auto res = volkInitialize();

    if (res != VK_SUCCESS) {
        Msg("Can't initialize volk: %d" res);
    }

}

void vhHW::Destroy() {

}

void vhHW::Reset() {
    
}

void vhHW::CreateInstance() {
    
}

void vhHW::CreateDevice() {
    
}