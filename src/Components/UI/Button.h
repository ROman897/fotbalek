//
// Created by roman on 30.4.2017.
//
#include <iostream>
#include <functional>
#include <vector>

#ifndef PV264_PROJECT_BUTTON_H
#define PV264_PROJECT_BUTTON_H

struct Button{
    std::string moveUpButtonTag;
    std::string moveDownButtonTag;
    // all of those are called when the button is clicked
    std::vector<std::function<void(void)>> callBacks;
    bool isSelected;
};

#endif //PV264_PROJECT_BUTTON_H
