#pragma once

#include <unordered_map>
#include "UIWidget.h"
#include "UILabel.h"
#include "UIButton.h"
#include "UITextBox.h"

class UI : public sf::Drawable, private sf::NonCopyable
{
public:
	UI() = default;
	~UI() = default;

	void add(const std::string & id, UIbaseWidget::Ptr widget);
	void remove(const std::string & id);

	template <class T>
	typename T::Ptr get(const std::string & id);
	void setFont(sf::Font & font);
	void handleEvent(sf::Event & ev);
	void update(float dt);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::unordered_map<std::string, UIbaseWidget::Ptr> m_widgets;
};

template <class T>
typename T::Ptr UI::get(const std::string & id)
{
	if (m_widgets.count(id) == 0)
		return nullptr;
	return std::static_pointer_cast<T>(m_widgets[id]);
}