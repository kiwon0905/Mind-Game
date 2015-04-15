#pragma once
#include <memory>
#include <unordered_map>
#include <string>


template <class R, class L>
class ResourceManager
{
public:
	std::shared_ptr<R> get(const std::string & n);
	void release(const std::string & n);
private:
	std::unordered_map<std::string, std::shared_ptr<R>> m_resourceMap;
	L m_load;
};

template <class R, class L>
std::shared_ptr<R> ResourceManager<R, L>::get(const std::string & n)
{
	if (m_resourceMap.count(n) == 0)
	{
		auto r= std::shared_ptr<R>(m_load(n));
		if (r == nullptr)
			throw std::exception(std::string("Failed to load " + n).c_str());
		m_resourceMap[n] = r;
	}

	
	return m_resourceMap[n];
}

template <class R, class L>
void ResourceManager<R, L>::release(const std::string & n)
{
	m_resourceMap.erase(n);
}

#include "SFMLResourceLoader.h"

typedef ResourceManager<sf::Texture, TextureLoader> Textures;
typedef ResourceManager<sf::Font, FontLoader> Fonts;
typedef ResourceManager<sf::SoundBuffer, SoundBufferLoader> SoundBuffers;