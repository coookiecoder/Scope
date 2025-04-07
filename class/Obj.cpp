#include "../include/Obj.hpp"

#include <algorithm>

Face::Face() {

}

Face::~Face() {

}

const std::vector<int>& Face::getVerticesIndex() const {
    return vertices_index;
}

const std::vector<int>& Face::getTexturesIndex() const {
    return textures_index;
}

const std::vector<int>& Face::getNormalsIndex() const {
    return normals_index;
}

int Face::getVerticesIndex(const int index) const {
    return vertices_index[index];
}

int Face::getTextureIndex(const int index) const {
    return textures_index[index];
}

int Face::getNormalIndex(const int index) const {
    return normals_index[index];
}

void Face::addVerticesIndex(const int vertices) {
    vertices_index.push_back(vertices);
}

void Face::addTexturesIndex(const int textures) {
    textures_index.push_back(textures);
}

void Face::addNormalsIndex(const int normals) {
    normals_index.push_back(normals);
}

std::ostream& operator<<(std::ostream& os, const Face& face) {
    auto &vertices = face.getVerticesIndex();
    auto &textures = face.getTexturesIndex();
    auto &normals = face.getNormalsIndex();

    for (int index = 0; index < vertices.size(); ++index) {
        os << vertices[index] << "/" << textures[index] << "/" << normals[index];
        if (index != vertices.size() - 1)
            os << " ";
    }

    return os;
}


void Obj::parseVertex(const std::string &line) {
    float x, y, z;
    std::istringstream iss(line);
    std::string type; // for the "v"
    iss >> type >> x >> y >> z;
    vertices.emplace_back(x, y, z);
}

void Obj::parseTexCoord(const std::string &line) {
    float x, y;
    std::istringstream iss(line);
    std::string type; // for the "vt"
    iss >> type >> x >> y;
    texture_coordinates.emplace_back(x, y);
}

void Obj::parseNormal(const std::string &line) {
    float x, y, z;
    std::istringstream iss(line);
    std::string type; // for the "vn"
    iss >> type >> x >> y >> z;
    normals.emplace_back(x, y, z);
}

void Obj::parseFace(const std::string &line) {
    Face face;
    std::istringstream iss(line);
    std::string type; // for the "f"
    iss >> type;

    std::string token;
    while (iss >> token) {
        std::ranges::replace(token, '/', ' ');
        std::istringstream tokenStream(token);
        int vertexIdx, texCoordIdx, normalIdx;

        tokenStream >> vertexIdx >> texCoordIdx >> normalIdx;
        face.addVerticesIndex(vertexIdx);
        face.addTexturesIndex(texCoordIdx);
        face.addNormalsIndex(normalIdx);
    }
    faces.push_back(face);
}


Obj::Obj(const std::string& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::invalid_argument("File could not be opened");
    }

    std::string line;

    while (getline(file, line)) {
        std::stringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "v") {
            this->parseVertex(line);
        } else if (type == "vt") {
            this->parseTexCoord(line);
        } else if (type == "vn") {
            this->parseNormal(line);
        } else if (type == "f") {
            this->parseFace(line);
        }
    }
}

Obj::~Obj() {

}

const std::vector<Vector3D<float>>& Obj::getVertices() const {
    return vertices;
}

const std::vector<Vector2D<float>>& Obj::getTextureCoordinates() const {
    return texture_coordinates;
}

const std::vector<Vector3D<float>>& Obj::getNormals() const {
    return normals;
}

const std::vector<Face>& Obj::getFaces() const {
    return faces;
}

std::ostream& operator<<(std::ostream& os, const Obj& obj) {
    auto &vertices = obj.getVertices();
    auto &texture_coordinates = obj.getTextureCoordinates();
    auto &normals = obj.getNormals();
    auto &faces = obj.getFaces();

    os << "Vertices: " << vertices.size() << std::endl;
    for (auto item : vertices)
        os << item << std::endl;
    os << std::endl << "Texture coordinates: " << texture_coordinates.size() << std::endl;
    for (auto item : texture_coordinates)
        os << item << std::endl;
    os << std::endl << "Normals: " << normals.size() << std::endl;
    for (auto item : normals)
        os << item << std::endl;
    os << std::endl << "Faces: " << faces.size() << std::endl;
    for (const auto& item : faces)
        os << item << std::endl;

    return os;
}