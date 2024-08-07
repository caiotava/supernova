//
// (c) 2024 Eduardo Doria.
//

#include "Object.h"

#include "subsystem/RenderSystem.h"
#include "subsystem/PhysicsSystem.h"

using namespace Supernova;

Object::Object(Scene* scene): EntityHandle(scene){
    addComponent<Transform>({});
}

Object::Object(Scene* scene, Entity entity): EntityHandle(scene, entity){
}

Object::~Object(){
}

void Object::setName(std::string name){
    Transform& transform = getComponent<Transform>();
    transform.name = name;
}

std::string Object::getName() const{
    Transform& transform = getComponent<Transform>();
    return transform.name;
}

void Object::setPosition(Vector3 position){
    Transform& transform = getComponent<Transform>();

    if (transform.position != position){
        transform.position = position;

        transform.needUpdate = true;
    }
}

void Object::setPosition(const float x, const float y, const float z){
    setPosition(Vector3(x,y,z));
}

void Object::setPosition(const float x, const float y){
    setPosition(Vector3(x,y,0));
}

Vector3 Object::getPosition() const{
    Transform& transform = getComponent<Transform>();
    return transform.position;
}

Vector3 Object::getWorldPosition() const{
    Transform& transform = getComponent<Transform>();
    return transform.worldPosition;
}

void Object::setRotation(Quaternion rotation){
    Transform& transform = getComponent<Transform>();

    if (transform.rotation != rotation){
        transform.rotation = rotation;

        transform.needUpdate = true;
    }
}

void Object::setRotation(const float xAngle, const float yAngle, const float zAngle){
    setRotation(Quaternion(xAngle, yAngle, zAngle));
}

Quaternion Object::getRotation() const{
    Transform& transform = getComponent<Transform>();
    return transform.rotation;
}

Quaternion Object::getWorldRotation() const{
    Transform& transform = getComponent<Transform>();
    return transform.worldRotation;
}

void Object::setScale(const float factor){
    setScale(Vector3(factor,factor,factor));
}

void Object::setScale(Vector3 scale){
    Transform& transform = getComponent<Transform>();

    if (transform.scale != scale){
        transform.scale = scale;

        transform.needUpdate = true;
    }
}

Vector3 Object::getScale() const{
    Transform& transform = getComponent<Transform>();
    return transform.scale;
}

Vector3 Object::getWorldScale() const{
    Transform& transform = getComponent<Transform>();
    return transform.worldScale;
}

void Object::setVisible(bool visible){
    Transform& transform = getComponent<Transform>();
    transform.visible = visible;
    transform.needUpdateChildVisibility = true;
}

bool Object::isVisible() const{
    Transform& transform = getComponent<Transform>();
    return transform.visible;
}

void Object::setVisibleOnly(bool visible){
    Transform& transform = getComponent<Transform>();
    transform.visible = visible;
}

void Object::setLocalMatrix(Matrix4 localMatrix){
    Transform& transform = getComponent<Transform>();
    transform.localMatrix = localMatrix;
    transform.staticObject = true;
}

Matrix4 Object::getLocalMatrix() const{
    Transform& transform = getComponent<Transform>();
    return transform.localMatrix;
}

Matrix4 Object::getModelMatrix() const{
    Transform& transform = getComponent<Transform>();
    return transform.modelMatrix;
}

Matrix4 Object::getNormalMatrix() const{
    Transform& transform = getComponent<Transform>();
    return transform.normalMatrix;
}

Matrix4 Object::getModelViewProjectionMatrix() const{
    Transform& transform = getComponent<Transform>();
    return transform.modelViewProjectionMatrix;
}

void Object::addChild(Object* child){
    scene->addEntityChild(this->entity, child->entity);
}

void Object::addChild(Entity child){
    scene->addEntityChild(this->entity, child);
}

void Object::moveToTop(){
    scene->moveChildToTop(this->entity);
}

void Object::moveUp(){
    scene->moveChildUp(this->entity);
}

void Object::moveDown(){
    scene->moveChildDown(this->entity);
}

void Object::moveToBottom(){
    scene->moveChildToBottom(this->entity);
}

void Object::updateTransform(){
    Transform& transform = getComponent<Transform>();

    scene->getSystem<RenderSystem>()->updateTransform(transform);
}

Body2D Object::getBody2D(){
    scene->getSystem<PhysicsSystem>()->createBody2D(entity);
    return Body2D(scene, entity);
}

void Object::removeBody2D(){
    scene->getSystem<PhysicsSystem>()->removeBody2D(entity);
}

Body3D Object::getBody3D(){
    scene->getSystem<PhysicsSystem>()->createBody3D(entity);
    return Body3D(scene, entity);
}

void Object::removeBody3D(){
    scene->getSystem<PhysicsSystem>()->removeBody3D(entity);
}

Ray Object::getRay(Vector3 direction){
    return Ray(getWorldPosition(), direction);
}