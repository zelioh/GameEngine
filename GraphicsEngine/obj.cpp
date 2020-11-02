#include "obj.h"

void Obj::ReadFile(std::string file)
{
    vPoints.clear();
    objects.clear();
    objectSelected = -1;
    std::fstream newfile;
    newfile.open(file, std::ios::in);
    if (newfile.is_open()) {
        std::string line;
        while (std::getline(newfile, line)) {
            ReadLine(line);
        }
        newfile.close();
    }
}

void Obj::ReadLine(std::string line)
{
    std::stringstream ss(line);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vstrings(begin, end);
    if (vstrings.size() > 1) {
        if (vstrings[0] == "o") {
            Object newObj;
            objects.push_back(newObj);
            objectSelected += 1;
            objects[objectSelected].name = vstrings[1];
            vPoints.clear();
        } else if (vstrings[0] == "v") {
            std::vector<float> v;
            int i = 1;
            for (; i < vstrings.size(); i++) {
                v.push_back(std::stof(vstrings[i]));
            }
            for (; i <= 3; i++) {
                v.push_back(0);
            }
            if (i <= 4) {
                v.push_back(1);
            }
            if (!v.empty())
                vPoints.push_back(v);
        } else if (vstrings[0] == "f" && objectSelected != -1) {
            ObjectFace objFace;
            for (int i = 1; i < vstrings.size(); i++) {
                ObjectPoint objPoint;
                int vPos = std::stoi(vstrings[i]);
                if (vPoints.size() >= vPos) {
                    objPoint.x = vPoints[vPos - 1][0];
                    objPoint.y = vPoints[vPos - 1][1];
                    objPoint.z = vPoints[vPos - 1][2];
                    objPoint.w = vPoints[vPos - 1][3];
                }
                objFace.points.push_back(objPoint);
            }
            if (!objFace.points.empty())
                objects[objectSelected].faces.push_back(objFace);
        }
    }
}

std::vector<Object> Obj::GetObjects() const
{
    return objects;
}

void Obj::PrintFaces() const
{
    for (int i = 0; i < objects.size(); i++) {
        std::cout << "object " << objects[i].name << " : " << std::endl;
        for (int u = 0; u < objects[i].faces.size(); u++) {
            std::cout << "    face " << u + 1 << " : ";
            for (int y = 0; y < objects[i].faces[u].points.size(); y++) {
                std::cout << "[";
                std::cout << " x=" << objects[i].faces[u].points[y].x;
                std::cout << " y=" << objects[i].faces[u].points[y].y;
                std::cout << " z=" << objects[i].faces[u].points[y].z;
                std::cout << " w=" << objects[i].faces[u].points[y].w;
                std::cout << " ]";
            }
            std::cout << std::endl;
        }
    }
}