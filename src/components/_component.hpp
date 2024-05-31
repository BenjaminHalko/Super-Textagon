#pragma once

class Component {
    int id;
public:
    Component() {
        static int next_id = 0;
        id = next_id++;
    }
};
