#pragma once

#include <math.h>

struct Vector2I {
    int x, y;
};

struct Vector2F {
    int x, y;
};

struct Vector3I {
    int x, y, z;
};

struct Vector3F {
    float x, y, z;
};

struct Rotation {
    float pitch, yaw;
};

Vector2I add(Vector2I first, Vector2I second) {
    Vector2I newVec;
    newVec.x = first.x + second.x;
    newVec.y = first.y + second.y;
    return newVec;
}

Vector2F add(Vector2F first, Vector2F second) {
    Vector2F newVec;
    newVec.x = first.x + second.x;
    newVec.y = first.y + second.y;
    return newVec;
}

Vector3I add(Vector3I first, Vector3I second) {
    Vector3I newVec;
    newVec.x = first.x + second.x;
    newVec.y = first.y + second.y;
    newVec.z = first.z + second.z;
    return newVec;
}

Vector3F add(Vector3F first, Vector3F second) {
    Vector3F newVec;
    newVec.x = first.x + second.x;
    newVec.y = first.y + second.y;
    newVec.z = first.z + second.z;
    return newVec;
}

double distance(Vector2I first, Vector2I second) {
    double x = (second.x - first.x) * (second.x - first.x);
    double y = (second.y - first.y) * (second.y - first.y);
    return sqrt(x + y);
}

double distance(Vector2F first, Vector2F second) {
    double x = (second.x - first.x) * (second.x - first.x);
    double y = (second.y - first.y) * (second.y - first.y);
    return sqrt(x + y);
}

double distance(Vector3I first, Vector3I second) {
    double x = (second.x - first.x) * (second.x - first.x);
    double y = (second.y - first.y) * (second.y - first.y);
    double z = (second.z - first.z) * (second.z - first.z);
    return sqrt(x + y + z);
}

double distance(Vector3F first, Vector3F second) {
    double x = (second.x - first.x) * (second.x - first.x);
    double y = (second.y - first.y) * (second.y - first.y);
    double z = (second.z - first.z) * (second.z - first.z);
    return sqrt(x + y + z);
}

//  ***************************************************************** //
//                                                                    //
//                      Convertion to Vector2I                        //
//                                                                    //
//  ***************************************************************** //


Vector2I Vector2Fto2I(Vector2F vector) {
    Vector2I newVec;
    newVec.x = (int)vector.x;
    newVec.y = (int)vector.y;
    return newVec;
}

Vector2I vector3Ito2I(Vector3I vector) {
    Vector2I newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    return newVec;
}

Vector2I vector3Fto2I(Vector3F vector) {
    Vector2I newVec;
    newVec.x = (int)vector.x;
    newVec.y = (int)vector.y;
    return newVec;
}

//  ***************************************************************** //
//                                                                    //
//                      Convertion to Vector2F                        //
//                                                                    //
//  ***************************************************************** //

Vector2F vector2Ito2F(Vector2I vector) {
    Vector2F newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    return newVec;
}

Vector2F vector3Ito2F(Vector3I vector) {
    Vector2F newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    return newVec;
}

Vector2F vector3Fto2F(Vector3F vector) {
    Vector2F newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    return newVec;
}

//  ***************************************************************** //
//                                                                    //
//                      Convertion to Vector3I                        //
//                                                                    //
//  ***************************************************************** //

Vector3I vector2Ito3I(Vector2I vector) {
    Vector3I newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    newVec.z = 0;
    return newVec;
}

Vector3I vector2Fto3I(Vector2F vector) {
    Vector3I newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    newVec.z = 0;
    return newVec;
}

Vector3I vector3Ito3I(Vector3F vector) {
    Vector3I newVec;
    newVec.x = (int)vector.x;
    newVec.y = (int)vector.y;
    newVec.z = (int)vector.z;
    return newVec;
}

Vector3I vector2Ito3I(Vector2I vector, float newZ) {
    Vector3I newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    newVec.z = newZ;
    return newVec;
}

Vector3I vector2Fto3I(Vector2F vector, float newZ) {
    Vector3I newVec;
    newVec.x = (int)vector.x;
    newVec.y = (int)vector.y;
    newVec.z = newZ;
    return newVec;
}

//  ***************************************************************** //
//                                                                    //
//                      Convertion to Vector3F                        //
//                                                                    //
//  ***************************************************************** //

Vector3F vector2Ito3F(Vector2I vector) {
    Vector3F newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    newVec.z = 0;
    return newVec;
}

Vector3F vector2Fto3F(Vector2F vector) {
    Vector3F newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    newVec.z = 0;
    return newVec;
}

Vector3F vector3Ito3F(Vector3I vector) {
    Vector3F newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    newVec.z = (float)vector.z;
    return newVec;
}

Vector3F vector2Ito3F(Vector2I vector, float newZ) {
    Vector3F newVec;
    newVec.x = (float)vector.x;
    newVec.y = (float)vector.y;
    newVec.z = newZ;
    return newVec;
}

Vector3F vector2Fto3F(Vector2F vector, float newZ) {
    Vector3F newVec;
    newVec.x = vector.x;
    newVec.y = vector.y;
    newVec.z = newZ;
    return newVec;
}