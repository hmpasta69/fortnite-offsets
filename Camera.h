#pragma once

#define M_PI 3.14159265358979323846

struct CamewaDescwipsion {
    Vector3 Location;
    Vector3 Rotation;
    float FieldOfView;
};

Camera GetViewAngles() {
    CamewaDescwipsion camera;
    auto locationPointer = read<uintptr_t>(LocalPtrs::Gworld + 0x178);
    auto rotationPointer = read<uintptr_t>(LocalPtrs::Gworld + 0x188);

    struct Rotation {
        double a;
        char pad_0008[24];
        double b;
        char pad_0028[424];
        double c;
    };
    Rotation rotation;
    rotation = read<Rotation>(rotationPointer);

    camera.Location = read<Vector3>(locationPointer);
    camera.Rotation.x = asin(rotation.c) * (180.0 / M_PI);
    camera.Rotation.y = ((atan2(rotation.a * -1, rotation.b) * (180.0 / M_PI)) * -1) * -1;
    camera.FieldOfView = read<float>(LocalPtrs::PlayerController + 0x3AC) * 90.f;

    return { camera.Location, camera.Rotation, camera.FieldOfView };
}
