#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::ms_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(ms_Instance == nullptr);
	ms_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{

	auto& m = ms_Instance->m_Texture;

	auto kvPair = m.find(filename);

	if (kvPair != m.end())
	{
		return kvPair->second;
	}
	else
	{
		auto& texture = m[filename];
		texture.loadFromFile(filename);
		return texture;
	}

}