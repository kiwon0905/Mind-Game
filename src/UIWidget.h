#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace sf
{
	class Event;
}

class UIbaseWidget : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	typedef std::shared_ptr<UIbaseWidget> Ptr;
	UIbaseWidget() = default;
	virtual ~UIbaseWidget() = default;

	virtual void handleEvent(sf::Event & ev){}
	virtual void update(float dt){}

protected:
	friend class UI;
	static sf::Font * m_font;
};

template <class W>
class UIWidget : public UIbaseWidget
{
public:
	typedef std::shared_ptr<W> Ptr;
	UIWidget() = default;
	virtual ~UIWidget() = default;

	template <class ... Args>
	static Ptr create(Args && ...args);
};

template <class W > 
template <class ... Args>
typename UIWidget<W>::Ptr UIWidget<W>::create(Args && ...args)
{
	return std::make_shared<W>(std::forward<Args>(args)...);
}