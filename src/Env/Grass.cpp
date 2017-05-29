#include <Env/Grass.hpp>
#include <Application.hpp>
#include <Interface/Visitor.hpp>
Grass::Grass(const Vec2d& initPos)
    : LivingEntity(initPos, getAppConfig().grass_initial_energy)
{}

Grass::~Grass() {}

void Grass::drawOn(sf::RenderTarget& targetWindow) const
{
    LivingEntity::drawOn(targetWindow);
    auto grassSprite = buildSprite(getPosition(), getEnergy() / 2.0,
                                   getAppTexture(getAppConfig().grass_texture));
    targetWindow.draw(grassSprite);

    if(isDebugOn()) {
        Obstacle::drawObstacle(targetWindow);
        auto text = buildText(getDebugString(),
                              getPosition(),
                              getAppFont(),
                              getAppConfig().default_debug_text_size,
                              sf::Color::White);
        targetWindow.draw(text);
    }
}

void Grass::update(sf::Time dt)
{
    LivingEntity::update(dt);
    double currentEnergy = getEnergy();
    if(currentEnergy <= getAppConfig().grass_max_energy) {
        setEnergy(currentEnergy + (getAppConfig().grass_growth_factor * dt.asSeconds()));
    }
}

bool Grass::eatable(LivingEntity const* other) const
{
    return other->eatableBy(this);
}

bool Grass::eatableBy(Wolf const* wolf) const
{
    return false;
}

bool Grass::eatableBy(Sheep const* sheep) const
{
    return true;
}

bool Grass::eatableBy(Grass const* grass) const
{
    return false;
}

std::string Grass::getDebugString() const
{
    return to_nice_string(getEnergy());
}

bool Grass::isDead() const
{
    return LivingEntity::isDead();
}

double Grass::getRadius() const
{
    return getEnergy() / 2.0;
}

bool Grass::matable(LivingEntity const* other) const
{
    return other->canMate(this);
}

bool Grass::canMate(Wolf const* wolf) const
{
    return false;
}

bool Grass::canMate(Sheep const* sheep) const
{
    return false;
}

bool Grass::canMate(Grass const* grass) const
{
    return false;
}
void Grass::meet(LivingEntity* mate)
{
    mate->breed(this);
}

void Grass::breed(Wolf* wolf)
{
    return;
}

void Grass::breed(Sheep* sheep)
{
    return;
}

void Grass::breed(Grass* grass)
{
    return;
}

void Grass::acceptVisit(Visitor& v) {
    v.visit(this);
}

std::string Grass::getStatLabel() const {
    return s::GRASS_INDIVIDUAL;
}
