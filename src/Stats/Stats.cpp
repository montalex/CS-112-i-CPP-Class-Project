#include <Stats/Stats.hpp>
#include <Application.hpp>

void Stats::setActive(int id) {
	activeId = id;
}

void Stats::reset() {
	for(std::pair<const int, LabelledGraph> & g : graphs) {
		g.second.graph->reset();
	}
}

void Stats::addGraph(int id, std::string const & label, std::vector<std::string> const & titles,
				     double min, double max, Vec2d const& windowDimensions) {
	Graph* newG = new Graph(titles, windowDimensions, min, max);
	graphs[id].graph.reset(newG);
	graphs[id].label = label;
	activeId = id;
}

void Stats::update(sf::Time dt) {
	// Only update if the right interval has passed, otherwise
	// wait
	if (timeSinceUpdate < getAppConfig().stats_refresh_rate) {
		timeSinceUpdate += dt.asSeconds();
		return;
	}
	// Each graph is updated
	for (std::pair<const int, LabelledGraph> & lg : graphs) {
		lg.second.graph->updateData(sf::seconds(timeSinceUpdate),
		       						getAppEnv().fetchData(lg.second.label));
	}
	// Start to wait again
	timeSinceUpdate = 0;
}

void Stats::drawOn(sf::RenderTarget& target) const {
	graphs.at(activeId).graph->drawOn(target);
}
