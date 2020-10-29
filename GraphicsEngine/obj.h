#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class ObjectPoint
{
public:
	float x = 0;
	float y = 0;
	float z = 0;
	float w = 1;
private:
};

class ObjectFace
{
public:
	std::vector<ObjectPoint> points;
private:
};

class Object
{
public:
	std::string name;
	std::vector<ObjectFace> faces;
private:
};

class Obj
{
public:
	void ReadFile(std::string file);
	std::vector<Object> GetObjects() const;
	void PrintFaces() const;
private:
	void ReadLine(std::string line);
	std::vector<std::vector<float>> vPoints;
	std::vector<Object> objects;
	int objectSelected;
};

