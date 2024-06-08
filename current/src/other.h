#define OTHER_H
#include <vector>
// using namespace std; // going to reference the namespace in the code instead

struct vec3d {
    float x,y,z; // same as listing them vertically
};

struct triangle {
    vec3d p[3]; // array of 3 vec3ds
};

// represents the object, grouping of triangles
struct mesh {
    std::vector<triangle> tris;
};

struct mat4x4 {
	float m[4][4] = { { 0 } };
};

void MultiplyMatrixVector(vec3d &i, vec3d &o, mat4x4 &m);

void CrossProductNormalised(vec3d &line1, vec3d &line2, vec3d &o);

float DotProduct(vec3d &line1, vec3d &line2);