#include "model.hpp"
#include "shaders.hpp"

#include <memory>
#include <fstream>

Model::Model(const std::string &name) {
    mesh = std::make_unique<Mesh>(MODEL_PATH + name + ".obj");

    // load material
    std::string materialPath = MODEL_PATH + name + ".mtl";

    std::ifstream file(materialPath);
    if (!file.is_open()) {
        ERROR("Failed to open file: " + materialPath);
        return;
    }

    struct mat {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 emissive;
        float specularExponent;
        float transparency;
        float refractionIndex;
        unsigned int illumno;
        std::string kdPath;
        std::string ksPath;
    };

    std::vector<mat> mats;
    std::string line;
    int index = -1;
    while (std::getline(file, line)) {
        std::string delim = " ";
        std::string token = line.substr(0, line.find(delim));
        if (token == "newmtl") {
            mats.push_back(mat());
            index++;
        }
        if (token == "Ns") {
            float specularExponent = 0;
            sscanf(line.c_str(), "Ns %f", &specularExponent);
            mats[index].specularExponent = specularExponent;
        }

        if (token == "Ka") {
            float r, g, b;
            sscanf(line.c_str(), "Ka %f %f %f", &r, &g, &b);
            mats[index].ambient = glm::vec3(r, g, b);
        }
        if (token == "Kd") {
            float r, g, b;
            sscanf(line.c_str(), "Kd %f %f %f", &r, &g, &b);
            mats[index].diffuse = glm::vec3(r, g, b);
        }
        if (token == "Ks") {
            float r, g, b;
            sscanf(line.c_str(), "Ks %f %f %f", &r, &g, &b);
            mats[index].specular = glm::vec3(r, g, b);
        }
        if (token == "Ke") {
            float r, g, b;
            sscanf(line.c_str(), "Ke %f %f %f", &r, &g, &b);
            mats[index].emissive = glm::vec3(r, g, b);
        }
        if (token == "d") {
            float transparency = 0;
            sscanf(line.c_str(), "d %f", &transparency);
            mats[index].transparency = transparency;
        }
        if (token == "Ni") {
            float refractionIndex = 0;
            sscanf(line.c_str(), "Ni %f", &refractionIndex);
            mats[index].refractionIndex = refractionIndex;
        }
        if (token == "illum") {
            unsigned int illumno = 0;
            sscanf(line.c_str(), "illum %u", &illumno);
            mats[index].illumno = illumno;
        }
        if (token == "map_Kd") {
            std::string kdPath = line.substr(line.find(delim) + 1);
            mats[index].kdPath = kdPath;
        }

        if (token == "map_Ks") {
            std::string ksPath = line.substr(line.find(delim) + 1);
            mats[index].ksPath = ksPath;
        }
    }
    for (auto &m : mats) {
        auto material = std::make_shared<Material>(
            m.ambient, m.diffuse, m.specular,m.emissive ,m.specularExponent,
            m.transparency, m.refractionIndex, m.illumno,
            MODEL_PATH + m.kdPath, MODEL_PATH + m.ksPath);
        materials.push_back(material);
    }
}

void Model::draw(ShaderProgram &shader) {
    for (int i = 0; i < materials.size(); i++) {
        materials[i]->use(shader);
        shader.use();
        mesh->draw();
    }
}
