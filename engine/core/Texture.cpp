#include "Texture.h"
#include "image/TextureLoader.h"


using namespace Supernova;

Texture::Texture(){
    this->textureRender = NULL;
    
    this->texturesData.push_back(NULL);
    this->type = S_TEXTURE_2D;
    
    this->id = "";
}

Texture::Texture(std::string path_id): Texture(){
    this->id = path_id;
}

Texture::Texture(TextureData* textureData, std::string id): Texture(){
    this->texturesData.push_back(textureData);
    this->id = id;
}

Texture::Texture(std::vector<TextureData*> texturesData, std::string id){
    this->texturesData = texturesData;
    this->id = id;
}

void Texture::setId(std::string path_id){
    this->id = path_id;
}

void Texture::setTextureData(TextureData* textureData){
    texturesData[0] = textureData;
}

void Texture::setType(int type){
    this->type = type;
}

bool Texture::load(){

    textureRender = TextureRender::sharedInstance(id);

    if (!textureRender.get()->isLoaded()){

        if (type == S_TEXTURE_2D){
            
            TextureLoader image;
            if (texturesData[0] == NULL){
                texturesData[0] = image.loadTextureData(id.c_str());
            }
            
            texturesData[0]->resamplePowerOfTwo();
            textureRender.get()->loadTexture(texturesData[0]);
            
            delete texturesData[0];
            
            return true;
            
        }else if (type == S_TEXTURE_CUBE){

            for (int i = 0; i < texturesData.size(); i++){
                texturesData[i]->resamplePowerOfTwo();
            }
            
            textureRender.get()->loadTextureCube(texturesData);
            
            for (int i = 0; i < texturesData.size(); i++){
                delete texturesData[i];
            }
            
            return true;
        }
        
    }
    
    return false;

}

Texture::~Texture(){
    textureRender.reset();
}

Texture::Texture(const Texture& t){
    this->textureRender = t.textureRender;
    this->texturesData = t.texturesData;
    this->type = t.type;
    this->id = t.id;
}

Texture& Texture::operator = (const Texture& t){
    this->textureRender = t.textureRender;
    this->texturesData = t.texturesData;
    this->type = t.type;
    this->id = t.id;

    return *this;
}

std::string Texture::getId(){
    return id;
}

int Texture::getType(){
    return type;
}

std::shared_ptr<TextureRender> Texture::getTextureRender(){
    return textureRender;
}

int Texture::getColorFormat(){
    if (textureRender)
        return textureRender.get()->getColorFormat();
    
    return -1;
}

bool Texture::hasAlphaChannel(){
    
    int colorFormat = getColorFormat();

    if (colorFormat == S_COLOR_GRAY_ALPHA ||
        colorFormat == S_COLOR_RGB_ALPHA ||
        colorFormat == S_COLOR_ALPHA)
        return true;

    return false;
}

int Texture::getWidth(){
    if (textureRender)
        return textureRender.get()->getWidth();
    
    return -1;
}

int Texture::getHeight(){
    if (textureRender)
        return textureRender.get()->getHeight();
    
    return -1;
}

void Texture::destroy(){
    textureRender.reset();
    this->textureRender = NULL;
    TextureRender::deleteUnused();
}
