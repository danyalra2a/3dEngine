#include <vector>
#include "other.h"

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m) {
    // note: the & means you're passing references in the declaration
    // this is a feature of c++ not c, may confuse me
    o.x = m.m[0][0]*i.x + m.m[0][1]*i.y + m.m[0][2]*i.z + m.m[0][3];
    o.y = m.m[1][0]*i.x + m.m[1][1]*i.y + m.m[1][2]*i.z + m.m[1][3];
    o.z = m.m[2][0]*i.x + m.m[2][1]*i.y + m.m[2][2]*i.z + m.m[2][3];
    float w = m.m[3][0]*i.x + m.m[3][1]*i.y + m.m[3][2]*i.z + m.m[3][3];

    if (w!= 0.0f){
        o.x /= w;
        o.y /= w;
        // This part is sketchy... so I ignored it, so not truly homogeneous coordinates...
        // o.z /= w;
    }

    // correct for screen increasing y in down direction
    o.y *= -1;

    // printf("after x coord: %f\n", o.x);
    // printf("after y coord: %f end\n", o.y);

    // printf("y coord: %f \n", o.y);
}

void CrossProductNormalised(vec3d &line1, vec3d &line2, vec3d &o) {
    o.x = line1.y * line2.z - line1.z * line2.y;
    o.y = line1.z * line2.x - line1.x * line2.z;
    o.z = line1.x * line2.y - line1.y * line2.x;

    float mag = sqrtf(o.x*o.x + o.y*o.y + o.z*o.z);
    o.x/=mag; o.y/=mag; o.x /=mag;
}

float DotProduct(vec3d &line1, vec3d &line2) {
    return line1.x * line2.x + line1.y * line2.y + line1.z * line2.z;
}