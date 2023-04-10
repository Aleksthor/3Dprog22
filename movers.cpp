#include "movers.h"
#include "visualobjectcomponent.h"
#include "physicscomponent.h"
#include "octahedron.h"
#include "vertex.h"
#include "line.h"
#include "logger.h"

Movers::Movers()  : GameObject()
{
    mesh = new VisualObjectComponent(new Octahedron(5), this, "PlainShader");
    setRootComponent(mesh);
    physics = new PhysicsComponent(this);
    physics->setupAttachment(mesh);


    float angle = std::rand() % 361;
    float r1 = (angle / 180.f) * M_PI;
    angle = std::rand() % 361;
    float r2 = (angle / 180.f) * M_PI;
    position = PhysicsComponent::createVector3D(r1,r2);
    position *= 25.f;
    transform->setPosition(position);

    line = new VisualObjectComponent(new Line(Vertex(Position(position.x(),position.y(),position.z()), QVector3D()),Vertex(Position(position.x(),position.y(),position.z()), QVector3D())),this, "PlainShader");
    line->setupAttachment(mesh);
    line->setUseObjectSpace(false);


    setName("Mover");

}

Movers::Movers(QVector3D pos) : GameObject()
{
    mesh = new VisualObjectComponent(new Octahedron(5), this, "PlainShader");
    setRootComponent(mesh);
    physics = new PhysicsComponent(this);
    physics->setupAttachment(mesh);

    position = pos;
    transform->setPosition(position);

    line = new VisualObjectComponent(new Line(Vertex(Position(position.x(),position.y(),position.z()), Color::Red),Vertex(Position(position.x(),position.y(),position.z()), Color::Red)),this, "PlainShader");
    line->setupAttachment(mesh);
    line->setUseObjectSpace(false);


    setName("Mover");

}

Movers::~Movers()
{

}

void Movers::awake()
{
    GameObject::awake();
    physics->setUsingGravitationalAttraction(true);


    float radius = transform->scale((5 + std::rand() % 6) * 0.05f);
    physics->setMass(radius * M_PI * 4 );

    physics->setVelocity(QVector3D::normal(position, QVector3D(0,0,1)) * 0.1f);
}

void Movers::update(float deltaTime)
{
    GameObject::update(deltaTime);

    position = getPosition3D();
    Line* l = (Line*)line->getObject();
    //l->addVertex(Vertex(Position(position.x(),position.y(),position.z()), Color::Red));
}
