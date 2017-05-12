#include "TextureRect.h"


TextureRect::TextureRect(){
    x = 0;
    y = 0;
    width = 1;
    height = 1;
}

TextureRect::TextureRect(float x, float y, float width, float height){
    setRect(x, y, width, height);
}

TextureRect::TextureRect(const TextureRect& t){
    this->x = t.x;
    this->y = t.y;
    this->width = t.width;
    this->height = t.height;
}

TextureRect& TextureRect::operator = (const TextureRect& t){
    this->x = t.x;
    this->y = t.y;
    this->width = t.width;
    this->height = t.height;
    
    return *this;
}

float TextureRect::getX(){
    return x;
}

float TextureRect::getY(){
    return y;
}

float TextureRect::getWidth(){
    return width;
}

float TextureRect::getHeight(){
    return height;
}

void TextureRect::setRect(float x, float y, float width, float height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void TextureRect::setRect(TextureRect* textureRect){
    setRect(textureRect->getX(), textureRect->getY(), textureRect->getWidth(), textureRect->getHeight());
}

bool TextureRect::isNormalized(){
    if ((x >= 0 && x <= 1) && (y >= 0 && y <= 1) && (width >= 0 && width <= 1) && (height >= 0 && height <= 1)){
        return true;
    }
    return false;
}
