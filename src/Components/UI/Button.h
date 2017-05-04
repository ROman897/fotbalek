//
// Created by roman on 30.4.2017.
//
#include <iostream>
#include <functional>
#include <vector>

#ifndef PV264_PROJECT_BUTTON_H
#define PV264_PROJECT_BUTTON_H

struct Button{
    std::string m_moveUpButtonTag;
    std::string m_moveDownButtonTag;
    // all of those are called when the button is clicked
    std::vector<std::function<void(void)>> m_callbacks;

    Button(const std::string &moveUpButtonTag, const std::string &moveDownButtonTag) : m_moveUpButtonTag(
            moveUpButtonTag), m_moveDownButtonTag(moveDownButtonTag) {}

    Button() = default;
};

#endif //PV264_PROJECT_BUTTON_H
