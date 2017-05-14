#ifndef STATS_HPP
#define STATS_HPP
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>
#include <Stats/Graph.hpp>
#include <SFML/System.hpp>

class Stats: public Drawable, public Updatable {
private:
	struct LabelledGraph {
		std::unique_ptr<Graph> graph;
		std::string label;
	};
	std::unordered_map<int, LabelledGraph> graphs;
	int activeId;
	double timeSinceUpdate = 0;

public:
	/*!
	 * @brief Sets the id of the graph that will be visible
     * 
	 * @param id of the graph desired to become active.
	 */
	void setActive(int id);
	virtual void drawOn(sf::RenderTarget& target) const override;
	void reset();
	/*!
	 * @brief Adds a new graph to the stats or modify an existing one
	 *
	 * @param id the id of the graph to modify/create
	 * @param label the label of the graph to modify/create
	 * @param titles the titles of the data series of the graph
	 * @param min, max the minimum and maximum values for the data values
	 * @param windowDimensions the size of the target window.
	 */
	void addGraph(int id, std::string const & label, std::vector<std::string> const & titles,
				  double min, double max, Vec2d const & windowDimensions);
	virtual void update(sf::Time dt) override;
};

#endif // STATS_HPP
