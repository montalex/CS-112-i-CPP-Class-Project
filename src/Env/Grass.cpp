#include <Env/Grass.hpp>
#include <Application.hpp>

Grass::Grass(const Vec2d& initPos)
    : LivingEntity(initPos, getAppConfig().grass_initial_energy) {
        Vec2d currentPosition = this->getPosition();
        double maxWidth = getAppConfig().window_simulation_width;
        double maxHeight = getAppConfig().window_simulation_height;
        /* Keeps grass in window bounds */
        if(currentPosition.x < 0) {
            currentPosition.x += maxWidth;
        } else if(currentPosition.x > maxWidth) {
            currentPosition.x -= maxWidth;
        }
        if(currentPosition.y < 0) {
            currentPosition.y += maxHeight;
        } else if(currentPosition.y > maxHeight) {
            currentPosition.y -= maxHeight;
        }
        this->setPosition(currentPosition);
    }

void Grass::drawOn(sf::RenderTarget& targetWindow) const {
    auto grassSprite = buildSprite(this->getPosition(), this->getEnergy() / 2.0,
                getAppTexture(getAppConfig().grass_texture));
        targetWindow.draw(grassSprite);
}

void Grass::update(sf::Time dt) {
    double currentEnergy = this->getEnergy();
    if(currentEnergy <= getAppConfig().grass_max_energy) {
        this->setEnergy(currentEnergy + (getAppConfig().grass_growth_factor * dt.asSeconds()));
    }
}
