#include "Collision.h"

void Collision::processVertices(glm::vec3 vector) {
        if (vector.x > right_most_point) {
            right_most_point = vector.x;
        }

        if (vector.x < left_most_point) {
            left_most_point = vector.x;
        }

        if (vector.y > top_most_point) {
            top_most_point = vector.y;
        }

        if (vector.y < bottom_most_point) {
            bottom_most_point = vector.y;
        }

        if (vector.z > front_most_point) {
            front_most_point = vector.z;
        }

        if (vector.z < back_most_point) {
            back_most_point = vector.z;
        }     
}

AABB Collision::calculateBoundingBox() {
    glm::vec3 position = glm::vec3(left_most_point , top_most_point , back_most_point );
    float sizeX = right_most_point - left_most_point;
    float sizeY = top_most_point - bottom_most_point;
    float sizeZ = front_most_point - back_most_point;

    glm::vec3 size = glm::vec3(sizeX , sizeY , sizeZ ) ;

    AABB _aabb;
    _aabb.position = position;
    _aabb.size = size;

    Collision::aabb = _aabb;

    return aabb;
}

bool Collision::CheckCollision(AABB &one, AABB &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.position.x + one.size.x >= two.position.x &&
        two.position.x + two.size.x >= one.position.x;
    // collision y-axis?
    bool collisionY = one.position.y - one.size.y <= two.position.y &&
        two.position.y - two.size.y <= one.position.y;

    bool collisionZ = one.position.z + one.size.z >= two.position.z &&
        two.position.z + two.size.z >= one.position.z;
    // collision only if on both axes
    return collisionX && collisionY && collisionZ;
}

bool Collision::CheckCollisionY(AABB &one, AABB &two) // AABB - AABB collision
{
    bool collisionY = one.position.y - one.size.y <= two.position.y &&
        two.position.y - two.size.y <= one.position.y;

    return collisionY;
}


bool Collision::CheckMassCollision(AABB &one, std::vector<AABB> static_objects) {
    for(AABB object : static_objects) {
        if (CheckCollision(one, object)) {
            return true;
        }
    }
    return false;
}

Mesh Collision::generateBoundingBoxMesh(AABB _aabb, glm::vec4 color) {

    std::vector<Vertex> vertices;
    std::vector<glm::vec3> vert;

    glm::vec3 vertex_1 = glm::vec3(_aabb.position.x, _aabb.position.y, _aabb.position.z + _aabb.size.z);
    glm::vec3 vertex_2 = glm::vec3(_aabb.position.x + _aabb.size.x, _aabb.position.y, _aabb.position.z + _aabb.size.z);
    // glm::vec3 vertex_2 = glm::vec3(right_most_point, top_most_point, front_most_point);
    glm::vec3 vertex_3 = glm::vec3(_aabb.position.x + _aabb.size.x, _aabb.position.y - _aabb.size.y, _aabb.position.z + _aabb.size.z);
    glm::vec3 vertex_4 = glm::vec3(_aabb.position.x, _aabb.position.y - _aabb.size.y,  _aabb.position.z + _aabb.size.z);

    glm::vec3 vertex_5 = glm::vec3(_aabb.position.x, _aabb.position.y - _aabb.size.y,  _aabb.position.z);
    glm::vec3 vertex_6 = glm::vec3(_aabb.position.x + _aabb.size.x, _aabb.position.y - _aabb.size.y, _aabb.position.z);
    glm::vec3 vertex_7 = glm::vec3(_aabb.position.x + _aabb.size.x, _aabb.position.y, _aabb.position.z);
    glm::vec3 vertex_8 = glm::vec3(_aabb.position.x, _aabb.position.y, _aabb.position.z);

    vert.push_back(vertex_1);
    vert.push_back(vertex_2);
    vert.push_back(vertex_3);
    vert.push_back(vertex_4);
    vert.push_back(vertex_5);
    vert.push_back(vertex_6);
    vert.push_back(vertex_7);
    vert.push_back(vertex_8);

    for (glm::vec3 vect : vert) {
        
        Vertex vertex;
        vertex.position = vect;
        vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f);


        if(vect == _aabb.position) {
            vertex.color = color + glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
        } else {
            vertex.color = color;
        }
    
        vertex.texUV = glm::vec2(1.0f, 1.0f);
        vertices.push_back(vertex);
    }

    std::vector<GLuint> indices = {
        0, 1, 2, 3,
        0, 7, 6, 1,
        1, 2, 5, 6,
        6, 1, 0, 7,
        7, 6, 5, 4,
        4, 7, 0, 3
    };

    std::vector<Texture> textures;

    return Mesh(vertices, indices, textures, false);
    
}