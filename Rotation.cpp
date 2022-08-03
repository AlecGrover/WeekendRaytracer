//
// Created by alecg on 8/2/2022.
//

#include "Rotation.h"

Rotation::Rotation() {
    right= {1, 0, 0};
    up= {0, 1, 0};
    forward= {0, 0, 1};
}

void Rotation::rotate(Vector3 rotation) {

    right= right.rotate_around_axis(up, rotation.y());
    forward= forward.rotate_around_axis(up, rotation.y());

    up= up.rotate_around_axis(right, rotation.x());
    forward= forward.rotate_around_axis(right, rotation.x());

    right= right.rotate_around_axis(forward, rotation.z());
    up= up.rotate_around_axis(forward, rotation.z());

}


