#ifndef model_h
#define model_h

#include <vector>
#include "Mesh.h"
#include "math/Vector3.h"

class Model: public Mesh {
private:
    const char* filename;
    bool loadOBJ(const char * path);
    std::string getBaseDir (const std::string str);

public:
    Model();
    Model(const char * path);
    virtual ~Model();

    bool load();

};


#endif /* model_h */
