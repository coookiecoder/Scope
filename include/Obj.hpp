#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../template/Vector.tpp"

class Face {
    private:
        std::vector<int> vertices_index;
        std::vector<int> textures_index;
        std::vector<int> normals_index;

    public:
        Face();
        ~Face();

        [[nodiscard]] const std::vector<int>& getVerticesIndex() const;
        [[nodiscard]] const std::vector<int>& getTexturesIndex() const;
        [[nodiscard]] const std::vector<int>& getNormalsIndex() const;

        [[nodiscard]] int getVerticesIndex(int index) const;
        [[nodiscard]] int getTextureIndex(int index) const;
        [[nodiscard]] int getNormalIndex(int index) const;

        void addVerticesIndex(int vertices);
        void addTexturesIndex(int textures);
        void addNormalsIndex(int normals);
};

std::ostream& operator<<(std::ostream& os, const Face& face);

class Obj {
    private:
        std::vector<Vector3D<float>> vertices;
        std::vector<Vector2D<float>> texture_coordinates;
        std::vector<Vector3D<float>> normals;
        std::vector<Face> faces;

        void parseVertex(const std::string &line);
        void parseTexCoord(const std::string &line);
        void parseNormal(const std::string &line);
        void parseFace(const std::string &line);

    public:
        explicit Obj(const std::string& path);
        ~Obj();

        [[nodiscard]] const std::vector<Vector3D<float>>& getVertices() const;
        [[nodiscard]] const std::vector<Vector2D<float>>& getTextureCoordinates() const;
        [[nodiscard]] const std::vector<Vector3D<float>>& getNormals() const;
        [[nodiscard]] const std::vector<Face>& getFaces() const;
};

std::ostream& operator<<(std::ostream& os, const Obj& obj);